#include "data.h"
#include "client.h"
#include "cli.h"
#include <array>

int main(int argc, char *argv[])
{
    // Создаем объект класса CMDParser для разбора аргументов командной строки
    CMDParser parser;
    parser.parseArgs(argc, argv);

    // Создаем объект класса Client для подключения к серверу
    Client client(parser.getAddress(), parser.getPort());
    client.conn();

    // Создаем объект класса Data для работы с данными
    Data data(parser.getConfigPath(), parser.getInputPath(), parser.getOutputPath());
    array<string, 2> userpass = data.conf();

    // Аутентификация пользователя
    client.auth(userpass[0], userpass[1]);

    // Чтение данных из входного файла
    vector<vector<float>> vectors = data.read();

    // Выполнение расчетов на сервере
    vector<float> result = client.calc(vectors);

    // Запись результатов в выходной файл
    data.write(result);

    // Закрытие соединения с сервером
    client.close();

    return 0;
}
