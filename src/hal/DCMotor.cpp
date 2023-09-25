#include "DCMotor.h"

namespace Hal {

DCMotor::DCMotor(double initialState)
    : motorState_(initialState)
{
}

void DCMotor::SetState(double state)
{
    motorState_ = state;
}

}