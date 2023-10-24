#ifndef CONFIGURATION_INTERFACE_H
#define CONFIGURATION_INTERFACE_H
#include "ConfigurationNameEnum.h"

namespace config {
template <typename ConfigurationFileType>
class ConfigurationInterface {
public:
    virtual ConfigurationFileType ReadConfigurationFile() = 0;
    virtual bool WriteConfigurationFile(ConfigurationFileType jsonfile) = 0;
    virtual int GetConfiguration(ConfigurationNameEnum ConfigName);
    virtual ~ConfigurationInterface() = default;
};
} // namespace config

#endif // CONFIGURATION_INTERFACE_H