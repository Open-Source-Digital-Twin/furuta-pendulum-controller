#ifndef CONFIGURATION_INTERFACE_H
#define CONFIGURATION_INTERFACE_H
#include "ConfigurationName.h"
#include "Setting.h"
#include <string>

namespace config {
class ConfigurationInterface {
public:
    virtual ~ConfigurationInterface() = default;
    /**
     * @brief Get the setting according to configuration name
     *
     * @param config_name
     * @return Setting
     */
    virtual Setting GetSetting(ConfigurationName config_name) = 0;
};

} // namespace config

#endif // CONFIGURATION_INTERFACE_H