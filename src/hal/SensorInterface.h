/**
 * @file SensorInterface.h
 * @author Luca Lagunas
 * @brief A shared templated interface for various types of sensors
 * @version 0.1
 * @date 2023-09-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SENSOR_H
#define SENSOR_H

namespace hal {

template <typename SensorReturnType, typename SensorInputType>
class SensorInterface {
public:
    /**
     * @brief Get the value read by the sensor
     *
     * @return Return the value
     */
    virtual SensorReturnType GetValue(SensorInputType) = 0;
};

} // namespace hal
#endif // SENSOR_H