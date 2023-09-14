#ifndef ANGLE_SENSOR_H
#define ANGLE_SENSOR_H

#include "SensorInterface.h"

class AngleSensor : public SensorInterface {
public:
    explicit AngleSensor(double initialAngle);
    double GetAngle() override;

private:
    double angle_;
};

#endif