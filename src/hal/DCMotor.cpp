#include "DCMotor.h"

namespace hal {

DCMotor::DCMotor(double initialState)
    : motorState_(initialState)
{
}

void DCMotor::SetState(double state)
{
    motorState_ = state;
}

} // namespace hal
