#pragma once

#include "error.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief Класс для разбора аргументов командной строки
 */
class CMDParser
{
public:
    /**
     * @brief Конструктор класса CMDParser
     */
    CMDParser();

    /**
     * @brief Получить адрес сервера
     * 
     * @return Адрес сервера
     */
    string getAddress();

    /**
     * @brief Получить порт сервера
     * 
     * @return Порт сервера
     */
    int getPort();

    /**
     * @brief Получить путь к входному файлу данных
     * 
     * @return Путь к входному файлу данных
     */
    string getInputPath();

    /**
     * @brief Получить путь к выходному файлу данных
     * 
     * @return Путь к выходному файлу данных
     */
    string getOutputPath();

    /**
     * @brief Получить путь к файлу конфигурации
     * 
     * @return Путь к файлу конфигурации
     */
    string getConfigPath();

    /**
     * @brief Разбор аргументов командной строки
     * 
     * @param argc Количество аргументов
     * @param argv Массив аргументов
     * @throw ClientError Если аргументы некорректные или отсутствуют
     */
    void parseArgs(int argc, char *argv[]);

    /**
     * @brief Показ справки по использованию программы
     */
    void showHelp();

private:
    string address = "127.0.0.1";     ///< Адрес сервера
    uint16_t port = 33333;      ///< Порт сервера
    string input_path = "input.bin";  ///< Путь к входному файлу
    string output_path = "output.bin"; ///< Путь к выходному файлу
    string config_path = "config.txt"; ///< Путь к файлу конфигурации
};
