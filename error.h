#pragma once

#include <exception>
#include <string>

using namespace std;

/**
 * @brief Класс исключений для работы с клиентом
 */
class ClientError : public exception
{
public:
    /**
     * @brief Конструктор класса ClientError
     * 
     * @param errorName Имя ошибки
     * @param func Имя функции, в которой возникла ошибка
     */
    ClientError(const string &errorName, const string &func);

    /**
     * @brief Получить сообщение об ошибке
     * 
     * @return Сообщение об ошибке
     */
    const char *what() const noexcept override;

    /**
     * @brief Получить имя ошибки
     * 
     * @return Имя ошибки
     */
    string getName() const;

    /**
     * @brief Получить имя функции, в которой возникла ошибка
     * 
     * @return Имя функции
     */
    string getFunc() const;

protected:
    string name;            ///< Имя исключения
    string func;            ///< Имя функции, в которой возникла ошибка
    mutable string message; ///< Сообщение об ошибке
};
