#include "DCMotorProto.h"

namespace Hal {

DCMotorProto::DCMotorProto(double initialState)
    : state_(initialState)
{
}

void DCMotorProto::SetState(google::protobuf::Message& actuatorMessage)
{
    // do stuff here
}

}