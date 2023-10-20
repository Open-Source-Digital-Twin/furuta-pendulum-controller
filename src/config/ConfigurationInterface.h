#ifndef CONFIGURATION_INTERFACE_H
#define CONFIGURATION_INTERFACE_H

namespace config {
template <typename ConfigurationFileType>
class ConfigurationInterface {
public:
    virtual ConfigurationFileType ReadConfigurationFile() = 0;
    virtual int WriteConfigurationFile(ConfigurationFileType jsonfile) = 0;
    virtual ~ConfigurationInterface() = default;
};
} // namespace config

#endif // CONFIGURATION_INTERFACE_H