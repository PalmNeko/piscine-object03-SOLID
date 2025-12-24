#pragma once

#include <cctype>

class IHourlyEmployee
{
public:
    virtual void addWorkTime(std::size_t day, int time) = 0;
};
