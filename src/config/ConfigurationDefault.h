#pragma once

#include "Setting.h"
#include <cmath>
#include <optional>
#include <vector>

namespace config {

const std::vector<Setting> kDefaultConfig = {
    { ConfigurationName::kAngleSensorMaxValue,
        M_PIf,
        std::nullopt,
        std::nullopt,
        "rad",
        "Maximum value of sensor's range" },
    { ConfigurationName::kAngleSensorMinValue,
        -M_PIf,
        std::nullopt,
        std::nullopt,
        "rad",
        "Minimum value of sensor's range" },
};

} // namespace config