#ifndef TECSCONTROLLER_H
#define TECSCONTROLLER_H

#include "ConfigurationInterface.h"
#include "ControllerInterface.h"
#include <array>
#include <chrono>

namespace controller {

// Specialized interface for Furuta pendulum control
// For TECS, we need to track both angles and their derivatives
struct PendulumState {
    double alpha; // Arm angle
    double alpha_dot; // Arm angular velocity
    double theta; // Pendulum angle
    double theta_dot; // Pendulum angular velocity
};

class TECSController : public ControllerInterface<PendulumState, double> {
public:
    TECSController(config::ConfigurationInterface& config, std::chrono::milliseconds cycle_time);
    ~TECSController() override = default;

    // Read current pendulum state
    void Read(PendulumState state) override;

    // Write control output (torque applied to the arm)
    [[nodiscard]] double Write() override;

private:
    void Calculate();
    [[nodiscard]] double CalculateTotalEnergy() const;

    // Controller parameters
    double kp_; // Proportional gain
    double ki_; // Integral gain
    double kd_; // Derivative gain

    // System parameters
    double mp_; // Mass of the pendulum
    double lp_; // Length of the pendulum
    double lr_; // Length of the rotating arm
    double jp_; // Moment of inertia of the pendulum
    double jr_; // Moment of inertia of the rotating arm
    const double g_ = 9.81; // Gravity acceleration

    // State variables
    PendulumState current_state_;
    double energy_error_;
    double energy_error_integral_;
    double previous_energy_error_;
    double output_;

    std::chrono::milliseconds cycle_time_;
};

} // namespace controller

#endif
