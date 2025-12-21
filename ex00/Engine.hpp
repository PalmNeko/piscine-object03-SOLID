#pragma once

#include "IDrivingStateCalculationFormula.hpp"

class Engine : public IDrivingStateCalculationFormula
{
    double speed_;
    bool power_;

public:
    Engine() : speed_(0), power_(false) {}
    ~Engine() {}
    Engine(const Engine &other) : speed_(other.speed_), power_(other.power_) {}

public:
    void speed(double value) { speed_ = value; }
    void power(bool value) { power_ = value; }

    DrivingState calculate(const DrivingState &state, double)
    {
        if (power_ == false)
            return state;
        DrivingState newstate(speed_, state.angle());
        return newstate;
    }

public:
    Engine &operator=(const Engine &other)
    {
        if (this != &other)
        {
            speed_ = other.speed_;
            power_ = other.power_;
        }
        return *this;
    }
};
