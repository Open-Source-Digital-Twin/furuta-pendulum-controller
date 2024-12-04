#include "TECSController.h"
#include <cmath>
namespace controller {


public:
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

    void Read(double alpha, double alpha_dot, double theta, double theta_dot) override {
        // ??
    }

    double Write() override {
        Calculate();
        return 0.0; //tmp
    }

    void Calculate() override {
        // ??
    }

} // namespace tecscontroller
