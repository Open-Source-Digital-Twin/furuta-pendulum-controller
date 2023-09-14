#ifndef ACTUATOR_H
#define ACTUATOR_H

class ActuatorInterface {
public:
    virtual void SetState(double state) = 0;
};

#endif