#pragma once

#include "IDrivingStateCalculationFormula.hpp"

class Engine : public IDrivingStateCalculationFormula
{
    double speed_;

public:
    double speed() { return speed_; }

    DrivingState calculate(const DrivingState &state, double deltaTime) = 0;
};
