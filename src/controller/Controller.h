#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Configuration.h"
#include "ConfigurationInterface.h"
#include "ControllerInterface.h"
#include <chrono>
namespace controller {

class Controller : ControllerInterface<double, double> {
public:
    explicit Controller(config::ConfigurationInterface<json>& config, std::chrono::microseconds dt);
    ~Controller() override = default;
    void Read(double error) override;
    [[nodiscard]] double Write() override;
    void Calculate();

private:
    double kp_;
    double ki_;
    double kd_;
    double integral_part_;
    double output_;
    double error_;
    double previous_error_;
    std::chrono::microseconds dt_;
};

} // namespace controller
#endif