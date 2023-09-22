#ifndef SENSOR_H
#define SENSOR_H

namespace Hal {

template <typename SensorReturnType, typename SensorInputType>
class SensorInterface {
public:
    virtual SensorReturnType GetValue(SensorInputType) = 0;
};

}
#endif // SENSOR_H