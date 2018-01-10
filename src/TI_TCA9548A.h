/*

Support for the Texas Instruments TCA9548A Low-Voltage 8-Channel I2C Switch with Reset

See the following datasheet:

http://www.ti.com/lit/ds/symlink/tca9548a.pdf

* * *

This software is licensed under the Revised (3-clause) BSD license as follows:

Copyright (c) 2018, Jeremy Cole <jeremy@jcole.us>

All rights reserved.

See the LICENSE file for more details.

*/

#ifndef TI_TCA9548A_H
#define TI_TCA9548A_H

#include <Wire.h>

#include "TwoWireMux.h"

class TI_TCA9548A : public TwoWireMux {
private:

  static const uint8_t I2C_ADDRESS_BASE = 0x70;
  uint8_t address_offset;

  uint8_t base_channel_mask = 0;
  uint8_t current_channel_mask = 0;

public:

  TI_TCA9548A(TwoWire *bus, uint8_t address_offset=0) : TwoWireMux(bus) {
    this->address_offset = address_offset;
  }

  // Set the channel mask directly. This is a bitmap of the 8 channels on the TCA9548A.
  void setChannelMask(uint8_t channel_mask) {
    if (channel_mask != current_channel_mask) {
      bus->beginTransmission(I2C_ADDRESS_BASE + address_offset);
      bus->write(channel_mask);
      bus->endTransmission();
    
      current_channel_mask = channel_mask;
    }
  }

  // Set the base channel mask, a set of channels which will always be enabled.
  void setBaseChannelMask(uint8_t channel_mask) {
    base_channel_mask = channel_mask;
  }

  // Add a channel by number to the base channel mask.
  void addBaseChannel(uint8_t channel) {
    base_channel_mask |= (1 << channel);
    setChannelMask(base_channel_mask);
  }

  // Select a channel (in addition to any channels in the base channel mask).
  void selectChannel(uint8_t channel) {
    setChannelMask(base_channel_mask | (1 << channel));
  }
};

#endif // TI_TCA9548A_H
