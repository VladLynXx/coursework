#include "client.h"
#include "error.h"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
#include <cryptopp/osrng.h>

// Конструктор
Client::Client(const string &address, uint16_t port)
    : address(address), port(port), socket(-1) {}

// Метод для установки соединения
void Client::conn()
{
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket < 0)
    {
        throw ClientError("Failed to create socket", __func__);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);

    if (inet_pton(AF_INET, this->address.c_str(), &server_addr.sin_addr) <= 0)
        throw ClientError("Invalid address/ Address not supported", __func__);

    if (connect(this->socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        throw ClientError("Connection failed", __func__);
}

// Метод для аутентификации
void Client::auth(const string &login, const string &password)
{
    // Отправка логина серверу
    if (send(this->socket, login.c_str(), login.size(), 0) < 0)
    {
        throw ClientError("Failed to send login", __func__);
    }

    // Получение соли от сервера
    char salt[17]; // Соль должна быть 16 символов
    int salt_length = recv(this->socket, salt, sizeof(salt) - 1, 0);
    if (salt_length < 0)
    {
        throw ClientError("Failed to receive salt", __func__);
    }
    salt[salt_length] = '\0';

    // Вычисление хеша с использованием CryptoPP
    CryptoPP::MD5 hash_func; // создаем объект хеш-функции
    string hash_hex;

    // формирование хэша и преобразование в шестнадцатеричную строку
    CryptoPP::StringSource(
        string(salt) + password,
        true,
        new CryptoPP::HashFilter(
            hash_func,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash_hex),
                true // Заглавные буквы
                )));

    // Отправка хеша серверу
    if (send(this->socket, hash_hex.c_str(), hash_hex.size(), 0) < 0)
    {
        throw ClientError("Failed to send hash", __func__);
    }

    // Получение ответа от сервера
    char response[1024];
    int response_length = recv(this->socket, response, sizeof(response) - 1, 0);
    if (response_length < 0)
    {
        throw ClientError("Failed to receive auth response", __func__);
    }

    response[response_length] = '\0';
    if (string(response) != "OK")
    {
        throw ClientError("Authentication failed", __func__);
    }
}

vector<float> Client::calc(const vector<vector<float>> &data)
{
    // Передача количества векторов
    uint32_t num_vectors = data.size();
    if (send(this->socket, &num_vectors, sizeof(num_vectors), 0) < 0)
    {
        throw ClientError("Failed to send number of vectors", __func__);
    }

    // Передача каждого вектора
    for (const auto &vec : data)
    {
        uint32_t vec_size = vec.size();
        if (send(this->socket, &vec_size, sizeof(vec_size), 0) < 0)
        {
            throw ClientError("Failed to send vector size", __func__);
        }
        if (send(this->socket, vec.data(), vec_size * sizeof(float), 0) < 0)
        {
            throw ClientError("Failed to send vector data", __func__);
        }
    }

    // Получение результатов
    vector<float> results(num_vectors);
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        if (recv(this->socket, &results[i], sizeof(float), 0) < 0)
        {
            throw ClientError("Failed to receive result", __func__);
        }
    }

    return results;
}

// Метод для закрытия соединения
void Client::close()
{
    if (this->socket >= 0)
    {
        ::close(this->socket);
        this->socket = -1;
    }
}

string Client::getAddress() const {
    return address;
}

uint16_t Client::getPort() const {
    return port;
}
