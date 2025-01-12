#include "error.h"

ClientError::ClientError(const string &errorName, const string &func)
    : name(errorName), func(func), message("Error: " + errorName + " in function: " + func) {}

const char *ClientError::what() const noexcept {
    return message.c_str();
}

string ClientError::getName() const {
    return name;
}

string ClientError::getFunc() const {
    return func;
}   
