/**
 * @file ActuatorInterface.h
 * @author Luca Lagunas
 * @brief A shared templated interface for various types of actuators
 * @version 0.1
 * @date 2023-09-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ACTUATOR_H
#define ACTUATOR_H

namespace hal {

template <typename ActuatorInputType>
class ActuatorInterface {
public:
    /**
     * @brief Set the state of the actuator
     *
     * @param state Value to set the actuator's state with
     */
    virtual void SetState(ActuatorInputType state) = 0;
    virtual ~ActuatorInterface() = default;
};

} // namespace hal

#endif // ACTUATOR_H
