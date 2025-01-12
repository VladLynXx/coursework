#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Функция для просмотра содержимого файла результата
void view_result(const string &file_path)
{
    ifstream infile(file_path, ios::binary);
    if (!infile.is_open())
    {
        cerr << "Error opening file: " << file_path << endl;
        return;
    }

    // Чтение количества результатов
    uint32_t count;
    infile.read(reinterpret_cast<char *>(&count), sizeof(count));
    cout << "Count: " << count << endl;

    // Чтение каждого результата
    vector<float> results(count);
    infile.read(reinterpret_cast<char *>(results.data()), count * sizeof(float));

    // Вывод результатов
    cout << "Results: { ";
    for (const auto &result : results)
    {
        cout << result << " ";
    }
    cout << "}" << endl;

    infile.close();
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: ./view PATH_TO_VIEW_RESULT" << endl;
        return 1;
    }
    
    string file_path = argv[1]; // Путь к вашему файлу результата
    view_result(file_path);
    return 0;
}
