#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "ActuatorInterface.h"

class DCMotor : public ActuatorInterface {
public:
    DCMotor(double initialState);
    void setState(double state) override;

private:
    double motorState;
};

#endif