#pragma once

#include "Engine.hpp"
#include "Brake.hpp"
#include "SteerWheel.hpp"
#include "CompositeDrivingStateCalculator.hpp"

class Car
{
    Engine engine;
    Brake brake;
    SteerWheel steerWheel;
    CompositeDrivingStateCalculator stateCalculator;

public:
    DrivingState state_;
    const DrivingState &state() { return state_; }

public:
    Car() {}
    Car(const Engine &engine,
        const Brake &brake,
        const SteerWheel &steerWheel) : engine(engine),
                                        brake(brake),
                                        steerWheel(steerWheel)
    {
        stateCalculator.addFormula(this->engine);
        stateCalculator.addFormula(this->brake);
        stateCalculator.addFormula(this->steerWheel);
    }

    ~Car() {}
    Car(const Car &other)
    {
        *this = other;
    }

public:
    void start() { engine.power(true); }
    void stop() { engine.power(false); }
    void accelerate(double speed) { engine.instanceSpeed(speed); }
    void shift_gears_up() {}
    void shift_gears_down() {}
    void reverse() {}
    void turn_wheel(double angle) { steerWheel.angle(angle); }
    void straighten_wheels() { steerWheel.angle(0); }
    void apply_force_on_brakes(double force) { brake.force(force); }
    void apply_emergency_brakes() { brake.force(100); }
    void update() { state_ = stateCalculator.calculate(state_, 1); }

private:
    Car &operator=(const Car &other)
    {
        if (this != &other)
        {
            state_ = other.state_;
            engine = other.engine;
            brake = other.brake;
            steerWheel = other.steerWheel;
            stateCalculator = CompositeDrivingStateCalculator();

            stateCalculator.addFormula(engine);
            stateCalculator.addFormula(brake);
            stateCalculator.addFormula(steerWheel);
        }
        return *this;
    }
};
