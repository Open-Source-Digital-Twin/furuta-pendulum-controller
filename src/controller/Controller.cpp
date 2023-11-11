#include "Controller.h"
#include <chrono>

namespace controller {

Controller::Controller(config::ConfigurationInterface& config, std::chrono::milliseconds cycle_time)
    : kp_(config.GetSetting(config::ConfigurationName::kControllerProportionalGain).Value<double>())
    , ki_(config.GetSetting(config::ConfigurationName::kControllerIntegrativeGain).Value<double>())
    , kd_(config.GetSetting(config::ConfigurationName::kControllerDerivativeGain).Value<double>())
    , error_(0.0)
    , integral_part_(0.0)
    , previous_error_(0.0)
    , output_(0.0)
    , cycle_time_(cycle_time)
{
}

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
    this->integral_part_ += ki_ * error_ * static_cast<double>(cycle_time_.count()); // This is an approximation of rectangle area below the curve, it could be improved to a trapezium.
    auto derivative_part = kd_ * (error_ - previous_error_) / static_cast<double>(cycle_time_.count());
    previous_error_ = error_;

    output_ = proportional_part + integral_part_ + derivative_part;
}

} // namespace controller