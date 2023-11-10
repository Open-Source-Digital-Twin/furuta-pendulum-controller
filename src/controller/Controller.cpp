#include "Controller.h"
#include <chrono>

namespace controller {

void Controller::Read(double error)
{
    this->error_ = error;
}

double Controller::Write()
{
    Calculate();
    return output_;
}

void Controller::Calculate()
{
    auto proportional_part = kp_ * error_;
    this->integral_part_ += ki_ * error_ * static_cast<double>(dt_.count()); // This is an approximation of rectangle area below the curve, it could be improved to a trapezium.
    auto derivative_part = kd_ * (error_ - previous_error_) / static_cast<double>(dt_.count());
    previous_error_ = error_;

    output_ = proportional_part + integral_part_ + derivative_part;
}

} // namespace controller