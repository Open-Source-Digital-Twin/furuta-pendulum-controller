#include "AngleSensorProto.h"
#include <algorithm>

namespace Hal {

const double AngleSensorProto::kMinAngle = 0.0;
const double AngleSensorProto::kMaxAngle = 360.0;

AngleSensorProto::AngleSensorProto(double initialAngle)
    : angle_(initialAngle)
{
}

double AngleSensorProto::GetValue(google::protobuf::Message& sensorMessage)
{

    double angle = sensorMessage.GetReflection()->GetDouble(sensorMessage, sensorMessage.GetDescriptor()->FindFieldByName("angle"));
    angle = std::clamp(angle, kMinAngle, kMaxAngle);
    return angle;
}

}
