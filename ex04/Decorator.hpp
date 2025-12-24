#pragma once

#include "ILogger.hpp"

class Decorator : public ILogger
{
protected:
    ILogger *logger;

public:
    Decorator(ILogger &logger) : logger(&logger) {}
    virtual ~Decorator() {}

protected:
    Decorator() : logger(0) {};
};
