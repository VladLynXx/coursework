#pragma once

#include <string>
#include <vector>
#include <array>
#include "error.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * @brief Класс для управления конфигурационными данными и данными для расчетов
 */
class Data
{
public:
    /**
     * @brief Конструктор класса Data
     * 
     * @param path_to_conf Путь к файлу конфигурации
     * @param path_to_in Путь к входному файлу данных
     * @param path_to_out Путь к выходному файлу данных
     */
    Data(const string &path_to_conf, const string &path_to_in, const string &path_to_out);

    /**
     * @brief Чтение конфигурационных данных
     * 
     * @return Пара логин и пароль
     * @throw ClientError Если не удается прочитать конфигурационный файл
     */
    array<string, 2> conf();

    /**
     * @brief Чтение входных данных
     * 
     * @return Входные данные для расчетов
     * @throw ClientError Если не удается прочитать входной файл
     */
    vector<vector<float>> read();

    /**
     * @brief Запись выходных данных
     * 
     * @param data Данные для записи
     * @throw ClientError Если не удается записать в выходной файл
     */
    void write(const vector<float> &data);

    /**
     * @brief Получить путь к файлу конфигурации
     * 
     * @return Путь к файлу конфигурации
     */
    string getConfigPath() const;

    /**
     * @brief Получить путь к входному файлу данных
     * 
     * @return Путь к входному файлу данных
     */
    string getInputPath() const;

    /**
     * @brief Получить путь к выходному файлу данных
     * 
     * @return Путь к выходному файлу данных
     */
    string getOutputPath() const;

private:
    string path_to_conf; ///< Путь к файлу конфигурации
    string path_to_in;   ///< Путь к входному файлу
    string path_to_out;  ///< Путь к выходному файлу
};

/**
 * @brief Функция для логирования одного вектора
 * 
 * @param vec Вектор для логирования
 */
void printVector(const vector<float>& vec); 

/**
 * @brief Функция для логирования множества векторов
 * 
 * @param vectors Множество векторов для логирования
 */
void printVectors(const vector<vector<float>>& vectors);
