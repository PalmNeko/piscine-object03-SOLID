#pragma once

#include "Engine.hpp"
#include "Brake.hpp"
#include "SteerWheel.hpp"
#include "Transmission.hpp"
#include "CompositeDrivingStateCalculator.hpp"

class Car
{
    Engine engine;
    Brake brake;
    SteerWheel steerWheel;
    Transmission transmission;
    CompositeDrivingStateCalculator stateCalculator;

public:
    DrivingState state;

public:
    Car() {}
    Car(const Engine &engine,
        const Brake &brake,
        const SteerWheel &steerWheel,
        const Transmission &transmission) : engine(engine),
                                            brake(brake),
                                            steerWheel(steerWheel),
                                            transmission(transmission)
    {
        stateCalculator.addFormula(this->engine);
        stateCalculator.addFormula(this->transmission);
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
    void accelerate(double speed) { engine.speed(state.speed() + speed); }
    void shift_gears_up() { this->transmission.shiftup(); }
    void shift_gears_down() { this->transmission.shiftdown(); }
    void reverse() { this->transmission.shiftReverse(); }
    void turn_wheel(double angle) { steerWheel.angle(angle); }
    void straighten_wheels() { steerWheel.angle(0); }
    void apply_force_on_brakes(double force) { brake.force(force); }
    void apply_emergency_brakes() { brake.force(100); }
    DrivingState calculate() { return stateCalculator.calculate(state, 1); }

private:
    Car &operator=(const Car &other)
    {
        if (this != &other)
        {
            state = other.state;
            engine = other.engine;
            brake = other.brake;
            steerWheel = other.steerWheel;
            transmission = other.transmission;
            stateCalculator = CompositeDrivingStateCalculator();

            stateCalculator.addFormula(engine);
            stateCalculator.addFormula(transmission);
            stateCalculator.addFormula(brake);
            stateCalculator.addFormula(steerWheel);
        }
        return *this;
    }
};
