#pragma once

#include <ostream>

namespace config {

enum class ConfigurationName {
    kAngleSensorMaxValue,
    kAngleSensorMinValue,
    kAngleSensorMaxVoltage,
    kAngleSensorMinVoltage,
    kDcMotorMaxVoltage,
    kDcMotorMinVoltage,
    kDcMotorTorque,
    kDcMotorSpeed,
    kControllerProportionalGain,
    kControllerIntegrativeGain,
    kControllerDerivativeGain,
};

/**
 * @brief Converts the given ConfigurationName into the equivalent name
 *
 * @param config_name
 * @return std::string name of the configuration
 *
 * @remark 	Foo logging purposes but also to overload the << operator so that GTest can print the errors correctly
 */
inline std::string ToString(ConfigurationName config_name)
{
    switch (config_name) {
    case ConfigurationName::kAngleSensorMaxValue:
        return "kAngleSensorMaxValue";
    case ConfigurationName::kAngleSensorMinValue:
        return "kAngleSensorMinValue";
    case ConfigurationName::kAngleSensorMaxVoltage:
        return "kAngleSensorMaxVoltage";
    case ConfigurationName::kAngleSensorMinVoltage:
        return "kAngleSensorMinVoltage";
    case ConfigurationName::kDcMotorMaxVoltage:
        return "kDcMotorMaxVoltage";
    case ConfigurationName::kDcMotorMinVoltage:
        return "kDcMotorMinVoltage";
    case ConfigurationName::kDcMotorTorque:
        return "kDcMotorTorque";
    case ConfigurationName::kDcMotorSpeed:
        return "kDcMotorSpeed";
    case ConfigurationName::kControllerProportionalGain:
        return "kControllerProportionalGain";
    case ConfigurationName::kControllerIntegrativeGain:
        return "kControllerIntegrativeGain";
    case ConfigurationName::kControllerDerivativeGain:
        return "kControllerDerivativeGain";

        return {};
        break;
    } // Don't add the default case, so that the compiler can warn you.
}

inline std::ostream& operator<<(std::ostream& ostream, const ConfigurationName& config_name)
{
    ostream << ToString(config_name);
    return ostream;
}

} // namespace config