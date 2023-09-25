/**
 * @file ActuatorInterface.h
 * @author Caio Piccirillo & Luca Lagunas
 * @brief A shared templated interface for various types of actuators
 * @version 0.1
 * @date 2023-09-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <google/protobuf/message.h>

namespace Hal {

template <typename ActuatorInputType>
class ActuatorInterface {
public:
    /**
     * @brief Set the state of the actuator
     *
     * @param state Value to set the actuator's state with
     */
    virtual void SetState(ActuatorInputType state) = 0;
};
}
#endif // ACTUATOR_H