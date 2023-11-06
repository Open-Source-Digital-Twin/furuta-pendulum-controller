#include "AngleSensor.h"
#include "Configuration.h"
#include "ConfigurationName.h"
#include "Controller.h"
#include "DCMotor.h"
#include "absl/strings/str_join.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
#include <vector>

int main(int /*unused*/, char** /*unused*/)
{
    std::vector<std::string> v = { "foo", "bar", "baz" };
    std::string s = absl::StrJoin(v, "-");

    spdlog::info("Starting controller.");

    spdlog::warn("Checking if abseil is working: {}", s);

    auto dc_motor = std::make_unique<hal::DCMotor>(0.0);
    [[gnu::unused]] auto angle_sensor = hal::AngleSensor(0.0);
    [[gnu::unused]] auto controller = Controller();

    config::Configuration config("/workspaces/inverted-pendulum-controller/config.json");
    auto target_config = config.GetSetting(config::ConfigurationName::kAngleSensorMaxValue).Value<float>();
    spdlog::critical("Getting config: {}", target_config);

    // If we try to get value as int, it'll throw an exception
    // auto int_config = config.GetSetting(config::ConfigurationName::kAngleSensorMaxValue).Value<int>();

    // If we try to get value of a non existing config, it'll show all available configs and throw an exception
    // [[gnu::unused]] auto motor_config = config.GetSetting(config::ConfigurationName::kDcMotorSpeed).Value<float>();

    return 0;
}