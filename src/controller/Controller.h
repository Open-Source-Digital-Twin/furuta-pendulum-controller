#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ConfigurationInterface.h"
#include "ControllerInterface.h"
#include <chrono>

namespace controller {

class Controller : ControllerInterface<double, double> {
public:
    Controller(config::ConfigurationInterface& config, std::chrono::milliseconds cycle_time);
    ~Controller() override = default;
    void Read(double error) override;
    [[nodiscard]] double Write() override;

private:
    void Calculate();

    double kp_;
    double ki_;
    double kd_;
    double integral_part_;
    double output_;
    double error_;
    double previous_error_;
    std::chrono::milliseconds cycle_time_;
};

} // namespace controller

#endif
