#ifndef ACTUATOR_H
#define ACTUATOR_H

class ActuatorInterface {
public:
    virtual void setState(double state) = 0;
};

#endif