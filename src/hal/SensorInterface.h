#ifndef SENSOR_H
#define SENSOR_H

class SensorInterface {
public:
    virtual double GetAngle() = 0;
};

#endif