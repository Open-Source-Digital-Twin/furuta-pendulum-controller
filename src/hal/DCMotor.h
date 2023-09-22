#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "ActuatorInterface.h"

namespace Hal {

class DCMotor : public ActuatorInterface<double> {
public:
    explicit DCMotor(double initialState);
    void SetState(double state) override;

private:
    double motorState_;
};

}

#endif // DC_MOTOR_H