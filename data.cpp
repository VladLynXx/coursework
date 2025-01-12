#include "data.h"

// Конструктор
Data::Data(const string &path_to_conf, const string &path_to_in, const string &path_to_out)
    : path_to_conf(path_to_conf), path_to_in(path_to_in), path_to_out(path_to_out) {}

// Метод для получения пути к файлу конфигурации
string Data::getConfigPath() const
{
    return this->path_to_conf;
}

// Метод для получения пути к входному файлу
string Data::getInputPath() const
{
    return this->path_to_in;
}

// Метод для получения пути к выходному файлу
string Data::getOutputPath() const
{
    return this->path_to_out;
}

// Метод для чтения конфигурационных данных
array<string, 2> Data::conf()
{
    ifstream conf_file(this->path_to_conf);
    if (!conf_file.is_open())
    {
        throw ClientError("Failed to open configuration file \"" + this->path_to_conf + "\"", __func__);
    }

    array<string, 2> credentials;
    string line;
    getline(conf_file, line);
    conf_file.close();

    istringstream iss(line);
    getline(iss, credentials[0], ':');
    getline(iss, credentials[1]);

    // Проверка на наличие обоих значений
    if (credentials[0].empty() || credentials[1].empty())
    {
        throw ClientError("Missing login or password", __func__);
    }

    // Логирование считанных логина и пароля
    cout << "Log: \"Data.conf()\"\n";
    cout << "UserData: " << credentials[0] << " " << credentials[1] << "\n";

    return credentials;
}

// Метод для чтения данных
vector<vector<float>> Data::read()
{
    ifstream input_file(this->path_to_in, ios::binary);
    if (!input_file.is_open())
        throw ClientError("Failed to open input file for reading.", __func__);

    // Чтение количества векторов
    uint32_t num_vectors;
    input_file.read(reinterpret_cast<char *>(&num_vectors), sizeof(num_vectors));

    vector<vector<float>> data(num_vectors);

    // Чтение каждого вектора
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        // Чтение размера вектора
        uint32_t vector_size;
        input_file.read(reinterpret_cast<char *>(&vector_size), sizeof(vector_size));

        // Чтение значений вектора
        vector<float> vec(vector_size);
        for (uint32_t j = 0; j < vector_size; ++j)
        {
            input_file.read(reinterpret_cast<char *>(&vec[j]), sizeof(vec[j])); // Чтение в бинарном формате
        }

        data[i] = vec;
    }

    input_file.close();

    // Логирование всех прочитанных векторов
    cout << "Log: Data.read()\n";
    printVectors(data);

    return data;
}

// Метод для записи числовых данных
void Data::write(const vector<float> &data)
{   

    // Логирование  вектора
    cout << "Log: Data.write()\n";
    printVector(data);
    ofstream output_file(this->path_to_out, ios::binary);
    if (!output_file.is_open())
    {
        throw ClientError("Failed to open output file \"" + this->path_to_out + "\"", __func__);
    }

    // Запись количества результатов
    uint32_t count = data.size();
    output_file.write(reinterpret_cast<const char *>(&count), sizeof(count));

    // Запись самих результатов
    for (const auto &num : data)
    {
        output_file.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }

    output_file.close();
}

// Функция для логирования одного вектора
void printVector(const vector<float>& vec) {
    cout << "{ ";
    for (const auto& val : vec) {
        cout << val << " ";
    }
    cout << "}" << endl;
}

// Функция для логирования множества векторов
void printVectors(const vector<vector<float>>& vectors) {
    cout << "{\n";
    for (const auto& vec : vectors) {
        cout << "  ";
        printVector(vec);
    }
    cout << "}" << endl;
}
