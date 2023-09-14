#ifndef ANGLE_SENSOR_H
#define ANGLE_SENSOR_H

#include "SensorInterface.h"

// int is just a placeholder
class AngleSensor : public SensorInterface<double, int> {
public:
    explicit AngleSensor(double initialAngle);
    double GetValue(int gpio) override;

private:
    double ValidateValue(double angle) override;
    static const double kMinAngle;
    static const double kMaxAngle;
    double angle_;
};

#endif