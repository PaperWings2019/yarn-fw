/*
* quiver: class quiver controller
* SdtElectronics 2021.3
*/

#pragma once

#include "drivers/L298N.h"

class quiver{
  public:
    quiver(L298N& dev);

    void speed(int v);

    void yaw(int diff);
    void forth();
    void spin(int diff);

  private:
    L298N& _dev;

    unsigned int cur_speed;
    unsigned int def_speed;

    static constexpr unsigned int dutyMed = 50;
};