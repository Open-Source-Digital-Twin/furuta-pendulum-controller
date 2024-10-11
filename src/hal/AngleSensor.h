#ifndef ANGLE_SENSOR_H
#define ANGLE_SENSOR_H

#include "SensorInterface.h"

namespace hal {

// int is just a placeholder
class AngleSensor : public SensorInterface<double, int> {
public:
    explicit AngleSensor(double initialAngle);
    [[nodiscard]] double GetValue(int /* unused */) override;

private:
    const double kMinAngle_;
    const double kMaxAngle_;
    double angle_;
};

} // namespace hal

#endif // ANGLE_SENSOR_H
