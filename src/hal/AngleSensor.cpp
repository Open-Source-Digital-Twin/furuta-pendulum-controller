#include "AngleSensor.h"

namespace hal {

namespace {
    const double kMinAngle_ = 0.0;
    const double kMaxAngle_ = 360.0;
}

AngleSensor::AngleSensor(double initialAngle)
    : angle_(initialAngle)
    , kMinAngle_(0.0)
    , kMaxAngle_(360.0)
{
}

double AngleSensor::GetValue(int /* unused */)
{
    // get here
    return angle_;
}

}
