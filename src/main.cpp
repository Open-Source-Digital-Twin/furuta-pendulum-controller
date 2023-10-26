#include "AngleSensor.h"
#include "Configuration.h"
#include "Controller.h"
#include "DCMotor.h"
#include <iostream>
#include <memory>

int main(int /*unused*/, char** /*unused*/)
{
    auto dc_motor = std::make_unique<hal::DCMotor>(0.0);
    [[gnu::unused]] auto angle_sensor = hal::AngleSensor(0.0);
    [[gnu::unused]] auto controller = Controller();


    config::Configuration config("/usr/local/config/InvertedPendulum/config.json");

    // // Load the existing configuration data from the JSON file
    // bool loadSuccess = config.LoadConfigurationFile();

    // if (loadSuccess) {
    //     std::string targetConfigName = "Angle Sensor"; 
    //     json targetConfig = config.GetConfiguration(targetConfigName);

    //     if (!targetConfig.empty()) {
    //         // Print the configuration element
    //         std::cout << "Configuration Name: " << targetConfig["Name"] << std::endl;
    //         std::cout << "MaxValue: " << targetConfig["MaxValue"] << std::endl;
    //         std::cout << "MinValue: " << targetConfig["MinValue"] << std::endl;
    //         std::cout << "DefaultValue: " << targetConfig["DefaultValue"] << std::endl;
    //         std::cout << "Description: " << targetConfig["Description"] << std::endl;
    //     }
    //     else {
    //         std::cout << "Configuration not found." << std::endl;
    //     }
    // }
    // else {
    //     std::cout << "Failed to load the configuration file." << std::endl;
    // }

    return 0;
}
