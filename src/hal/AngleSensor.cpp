#include "AngleSensor.h"

const double AngleSensor::kMinAngle = 0.0;
const double AngleSensor::kMaxAngle = 360.0;

AngleSensor::AngleSensor(double initialAngle)
    : angle_(initialAngle)
{
}

double AngleSensor::GetValue(int gpio)
{
    // get here
    return angle_;
}

double AngleSensor::ValidateValue(double angle)
{
    if (angle < kMinAngle) {
        return kMinAngle;
    }
    if (angle > kMaxAngle) {
        return kMaxAngle;
    }
    return angle;
}