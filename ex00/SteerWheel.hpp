#pragma once

#include "IDrivingStateCalculationFormula.hpp"

class SteerWheel : public IDrivingStateCalculationFormula
{
    double angle_; // 向き

public:
    SteerWheel() : angle_(0) {}
    ~SteerWheel() {}
    SteerWheel(const SteerWheel &other) : angle_(other.angle_) {}

public:
    void angle(double value) { angle_ = value; }

    DrivingState calculate(const DrivingState &state, double)
    {
        DrivingState newstate(state.speed(), angle_);
        return newstate;
    }

public:
    SteerWheel &operator=(const SteerWheel &other)
    {
        if (this != &other)
        {
            angle_ = other.angle_;
        }
        return *this;
    }
};
