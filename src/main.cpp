#include <iostream>
#include <memory>
#include "AngleSensor.h"
#include "DCMotor.h"
#include "Configuration.h"
#include "Controller.h"

int main(int, char**)
{
    auto dc_motor = std::make_unique<DCMotor>(0.0);

    auto angle_sensor = AngleSensor(0.0);

    auto configuration = Configuration();

    auto controller = Controller();

    return 0;
}
