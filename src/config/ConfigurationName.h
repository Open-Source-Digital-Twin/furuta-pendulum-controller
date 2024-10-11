#ifndef CONFIGURATION_NAME_H
#define CONFIGURATION_NAME_H

#include <ostream>
#include <spdlog/spdlog.h>

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
 * @remark 	For logging purposes but also to overload the << operator so that GTest can print the errors correctly
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
    } // Don't add the default case, so that the compiler can warn you.
    return {};
}

inline ConfigurationName FromString(const std::string& config_name)
{
    if (config_name == "kAngleSensorMaxValue") {
        return ConfigurationName::kAngleSensorMaxValue;
    }
    if (config_name == "kAngleSensorMinValue") {
        return ConfigurationName::kAngleSensorMinValue;
    }
    if (config_name == "kAngleSensorMaxVoltage") {
        return ConfigurationName::kAngleSensorMaxVoltage;
    }
    if (config_name == "kAngleSensorMinVoltage") {
        return ConfigurationName::kAngleSensorMinVoltage;
    }
    if (config_name == "kDcMotorMaxVoltage") {
        return ConfigurationName::kDcMotorMaxVoltage;
    }
    if (config_name == "kDcMotorMinVoltage") {
        return ConfigurationName::kDcMotorMinVoltage;
    }
    if (config_name == "kDcMotorTorque") {
        return ConfigurationName::kDcMotorTorque;
    }
    if (config_name == "kDcMotorSpeed") {
        return ConfigurationName::kDcMotorSpeed;
    }
    if (config_name == "kControllerProportionalGain") {
        return ConfigurationName::kControllerProportionalGain;
    }
    if (config_name == "kControllerIntegrativeGain") {
        return ConfigurationName::kControllerIntegrativeGain;
    }
    if (config_name == "kControllerDerivativeGain") {
        return ConfigurationName::kControllerDerivativeGain;
    }
    spdlog::critical("Trying to parse {} as ConfigurationName", config_name);
    return {};
}

inline std::ostream& operator<<(std::ostream& ostream, const ConfigurationName& config_name)
{
    ostream << ToString(config_name);
    return ostream;
}

} // namespace config

#endif
