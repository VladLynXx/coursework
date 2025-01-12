#include <UnitTest++/UnitTest++.h>
#include "cli.h"
#include "client.h"
#include "data.h"
#include "error.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

// Функция для принудительного округления значений до заданной точности
float roundToPrecision(float value, int precision)
{
    float scale = std::pow(10.0f, precision);
    return std::round(value * scale) / scale;
}

// Тест CMDParser
TEST(CMDParserTest)
{
    CMDParser parser;

    parser.parseArgs(0, nullptr);
    CHECK_EQUAL("127.0.0.1", parser.getAddress());
    CHECK_EQUAL(33333, parser.getPort());
    CHECK_EQUAL("input.bin", parser.getInputPath());
    CHECK_EQUAL("output.bin", parser.getOutputPath());
    CHECK_EQUAL("config.txt", parser.getConfigPath());
}

TEST(CMDParserInvalidArgs)
{
    CMDParser parser;
    char *argv[] = {"program", "-invalid", "value"};
    CHECK_THROW(parser.parseArgs(3, argv), ClientError);
}

TEST(CMDParserMissingValues)
{
    CMDParser parser;
    char *argv[] = {"program", "-address", "-port"};
    CHECK_THROW(parser.parseArgs(3, argv), ClientError);
}

// Тест Client конструктора
TEST(ClientConstructorTest)
{
    Client client("127.0.0.1", 33333);

    CHECK_EQUAL("127.0.0.1", client.getAddress());
    CHECK_EQUAL(33333, client.getPort());
}

// Тест Data чтение конфигурационного файла
TEST(DataConfTest)
{
    Data data("config.txt", "input.bin", "output.bin");

    array<string, 2> conf = data.conf();
    CHECK_EQUAL("user", conf[0]);
    CHECK_EQUAL("P@ssW0rd", conf[1]);
    CHECK_EQUAL("config.txt", data.getConfigPath());
}

// Тест Data чтение данных
TEST(DataReadTest)
{
    Data data("config.txt", "input.bin", "output.bin");

    vector<vector<float>> inputData = data.read();

    vector<vector<float>> expected = {
        {-52134.9f, -5177.23f, 18299.2f},
        {31237.3f, 2184.94f, -41018.2f},
        {34558.5f, 64136.6f, 5522.84f}};

    CHECK_EQUAL(expected.size(), inputData.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), inputData[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(
                roundToPrecision(expected[i][j], 1),
                roundToPrecision(inputData[i][j], 1));
        }
    }
}

TEST(DataWriteTest) {
    Data data("config.txt", "input.bin", "output.bin");

    vector<float> writeData = {-39013.0f, -7595.98f, 104218.0f};
    data.write(writeData);

    // Чтение данных после записи напрямую из файла для проверки
    ifstream infile("output.bin", ios::binary);
    if (!infile.is_open()) {
        cerr << "Error opening file: output.bin" << endl;
        return;
    }

    uint32_t count;
    infile.read(reinterpret_cast<char *>(&count), sizeof(count));

    vector<float> results(count);
    infile.read(reinterpret_cast<char *>(results.data()), count * sizeof(float));
    infile.close();

    CHECK_EQUAL(writeData.size(), results.size());
    for (size_t i = 0; i < writeData.size(); ++i) {
        CHECK_EQUAL(roundToPrecision(writeData[i], 2), roundToPrecision(results[i], 2));
    }
}


// Тест Data неверные пути
TEST(DataInvalidConfigPath)
{
    Data data("invalid_config.txt", "input.bin", "output.bin");
    CHECK_THROW(data.conf(), ClientError);
}

TEST(DataInvalidInputPath)
{
    Data data("config.txt", "invalid_input.bin", "output.bin");
    CHECK_THROW(data.read(), ClientError);
}

TEST(DataInvalidOutputPath)
{
    Data data("config.txt", "input.bin", "./invalid/output.bin");
    CHECK_THROW(data.write({1.0f, 2.0f, 3.0f}), ClientError);
}

// Тест ClientError
TEST(ClientErrorTest)
{
    ClientError error("TestError", "TestFunc");
    CHECK_EQUAL("TestError", error.getName());
    CHECK_EQUAL("TestFunc", error.getFunc());
    CHECK_EQUAL("Error: TestError in function: TestFunc", string(error.what()));
}

int main()
{
    return UnitTest::RunAllTests();
}
