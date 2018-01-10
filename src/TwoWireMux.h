/*

A generic interface for a TwoWire multiplexer.

* * *

This software is licensed under the Revised (3-clause) BSD license as follows:

Copyright (c) 2018, Jeremy Cole <jeremy@jcole.us>

All rights reserved.

See the LICENSE file for more details.

*/

#ifndef TWOWIREMUX_H
#define TWOWIREMUX_H

#include <stdint.h>

#include <Wire.h>

class TwoWireMux {
protected:

  TwoWire *bus;

public:

  TwoWireMux(TwoWire *bus) {
    this->bus = bus;
  }

  TwoWire *getBus() {
    return bus;
  };

  virtual void selectChannel(uint8_t channel) = 0;
};

#endif // TWOWIREMUX_H
