#pragma once

#include "IDrivingStateCalculationFormula.hpp"
#include "Gear.hpp"
#include "DrivingState.hpp"

#include <vector>

class Transmission : public IDrivingStateCalculationFormula
{
    std::vector<Gear> gears;
    Gear reverse;
    int gearNo;

public:
    Transmission() : gearNo(0) {}
    ~Transmission() {}
    Transmission(const Transmission &other) { *this = other; }

public:
    DrivingState calculate(const DrivingState &state, double deltaTime)
    {
        Gear *gear;
        if (gearNo == -1)
            gear = &reverse;
        else if (gears.empty())
            return state;
        else
            gear = &gears[gearNo];
        return gear->calculate(state, deltaTime);
    }

    void shiftup()
    {
        if (gearNo < 0)
            return;
        std::size_t UgearNo = static_cast<std::size_t>(gearNo);
        if (UgearNo + 1 < gears.size())
            gearNo++;
        return;
    }

    void shiftdown()
    {
        if (gearNo > 0)
            gearNo--;
    }

    void shiftReverse()
    {
        if (gearNo >= 0)
            gearNo = -1;
        else
            gearNo = 0;
    }

    void addGear(const Gear &gear)
    {
        gears.push_back(gear);
    }

    void setReverse(const Gear &gear)
    {
        reverse = gear;
    }

public:
    Transmission &operator=(const Transmission &other)
    {
        if (this != &other)
        {
            gears = other.gears;
            reverse = other.reverse;
            gearNo = other.gearNo;
        }
        return *this;
    }
};
