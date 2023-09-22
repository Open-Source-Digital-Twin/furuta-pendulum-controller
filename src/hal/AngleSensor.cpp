#include "AngleSensor.h"

namespace Hal {

namespace {
    const double kMinAngle = 0.0;
    const double kMaxAngle = 360.0;
}

AngleSensor::AngleSensor(double initialAngle)
    : kMinAngle(0.0)
    , kMaxAngle(360.0)
    , angle_(initialAngle) // Initialize const members in the member initialization list
{
}

double AngleSensor::GetValue(int gpio)
{
    // get here
    return angle_;
}

}
