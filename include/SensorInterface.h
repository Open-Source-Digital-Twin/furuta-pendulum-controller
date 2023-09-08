#ifndef SENSOR_H
#define SENSOR_H

class SensorInterface {
public:
    virtual double getAngle() = 0;
};

#endif