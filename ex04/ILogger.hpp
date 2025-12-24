#pragma once

#include <iostream>

class ILogger
{
public:
    virtual void write(const std::string &) = 0;
};
