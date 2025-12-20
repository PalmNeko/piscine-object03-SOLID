#pragma once

class DrivingState
{
    double speed_;
    double angle_;

private:
    DrivingState() {}

public:
    DrivingState(double speed, double angle) : speed_(speed), angle_(angle) {}
    ~DrivingState() {}
    DrivingState(const DrivingState &other) : speed_(other.speed_), angle_(other.angle_) {}

public:
    double speed() { return speed_; }
    double angle() { return angle_; }

public:
    DrivingState &operator=(const DrivingState &other)
    {
        if (this != &other)
        {
            speed_ = other.speed_;
            angle_ = other.angle_;
        }
        return *this;
    }
};
