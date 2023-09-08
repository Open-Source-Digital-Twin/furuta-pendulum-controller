#ifndef ANGLE_SENSOR_H
#define ANGLE_SENSOR_H

#include "SensorInterface.h"

class AngleSensor : public SensorInterface {
public:
    AngleSensor(double initialAngle);
    double getAngle() override;

private:
    double angle;
};

#endif