#include "Configuration.h"

namespace config {

Configuration::Configuration(std::string& filepath)
    : filepath_(std::move(filepath)) {}

json Configuration::ReadConfigurationFile(){}

int Configuration::WriteConfigurationFile(json jsonfile){}
}