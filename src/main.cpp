#include "AngleSensor.h"
#include "Configuration.h"
#include "Controller.h"
#include "DCMotor.h"
#include <iostream>
#include <memory>

int main(int, char**)
{
    auto dc_motor = std::make_unique<Hal::DCMotor>(0.0);

    [[gnu::unused]] auto angle_sensor = Hal::AngleSensor(0.0);

    [[gnu::unused]] auto configuration = Configuration();

    [[gnu::unused]] auto controller = Controller();

    return 0;
}
