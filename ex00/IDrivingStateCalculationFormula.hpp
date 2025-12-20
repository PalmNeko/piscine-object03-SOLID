#pragma once

#include "DrivingState.hpp"

class IDrivingStateCalculationFormula
{
public:
    virtual DrivingState calculate(const DrivingState &state, double deltaTime) = 0;
};
