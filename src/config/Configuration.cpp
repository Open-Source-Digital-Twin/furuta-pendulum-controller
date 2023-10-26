#include "Configuration.h"
#include <cstdio>
#include <fstream>
#include <iostream>

namespace config {

Configuration::Configuration(std::filesystem::path filepath)
    : filepath_(std::move(filepath))
{

    if (!std::filesystem::exists(filepath_)) {
        bool creation_success = CreateDefaultConfigurationFile();
        if (!creation_success){
            // This is temporary. I suppose we can use spdlog to log the failures
            std::cout << "Failed to create config file" << std::endl;
        }

    } else {
        // Same as above
        bool load_success = LoadConfigurationFile();
        if (!load_success){
            std::cout << "Failed to load config file" << std::endl;
        }
    }
}

bool Configuration::LoadConfigurationFile() {
    std::ifstream configFile(filepath_);
    configFile >> configData_;
    return configFile.good();
}

// bool Configuration::WriteConfigurationFile(json jsonfile) {
//     std::ofstream configFile(filepath_);
//     configFile << std::setw(4) << jsonfile << std::endl;
//     return configFile.good();
// }
bool Configuration::WriteConfigurationFile(json& jsonfile) {
    // if (jsonfile.empty()) {
    //     // Another spdlog maybe?
    //     return false;
    // }

    // // Open the file for writing
    std::ofstream configFile(filepath_);
    // if (!configFile.is_open()) {
    //     return false;
    // }

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
    // Create JSON objects for each configuration
    json angleSensorConfig = {
        {"Name", "Angle Sensor"},
        {"MaxValue", 360},
        {"MinValue", 0},
        {"DefaultValue", 0},
        {"Description", "abc"}
    };

    json dcMotorConfig = {
        {"Name", "DC Motor"},
        {"MaxValue", 100},
        {"MinValue", 0},
        {"DefaultValue", 0},
        {"Description", "def"}
    };

    // Create a JSON object that contains these configuration objects
    json defaultConfig;
    defaultConfig["angleSensorConfig"] = angleSensorConfig;
    defaultConfig["dcMotorConfig"] = dcMotorConfig;

    bool writeSuccess = WriteConfigurationFile(defaultConfig);

    return writeSuccess;
}

} // namespace config
