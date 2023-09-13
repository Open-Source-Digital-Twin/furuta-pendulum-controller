#include <iostream>
#include <memory>
#include "hal/AngleSensor.h"
#include "hal/DCMotor.h"

int main(int, char**)
{
    auto dcMotor = std::make_unique<DCMotor>(0.0);

    return 0;
}
