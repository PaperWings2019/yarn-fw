/*
* quiver: class quiver controller
* SdtElectronics 2021.3
*/
#pragma once

#include "drivers/pwm.h"

class quiver{
  public:
    quiver(pwm& lhsPWM, pwm& rhsPWM);

    unsigned int speed(unsigned int v);

    void yaw(int diff);
    void forth();

  private:

    pwm& _lhsPWM;
    pwm& _rhsPWM;
    unsigned int cur_speed;
    unsigned int def_speed;

    static constexpr unsigned int dutyMed = 50;
};