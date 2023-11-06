#include "Configuration.h"
#include "ConfigurationDefault.h"
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
    std::ifstream config_file(filepath_);
    config_file >> configData_;
    return config_file.good();
}

bool Configuration::WriteConfigurationFile(json& jsonfile)
{
    if (jsonfile.empty()) {
        // Another spdlog maybe?
        return false;
    }

    std::ofstream config_file;
    config_file.open(filepath_);

    if (!config_file.is_open()) {
        int errnum = errno;
        std::cerr << "Failed to open file: " << strerror(errnum) << std::endl;
    }
    try {
        config_file << std::setw(4) << jsonfile << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
        return false;
    }

    return config_file.good();
}

Setting Configuration::GetSetting(ConfigurationName config_name)
{
    // TODO(caiopiccirillo): Implement getting a setting from the config file
    // if (!configData_.empty()) {
    //  return configData_.at(ToString(config_name));
    // }

    auto has_name = [config_name](const Setting& setting) { return setting.name == config_name; };
    if (auto iter = std::find_if(kDefaultConfig.begin(), kDefaultConfig.end(), has_name); iter != std::end(kDefaultConfig)) {
        return *iter;
    }

    std::cout << "Configuration not found. The available configuration names are:" << std::endl;
    for (const auto& [key, value] : configData_.items()) {
        std::cout << key << std::endl;
    }

    std::string error = "Configuration not found: " + ToString(config_name);
    throw std::runtime_error(error);
}

bool Configuration::CreateDefaultConfigurationFile()
{
    json default_config;

    for (const auto& setting : kDefaultConfig) {
        default_config[ToString(setting.name)]["Name"] = ToString(setting.name);
        default_config[ToString(setting.name)]["MaxValue"] = setting.max_value;
        default_config[ToString(setting.name)]["MinValue"] = setting.min_value;
        default_config[ToString(setting.name)]["DefaultValue"] = setting.Value<float>(); // TODO(caiopiccirillo): This is a bit hacky, add support for other types
        default_config[ToString(setting.name)]["Unit"] = setting.unit;
        default_config[ToString(setting.name)]["Description"] = setting.description;
    }

    bool write_success = WriteConfigurationFile(default_config);

    return write_success;
}

} // namespace config