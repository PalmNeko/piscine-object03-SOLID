#pragma once
#include <ctime>

#include "Decorator.hpp"

class DateDecorator : public Decorator
{
    std::string header;

public:
    DateDecorator(ILogger &logger) : Decorator(logger) {}
    ~DateDecorator() {}

private:
    DateDecorator() {}

public:
    void write(const std::string &message)
    {
        std::time_t current;
        struct tm *timeinfo;
        char buffer[80];

        current = time(NULL);
        timeinfo = localtime(&current);
        strftime(buffer, 80, "[%Y %T] ", timeinfo);
        logger->write(buffer + message);
    }
};
