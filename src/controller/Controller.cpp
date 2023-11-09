#include "Controller.h"
#include <chrono>

namespace controller {

// template <typename ConfigFileType>
// Controller::Controller(config::ConfigurationInterface<ConfigFileType>& config, std::chrono::microseconds dt)
//     : kp_(config.GetSetting(config::ConfigurationName::kControllerProportionalGain).template Value<double>())
//     , ki_(config.GetSetting(config::ConfigurationName::kControllerIntegrativeGain).template Value<double>())
//     , kd_(config.GetSetting(config::ConfigurationName::kControllerDerivativeGain).template Value<double>())
//     , error_(0.0)
//     , previous_error_(0.0)
//     , integral_part_(0.0)
//     , output_(0.0)
//     , dt_(dt)
// {
// }

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