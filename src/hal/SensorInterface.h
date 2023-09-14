#ifndef SENSOR_H
#define SENSOR_H

template <typename SensorReturnType, typename SensorInputType>

class SensorInterface {
public:
    virtual SensorReturnType GetValue(SensorInputType) = 0;

protected:
    virtual SensorReturnType ValidateValue(SensorReturnType value) = 0;
};

#endif