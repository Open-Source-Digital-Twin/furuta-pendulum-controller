#pragma once

#include "ConfigurationInterface.h"
#include <gmock/gmock.h>

namespace config {

class MockConfiguration : public ConfigurationInterface {
public:
    MOCK_METHOD(Setting, GetSetting, (ConfigurationName config_name), (override));
};

} // namespace config