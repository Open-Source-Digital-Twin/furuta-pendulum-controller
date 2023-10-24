#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;

namespace config {
class Configuration : public ConfigurationInterface<json> {
public:
    explicit Configuration(std::filesystem::path filepath);
    [[nodiscard]] json ReadConfigurationFile() override;
    [[nodiscard]] int GetConfiguration(ConfigurationNameEnum ConfigName) override;
    [[nodiscard]] bool WriteConfigurationFile(json jsonfile) override;

private:
    std::filesystem::path filepath_;
};
} // namespace config

#endif // CONFIGURATION_H