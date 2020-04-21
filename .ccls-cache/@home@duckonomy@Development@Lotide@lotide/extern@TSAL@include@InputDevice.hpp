#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "OutputDevice.hpp"
#include <vector>

namespace tsal {

/** @class InputDevice
 * @brief Base class for a device that takes input
 * 
 */
class InputDevice {
  public:
    virtual ~InputDevice() {};
    virtual double getInput() { return 0; };
    // virtual void getInput(AudioBuffer<float> &buffer) { return; };
};

}

#endif
