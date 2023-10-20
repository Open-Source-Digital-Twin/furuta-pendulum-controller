#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace config {
class Configuration : public ConfigurationInterface<json> {
public:
    explicit Configuration(std::string& filepath);
    json ReadConfigurationFile() override;
    int WriteConfigurationFile(json jsonfile) override;
private:
    std::string filepath_;
};
}

#endif // CONFIGURATION_H