#ifndef CONFIGURATION_INTERFACE_H
#define CONFIGURATION_INTERFACE_H
#include "ConfigurationNameEnum.h"
#include <string>

namespace config {
template <typename ConfigurationFileType>
class ConfigurationInterface {
public:
    /**
     * @brief Loads the content of the configuration file into a private member variable
     *
     * @return true when loading successfully
     * @return false when failing to load
     */
    virtual bool LoadConfigurationFile() = 0;
    /**
     * @brief Writes configuration data to file
     * 
     * @param jsonfile 
     * @return true when writing successfully
     * @return false when failing to write
     */
    virtual bool WriteConfigurationFile(ConfigurationFileType& jsonfile) = 0;
    /**
     * @brief Get a specific configuration from the private member variable
     * 
     * @param ConfigName 
     * @return ConfigurationFileType 
     */
    virtual ConfigurationFileType GetConfiguration(std::string& configName) = 0;
    virtual ~ConfigurationInterface() = default;
};
} // namespace config

#endif // CONFIGURATION_INTERFACE_H