#include "Configuration.h"
#include <cstdio>
#include <fstream>

namespace config {

Configuration::Configuration(std::filesystem::path filepath)
    : filepath_(std::move(filepath))
{
    std::filesystem::path configFilePath = filepath_ / "config.json";

    if (!std::filesystem::exists(configFilePath)) {
        bool creation_success = CreateDefaultConfigurationFile();
        if (!creation_success){
            // This is temporary. I suppose we can use spdlog to log the failures
            printf("Failed to create config file");
        }

    } else {
        // Same as above
        bool load_success = LoadConfigurationFile();
        if (!load_success){
            printf("Failed to load config file");
        }
    }
}

bool Configuration::LoadConfigurationFile() {
    std::ifstream configFile(filepath_);
    configFile >> configData_;
    return configFile.good();
}

bool Configuration::WriteConfigurationFile(json jsonfile) {
    std::ofstream configFile(filepath_);
    configFile << std::setw(4) << jsonfile << std::endl;
    return configFile.good();
}

json Configuration::GetConfiguration(std::string& configName) {
    // Assuming the configuration data is already loaded
    if (configData_.is_array()) {
        // Loop through the JSON array and find the element with a matching 'Name' field
        for (const auto& configElement : configData_) {
            if (configElement.is_object() && configElement.contains("Name")) {
                const std::string name = configElement["Name"];
                if (name == configName) {
                    // Return the found configuration element
                    return configElement;
                }
            }
        }
    }

    // Return an empty JSON object if the configuration element is not found
    return json();
}


bool Configuration::CreateDefaultConfigurationFile() {
    // Create a default configuration JSON with elements for both kAngleSensorConfiguration and kDcMotorConfiguration
    json defaultConfig;

    json angleSensorConfig;
    angleSensorConfig["Name"] = "Angle Sensor";
    angleSensorConfig["MaxValue"] = 0;
    angleSensorConfig["MinValue"] = 360;
    angleSensorConfig["DefaultValue"] = 0;
    angleSensorConfig["Description"] = "Measures and converts mechanical rotation into a scaled electrical signal";

    json dcMotorConfig;
    dcMotorConfig["Name"] = "DC Motor";
    dcMotorConfig["MaxValue"] = 100;
    dcMotorConfig["MinValue"] = 0;
    dcMotorConfig["DefaultValue"] = 0;
    dcMotorConfig["Description"] = "Direct current motor";

    defaultConfig[kAngleSensorConfiguration] = angleSensorConfig;
    defaultConfig[kDcMotorConfiguration] = dcMotorConfig;

    bool writeSuccess = WriteConfigurationFile(defaultConfig);

    return writeSuccess;
}

} // namespace config
