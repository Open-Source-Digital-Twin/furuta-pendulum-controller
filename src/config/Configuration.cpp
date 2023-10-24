#include "Configuration.h"

namespace config {

Configuration::Configuration(std::filesystem::path filepath)
    : filepath_(std::move(filepath))
{
}

json Configuration::ReadConfigurationFile() { }

int Configuration::GetConfiguration(ConfigurationNameEnum ConfigName) { return 0; };

bool Configuration::WriteConfigurationFile(json jsonfile) { return true;}
}