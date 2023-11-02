#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include <filesystem>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace config {
class Configuration : public ConfigurationInterface<json> {
public:
    explicit Configuration(std::filesystem::path filepath);
    [[nodiscard]] bool LoadConfigurationFile() override;
    [[nodiscard]] bool WriteConfigurationFile(json& jsonfile) override;
    [[nodiscard]] json GetConfiguration(std::string& configName) override;
    [[nodiscard]] bool CreateDefaultConfigurationFile();

private:
    std::filesystem::path filepath_;
    json configData_;
};
} // namespace config

#endif // CONFIGURATION_H