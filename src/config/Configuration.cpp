#include "Configuration.h"
#include <cstdio>
#include <fstream>
#include <iomanip>

namespace config {

Configuration::Configuration(std::filesystem::path filepath, ConfigurationNameEnum ConfigName)
    : filepath_(std::move(filepath))
{
    if (!std::filesystem::exists(filepath_)) {
        CreateDefaultConfigurationFile(ConfigName);
    }
}

json Configuration::ReadConfigurationFile()
{
    std::ifstream configFile(filepath_);
    json configurationData;
    configFile >> configurationData;
    return configurationData;
}

int Configuration::GetConfiguration(ConfigurationNameEnum ConfigName)
{
    json configurationData = ReadConfigurationFile();
    return configurationData[ConfigName];
}

bool Configuration::WriteConfigurationFile(json jsonfile)
{
    std::ofstream configFile(filepath_);
    configFile << std::setw(4) << jsonfile << std::endl;

    return configFile.good();
}

void Configuration::CreateDefaultConfigurationFile(ConfigurationNameEnum ConfigName)
{
    json defaultConfig;
    switch (ConfigName) {
        case kAngleSensorConfiguration:
            defaultConfig["Name"] = "Angle Sensor";
            defaultConfig["MaxValue"] = 0;
            defaultConfig["MinValue"] = 360;
            defaultConfig["DefaultValue"] = 0;
            defaultConfig["Description"] = "Measures and converts mechanical rotation into a scaled elecrical signal";
            break;
        case kDcMotorConfiguration:
            defaultConfig["Name"] = "DC Motor";
            defaultConfig["MaxValue"] = 100;
            defaultConfig["MinValue"] = 0;
            defaultConfig["DefaultValue"] = 0;
            defaultConfig["Description"] = "Direct current motor";
            break;
    }


    bool write_success = WriteConfigurationFile(defaultConfig);

    if (write_success) {
        // This is temporary. I suppose we can use spdlog here.
        printf("writing successfull");
    }
    else {
        printf("failed to write to file");
    }
}
} // namespace config
