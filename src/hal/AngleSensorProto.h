#ifndef ANGLE_SENSOR_PROTO_H
#define ANGLE_SENSOR_PROTO_H

#include <google/protobuf/message.h>

namespace Hal {

// If I interpreted the intentions correctly the idea here is that the proto version of the sensor also returns a double but
// gets its value from a protobuf message instead of the gpio
class AngleSensorProto : public SensorInterface<double, google::protobuf::Message&> {
public:
    explicit AngleSensorProto(double initialAngle);
    [[nodiscard]] double GetValue(google::protobuf::Message& sensorMessage) override;

private:
    const double kMinAngle_;
    const double kMaxAngle_;
    double angle_;
};

} // namespace Hal

#endif // ANGLE_SENSOR_PROTO_H
