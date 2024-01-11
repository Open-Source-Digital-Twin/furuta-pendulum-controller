#include "AngleSensor.h"
#include "CMakeConfig.h"
#include "Configuration.h"
#include "Controller.h"
#include "DCMotor.h"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

namespace {
const auto kCycleTime = 1000ms;
}

/**
 * @brief Get the configuration path
 *
 * @return std::filesystem::path
 */
auto GetConfigurationPath()
{
    std::filesystem::path config_path = std::filesystem::current_path();
    config_path /= ".cache";
    config_path /= "controller";
    std::filesystem::create_directories(config_path); // Create directory if it doesn't exist
    config_path /= "config.json";
    return config_path;
}

int main(int /*unused*/, char** /*unused*/)
{
    spdlog::info("Starting {} version {}.", PROJECT_NAME, PROJECT_VERSION);

    spdlog::info("Instantiating motor, sensor and controller.");
    auto dc_motor = std::make_unique<hal::DCMotor>(0.0);
    [[gnu::unused]] auto angle_sensor = hal::AngleSensor(0.0);

    config::Configuration config(GetConfigurationPath());

    // auto target_config = config.GetSetting(config::ConfigurationName::kAngleSensorMaxValue).Value<float>();
    // spdlog::critical("Getting config: {}", target_config);

    // If we try to get value as int, it'll throw an exception
    // auto int_config = config.GetSetting(config::ConfigurationName::kAngleSensorMaxValue).Value<int>();

    // If we try to get value of a non existing config, it'll show all available configs and throw an exception
    // [[gnu::unused]] auto motor_config = config.GetSetting(config::ConfigurationName::kDcMotorSpeed).Value<float>();

    auto pid_controller = controller::Controller(config, kCycleTime);

    while (true) {
        std::this_thread::sleep_for(kCycleTime);
        pid_controller.Read(1.);
        spdlog::info("Getting controller output: {}", pid_controller.Write());
    }

    return 0;
}