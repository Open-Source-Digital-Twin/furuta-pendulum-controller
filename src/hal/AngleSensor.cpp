#include "AngleSensor.h"

namespace Hal {

namespace {
    const double kMinAngle = 0.0;
    const double kMaxAngle = 360.0;
}

AngleSensor::AngleSensor(double initialAngle)
    : angle_(initialAngle)
    , kMinAngle(0.0)
    , kMaxAngle(360.0)
{
}

double AngleSensor::GetValue(int /* unused */)
{
    // get here
    return angle_;
}

}
