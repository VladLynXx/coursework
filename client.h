#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

/**
 * @brief Класс для управления подключением и взаимодействием с сервером
 */
class Client
{
public:
    /**
     * @brief Конструктор класса Client
     * 
     * @param address Адрес сервера
     * @param port Порт сервера
     */
    Client(const string &address, uint16_t port);

    /**
     * @brief Установить соединение с сервером
     * 
     * @throw ClientError Если не удается установить соединение
     */
    void conn();

    /**
     * @brief Аутентификация пользователя на сервере
     * 
     * @param username Имя пользователя
     * @param password Пароль пользователя
     * @throw ClientError Если аутентификация не удалась
     */
    void auth(const string &username, const string &password);

    /**
     * @brief Выполнение расчетов на сервере
     * 
     * @param data Входные данные для расчетов
     * @return Результаты расчетов
     * @throw ClientError Если выполнение расчетов не удалось
     */
    vector<float> calc(const vector<vector<float>> &data);

    /**
     * @brief Закрытие соединения с сервером
     */
    void close();

    /**
     * @brief Получить адрес сервера
     * 
     * @return Адрес сервера
     */
    string getAddress() const;

    /**
     * @brief Получить порт сервера
     * 
     * @return Порт сервера
     */
    uint16_t getPort() const;

private:
    int socket;     ///< Сокет подключения
    string address; ///< Адрес сервера
    uint16_t port;  ///< Порт сервера
};
