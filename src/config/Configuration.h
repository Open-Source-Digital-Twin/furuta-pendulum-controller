#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include <filesystem>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace config {
class Configuration : public ConfigurationInterface<json> {
public:
    explicit Configuration(std::filesystem::path filepath, ConfigurationNameEnum ConfigName);
    [[nodiscard]] json ReadConfigurationFile() override;
    [[nodiscard]] int GetConfiguration(ConfigurationNameEnum ConfigName) override;
    [[nodiscard]] bool WriteConfigurationFile(json jsonfile) override;

private:
    std::filesystem::path filepath_;
    void CreateDefaultConfigurationFile(ConfigurationNameEnum ConfigName);
};
} // namespace config

#endif // CONFIGURATION_H