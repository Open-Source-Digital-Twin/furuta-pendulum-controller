#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <google/protobuf/message.h>

namespace Hal {

template <typename ActuatorInputType>
class ActuatorInterface {
public:
    virtual void SetState(ActuatorInputType state) = 0;
};
}
#endif // ACTUATOR_H