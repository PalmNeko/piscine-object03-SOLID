#pragma once

#include "IDrivingStateCalculationFormula.hpp"
#include "DrivingState.hpp"

class Gear : IDrivingStateCalculationFormula
{
    double speed_ratio_;

public:
    Gear() : speed_ratio_(0) {}
    Gear(double speed_ratio)
        : speed_ratio_(speed_ratio) {}
    ~Gear() {}
    Gear(const Gear &other) { *this = other; }

public:
    DrivingState calculate(const DrivingState &state, double)
    {
        return DrivingState(state.speed() * speed_ratio_, state.angle());
    }

public:
    Gear &operator=(const Gear &other)
    {
        if (this != &other)
        {
            speed_ratio_ = other.speed_ratio_;
        }
        return *this;
    }
};
