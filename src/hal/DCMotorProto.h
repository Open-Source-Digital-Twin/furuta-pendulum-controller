#ifndef DC_MOTOR_PROTO_H
#define DC_MOTOR_PROTO_H

#include "ActuatorInterface.h"
#include <google/protobuf/message.h>

namespace Hal {

class DCMotorProto : public ActuatorInterface<google::protobuf::Message&> {
public:
    explicit DCMotorProto(double initialState);
    void SetState(google::protobuf::Message& actuatorMessage) override;

private:
    double state_;
};

}

#endif // DC_MOTOR_PROTO_H