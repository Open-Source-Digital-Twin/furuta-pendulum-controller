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
    kDcMotorSpeed
};

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
    } // Don't add the default case, so that the compiler can warn you.
}

inline std::ostream& operator<<(std::ostream& ostream, const ConfigurationName& config_name)
{
    ostream << ToString(config_name);
    return ostream;
}

} // namespace config