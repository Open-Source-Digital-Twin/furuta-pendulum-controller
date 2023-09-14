#include "DCMotor.h"

DCMotor::DCMotor(double initialState)
    : motorState_(initialState)
{
}

void DCMotor::SetState(double state)
{
    motorState_ = state;
}