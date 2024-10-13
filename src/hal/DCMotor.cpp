#include "DCMotor.h"
#include "spdlog/spdlog.h"

namespace hal {

DCMotor::DCMotor(double initialState)
    : motorState_(initialState)
{
}

void DCMotor::SetState(double state)
{
    spdlog::info("Getting controller output: {}", state);
    motorState_ = state;
}

} // namespace hal
