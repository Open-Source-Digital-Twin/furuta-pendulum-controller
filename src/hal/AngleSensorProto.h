#ifndef ANGLE_SENSOR_PROTO_H
#define ANGLE_SENSOR_PROTO_H

#include "SensorInterface.h"
#include <google/protobuf/message.h>

// If I interpreted the intentions correctly the idea here is that the proto version of the sensor also returns a double but
// gets its value from a protobuf message instead of the gpio
class AngleSensorProto : public SensorInterface<double, google::protobuf::Message&> {
public:
    explicit AngleSensorProto(double initialAngle);
    double GetValue(google::protobuf::Message& sensorMessage) override;

private:
    double ValidateValue(double angle) override;
    static const double kMinAngle;
    static const double kMaxAngle;
    double angle_;
};

#endif