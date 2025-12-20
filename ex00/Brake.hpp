#pragma once

#include "IDrivingStateCalculationFormula.hpp"

class Brake : public IDrivingStateCalculationFormula
{
    double force_;    // ブレーキの力
    double friction_; // 摩擦係数

public:
    Brake(double friction = 1.0) : force_(0), friction_(friction) {}
    ~Brake() {}
    Brake(const Brake &other) : force_(other.force_), friction_(other.friction_) {}

public:
    void force(double value)
    {
        if (value > 100)
            value = 100;
        else if (value < 0)
            value = 0;
        force_ = value;
    }

    DrivingState calculate(const DrivingState &state, double deltaTime)
    {
        double a = -friction_ * force_;
        double newSpeed = state.speed() + a * deltaTime; // v = v0 + at
        if (newSpeed < 0)
            newSpeed = 0;
        DrivingState newstate(newSpeed, state.angle());
        return newstate;
    }

public:
    Brake &operator=(const Brake &other)
    {
        if (this != &other)
        {
            force_ = other.force_;
            friction_ = other.friction_;
        }
        return *this;
    }
};
