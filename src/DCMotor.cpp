#include "DCMotor.h"

DCMotor::DCMotor(double initialState)
    : motorState(initialState)
{
}

void DCMotor::setState(double state)
{
    motorState = state;
}