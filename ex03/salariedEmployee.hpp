#pragma once

#include <cctype>

class ISalariedEmployee
{
public:
    virtual void addBreakTime(std::size_t day, int time) = 0;
};
