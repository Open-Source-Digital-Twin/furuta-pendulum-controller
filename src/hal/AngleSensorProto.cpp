#include "AngleSensorProto.h"
#include <algorithm>

namespace Hal {

namespace {
    const double kMinAngle = 0.0;
    const double kMaxAngle = 360.0;
}

AngleSensorProto::AngleSensorProto(double initialAngle)
    : angle_(initialAngle)
    , kMinAngle_(0.0)
    , kMaxAngle_(0.0)
{
}

double AngleSensorProto::GetValue(google::protobuf::Message& sensorMessage)
{

    double angle = sensorMessage.GetReflection()->GetDouble(sensorMessage, sensorMessage.GetDescriptor()->FindFieldByName("angle"));
    angle = std::clamp(angle, kMinAngle, kMaxAngle);
    return angle;
}

} // namespace Hal
