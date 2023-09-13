#include <iostream>
#include <memory>
#include "AngleSensor.h"
#include "DCMotor.h"
#include "Configuration.h"
#include "Controller.h"

int main(int, char**)
{
    auto dcMotor = std::make_unique<DCMotor>(0.0);

    return 0;
}
