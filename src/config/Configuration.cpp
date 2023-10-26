#include "Configuration.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>

namespace config {

Configuration::Configuration(std::filesystem::path filepath)
    : filepath_(std::move(filepath))
{

    if (!std::filesystem::exists(filepath_)) {
        bool creation_success = CreateDefaultConfigurationFile();
        if (!creation_success) {
            // This is temporary. I suppose we can use spdlog to log the failures
            std::cout << "Failed to create config file" << std::endl;
        }
    }
    else {
        // Same as above
        bool load_success = LoadConfigurationFile();
        if (!load_success) {
            std::cout << "Failed to load config file" << std::endl;
        }
    }
}

bool Configuration::LoadConfigurationFile()
{
    std::ifstream configFile(filepath_);
    configFile >> configData_;
    return configFile.good();
}

bool Configuration::WriteConfigurationFile(json& jsonfile)
{
    if (jsonfile.empty()) {
        // Another spdlog maybe?
        return false;
    }

    std::ofstream configFile;
    configFile.open(filepath_);

    if (!configFile.is_open()) {
        int errnum = errno;
        std::cerr << "Failed to open file: " << strerror(errnum) << std::endl;
    }
    try {
        configFile << std::setw(4) << jsonfile << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
        return false;
    }

    return configFile.good();
}

json Configuration::GetConfiguration(std::string& configName)
{
    if (configData_.contains(configName)) {
        return configData_[configName];
    }
    return {};
}

bool Configuration::CreateDefaultConfigurationFile()
{
    // Create JSON objects for each configuration
    json angleSensorConfig = {
        { "Name", "Angle Sensor" },
        { "MaxValue", 360 },
        { "MinValue", 0 },
        { "DefaultValue", 0 },
        { "Description", "Measures and converts mechanical rotation into a scaled electrical signal" }
    };

    json dcMotorConfig = {
        { "Name", "DC Motor" },
        { "MaxValue", 100 },
        { "MinValue", 0 },
        { "DefaultValue", 0 },
        { "Description", "Direct current motor" }
    };

    // Create a JSON object that contains these configuration objects
    json defaultConfig;
    defaultConfig["angleSensorConfig"] = angleSensorConfig;
    defaultConfig["dcMotorConfig"] = dcMotorConfig;

    bool writeSuccess = WriteConfigurationFile(defaultConfig);

    return writeSuccess;
}

} // namespace config
