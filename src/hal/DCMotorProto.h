#ifndef DC_MOTOR_PROTO_H
#define DC_MOTOR_PROTO_H

#include <google/protobuf/message.h>

namespace hal {

class DCMotorProto : public ActuatorInterface<google::protobuf::Message&> {
public:
    explicit DCMotorProto(double initialState);
    void SetState(google::protobuf::Message& actuatorMessage) override;

private:
    double state_;
};

} // namespace hal

#endif // DC_MOTOR_PROTO_H
