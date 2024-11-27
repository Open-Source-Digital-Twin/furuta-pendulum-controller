#include "TECSController.h"
#include <cmath>
namespace tecscontroller {


class TECSController : public ControllerInterface<double, double> {
public:
    double kappa;
    double ktheta;

    TECSController(config::ConfigurationInterface& config, std::chrono::milliseconds cycle_time)
        : kp_(config.GetSetting(config::ConfigurationName::kControllerProportionalGain).ValueByType<double>())
        , ki_(config.GetSetting(config::ConfigurationName::kControllerIntegrativeGain).ValueByType<double>())
        , kd_(config.GetSetting(config::ConfigurationName::kControllerDerivativeGain).ValueByType<double>())
        , mp_(config.GetSetting(config::ConfigurationName::kControllerMassPendulum).ValueByType<double>())
        , lp_(config.GetSetting(config::ConfigurationName::kControllerLengthPendulum).ValueByType<double>())
        , lr_(config.GetSetting(config::ConfigurationName::kControllerLengthRotatingArm).ValueByType<double>())
        , jp_(config.GetSetting(config::ConfigurationName::kControllerMomentInertiaPendulum).ValueByType<double>())
        , jr_(config.GetSetting(config::ConfigurationName::kControllerMomentInertiaRotatingArm).ValueByType<double>())
    {}

    void Read(double alpha, double theta, double He) override {
        // Calculate desired total energy rate
        double phi_alpha = cos(alpha)*2 / (1 + cos(alpha)*2);
        this->hd_e_ = -kappa*Le*(phi_alpha*sin(alpha));

        // Update error to be the difference between actual and desired total energy rates
        this->error_ = He - hd_e_;
    }

    double Write() override {
        Calculate();
        return output_;
    }

    void Calculate() override {
        auto proportional_part = 0.0; // Swing-up controller does not have a traditional proportional part

        // Update integral part to be the sum of all previous errors
        this->integral_part_ += kappa*Le*sin(alpha_) * static_cast<double>(cycle_time_.count());

        // Update derivative part based on change in alpha and theta
        auto derivative_part = -ktheta * (alpha_ - alpha_prev_) / static_cast<double>(cycle_time_.count());
        alpha_prev_ = alpha_;

        // Calculate output by summing all three parts
        this->output_ = proportional_part + integral_part_ + derivative_part;

        // Limit magnitude of output
        if (output_ > 10.0 || output_ < -10.0) {
            output_ = (output_ > 0) ? 10.0 : -10.0;
        }
    }
};

} // namespace tecscontroller
