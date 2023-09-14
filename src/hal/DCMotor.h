#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "ActuatorInterface.h"

class DCMotor : public ActuatorInterface {
public:
    explicit DCMotor(double initialState);
    void SetState(double state) override;

private:
    double motorState_;
};

#endif