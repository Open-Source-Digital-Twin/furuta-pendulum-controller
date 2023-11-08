#ifndef CONTROLLER_INTERFACE_H
#define CONTROLLER_INTERFACE_H

namespace controller {

template <typename LogicalInput, typename LogicalOutput>
class ControllerInterface {
public:
    virtual ~ControllerInterface() = default;
    virtual void Read(LogicalInput input) = 0;
    [[nodiscard]] virtual LogicalOutput Write() = 0;
};

}

#endif