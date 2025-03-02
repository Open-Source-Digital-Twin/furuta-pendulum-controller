#include "TECSController.h"
#include <cmath>
namespace controller {

TECSController::TECSController(config::ConfigurationInterface& config, std::chrono::milliseconds cycle_time)
    : kp_(config.GetSetting(config::ConfigurationName::kControllerProportionalGain).ValueByType<double>())
    , ki_(config.GetSetting(config::ConfigurationName::kControllerIntegrativeGain).ValueByType<double>())
    , kd_(config.GetSetting(config::ConfigurationName::kControllerDerivativeGain).ValueByType<double>())
    , mp_(config.GetSetting(config::ConfigurationName::kControllerMassPendulum).ValueByType<double>())
    , lp_(config.GetSetting(config::ConfigurationName::kControllerLengthPendulum).ValueByType<double>())
    , lr_(config.GetSetting(config::ConfigurationName::kControllerLengthRotatingArm).ValueByType<double>())
    , jp_(config.GetSetting(config::ConfigurationName::kControllerMomentInertiaPendulum).ValueByType<double>())
    , jr_(config.GetSetting(config::ConfigurationName::kControllerMomentInertiaRotatingArm).ValueByType<double>())
    , current_state_({ 0.0, 0.0, 0.0, 0.0 })
    , energy_error_(0.0)
    , energy_error_integral_(0.0)
    , previous_energy_error_(0.0)
    , output_(0.0)
    , cycle_time_(cycle_time)
{
}

void TECSController::Read(PendulumState state)
{
    current_state_ = state;
}

double TECSController::Write()
{
    Calculate();
    return output_;
}

double TECSController::CalculateTotalEnergy() const
{
    // Calculate potential energy
    // For an inverted pendulum, the minimum potential energy is when the pendulum is hanging down (θ = π)
    // and maximum when it's perfectly upright (θ = 0)
    double potential_energy = mp_ * g_ * lp_ * (1 + cos(current_state_.theta));

    // Calculate kinetic energy
    // Kinetic energy includes both rotational arm and pendulum contributions
    double pendulum_kinetic = 0.5 * jp_ * std::pow(current_state_.theta_dot, 2) + 0.5 * mp_ * (std::pow(lr_ * current_state_.alpha_dot, 2) + std::pow(lp_ * current_state_.theta_dot, 2) + 2 * lr_ * lp_ * current_state_.alpha_dot * current_state_.theta_dot * std::cos(current_state_.theta));

    double arm_kinetic = 0.5 * jr_ * std::pow(current_state_.alpha_dot, 2);
    double kinetic_energy = pendulum_kinetic + arm_kinetic;

    // Total energy is the sum of potential and kinetic
    return potential_energy + kinetic_energy;
}

void TECSController::Calculate()
{
    // Calculate the current total energy of the system
    double current_energy = CalculateTotalEnergy();

    // For the inverted pendulum, the target energy is just the potential energy when upright
    double target_energy = mp_ * g_ * lp_ * 2; // Maximum potential energy when θ = 0

    // Calculate energy error
    energy_error_ = target_energy - current_energy;

    // Calculate PID terms based on energy error
    double proportional_part = kp_ * energy_error_;

    // Integrate error (with time factor for correct units)
    energy_error_integral_ += energy_error_ * static_cast<double>(cycle_time_.count()) / 1000.0;
    double integral_part = ki_ * energy_error_integral_;

    // Derivative term uses change in error divided by time
    double derivative_part = kd_ * (energy_error_ - previous_energy_error_) / (static_cast<double>(cycle_time_.count()) / 1000.0);
    previous_energy_error_ = energy_error_;

    // The control output is the torque to apply to the arm
    // We also need to add damping to the arm's angular velocity for stability
    double damping_term = -0.1 * current_state_.alpha_dot;

    // Combine all terms
    output_ = proportional_part + integral_part + derivative_part + damping_term;

    // Apply swing-up control strategy when pendulum is not near upright
    // and balancing control when it's close to upright
    if (std::abs(current_state_.theta) > 0.3) { // If more than ~17 degrees from vertical
        // Swing-up using energy control
        output_ = std::copysign(std::min(std::abs(output_), 1.0), output_);
    }
    else {
        // Near upright position, use LQR-like control directly on angles
        double position_term = -3.0 * current_state_.theta - 0.5 * current_state_.theta_dot;
        double velocity_term = -0.2 * current_state_.alpha_dot;
        output_ = position_term + velocity_term;
    }

    // Limit the output to avoid excessive torque
    const double max_output = 5.0;
    if (output_ > max_output) {
        output_ = max_output;
    }
    if (output_ < -max_output) {
        output_ = -max_output;
    }
}

} // namespace controller
