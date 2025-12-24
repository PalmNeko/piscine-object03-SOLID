#pragma once

#include "Decorator.hpp"

class HeaderDecorator : public Decorator
{
    std::string header;

public:
    HeaderDecorator(const std::string &header, ILogger &logger)
        : Decorator(logger), header(header) {}
    ~HeaderDecorator() {}

private:
    HeaderDecorator() {}

public:
    void write(const std::string &message)
    {
        logger->write(this->header + message);
    }
};
