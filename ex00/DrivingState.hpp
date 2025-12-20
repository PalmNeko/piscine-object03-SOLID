#pragma once

class DrivingState
{
    double speed_;
    double angle_;

public:
    DrivingState() : speed_(0), angle_(0) {}
    DrivingState(double speed, double angle) : speed_(speed), angle_(angle) {}
    ~DrivingState() {}
    DrivingState(const DrivingState &other) : speed_(other.speed_), angle_(other.angle_) {}

public:
    double speed() const { return speed_; }
    double angle() const { return angle_; }

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
