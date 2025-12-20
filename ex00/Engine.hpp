#pragma once

#include "IDrivingStateCalculationFormula.hpp"

class Engine : public IDrivingStateCalculationFormula
{
    double instance_speed;

public:
    Engine() : instance_speed(0) {}
    ~Engine() {}
    Engine(const Engine &other) : instance_speed(other.instance_speed) {}

public:
    void instanceSpeed(double value) { instance_speed = value; }

    DrivingState calculate(const DrivingState &state, double)
    {
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
        }
        return *this;
    }
};
