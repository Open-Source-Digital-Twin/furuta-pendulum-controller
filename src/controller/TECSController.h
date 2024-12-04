#ifndef TECSCONTROLLER_H
#define TECSCONTROLLER_H

#include "ConfigurationInterface.h"
#include "ControllerInterface.h"
#include <chrono>

//TODO: write documentation to explain TECS approach
namespace controller {

class TECSController : ControllerInterface<double, double> {
public:
    TECSController(config::ConfigurationInterface& config, std::chrono::milliseconds cycle_time);
    ~TECSController() override = default;
    void Read(double error) override;
    [[nodiscard]] double Write() override;

private:
    void Calculate(double alpha, double theta, double He);

    double kp_;
    double ki_;
    double kd_;
    double mp_; // Mass of the pendulum
    double lp_; // Length of the pendulum
    double lr_; // Length of the rotating arm
    double jp_; // Moment of inertia of the pendulum
    double jr_; // Moment of the rotating arm

    const double g_ = 9.81;
    std::chrono::milliseconds cycle_time_;
};

} // namespace tecscontroller

#endif
