#include "Configuration.h"
#include "ConfigurationDefault.h"
#include <fstream>
#include <ostream>
#include <spdlog/spdlog.h>

namespace config {

Configuration::Configuration(std::filesystem::path filepath)
    : filepath_(std::move(filepath))
{

    if (!std::filesystem::exists(filepath_)) {
        bool creation_success = CreateDefaultConfigurationFile();
        if (!creation_success) {
            spdlog::error("Failed to create config file");
        }
    }
    else {
        bool load_success = LoadConfigurationFile();
        if (!load_success) {
            spdlog::error("Failed to load config file");
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
        spdlog::error("Failed to open file: {}", strerror(errnum));
    }
    try {
        config_file << std::setw(4) << jsonfile << std::endl;
    }
    catch (const std::exception& e) {
        spdlog::error("Error writing JSON to file: {}", e.what());
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

    auto has_name = [config_name](const Setting& setting) { return setting.Name() == config_name; };
    if (auto iter = std::find_if(kDefaultConfig.begin(), kDefaultConfig.end(), has_name); iter != std::end(kDefaultConfig)) {
        return *iter;
    }

    spdlog::warn("Configuration not found. The available configuration names are:");
    for (const auto& [key, value] : configData_.items()) {
        spdlog::warn("{}", key);
    }

    std::string error = "Configuration not found: " + ToString(config_name);
    throw std::runtime_error(error);
}

bool Configuration::CreateDefaultConfigurationFile()
{
    json default_config;

    for (const auto& setting : kDefaultConfig) {
        default_config[ToString(setting.Name())]["name"] = ToString(setting.Name());
        default_config[ToString(setting.Name())]["max_value"] = setting.MaxValue();
        default_config[ToString(setting.Name())]["min_value"] = setting.MinValue();
        default_config[ToString(setting.Name())]["value"] = setting.Value<double>(); // TODO(caiopiccirillo): This is a bit hacky, add support for other types
        default_config[ToString(setting.Name())]["unit"] = setting.Unit();
        default_config[ToString(setting.Name())]["description"] = setting.Description();
    }

    bool write_success = WriteConfigurationFile(default_config);

    return write_success;
}

} // namespace config