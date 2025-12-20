#pragma once

#include "IDrivingStateCalculationFormula.hpp"

class Engine : public IDrivingStateCalculationFormula
{
    double instance_speed;
    bool power_;

public:
    Engine() : instance_speed(0), power_(false) {}
    ~Engine() {}
    Engine(const Engine &other) : instance_speed(other.instance_speed), power_(other.power_) {}

public:
    void instanceSpeed(double value)
    {
        if (power_)
            instance_speed = value;
    }
    void power(bool value) { power_ = value; }

    DrivingState calculate(const DrivingState &state, double)
    {
        if (power_ == false)
            return state;
        DrivingState newstate(state.speed() + instance_speed, state.angle());
        instance_speed = 0;
        return newstate;
    }

public:
    Engine &operator=(const Engine &other)
    {
        if (this != &other)
        {
            instance_speed = other.instance_speed;
            power_ = other.power_;
        }
        return *this;
    }
};
