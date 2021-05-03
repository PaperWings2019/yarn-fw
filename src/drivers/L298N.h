/*
* L298N: class L298N driver
* SdtElectronics 2021.4
*/

#pragma once

#include <gpiod.hpp>
#include "pwm.h"

class L298N{
    public:
    L298N(          pwm& lhsPWM,         pwm& rhsPWM,
            gpiod::line& lhsIN1, gpiod::line& lhsIN2,
            gpiod::line& rhsIN1, gpiod::line& rhsIN2);

    inline void lhsSpd(unsigned int v);
    inline void rhsSpd(unsigned int v);

    inline void lhsCW();
    inline void rhsCW();

    inline void lhsCCW();
    inline void rhsCCW();

    inline void lhsBrk();
    inline void rhsBrk();

  private:
    pwm& _lhsPWM;
    pwm& _rhsPWM;

    gpiod::line& _lhsIN1;
    gpiod::line& _lhsIN2;
    gpiod::line& _rhsIN1;
    gpiod::line& _rhsIN2;

    unsigned int cur_speed;
    unsigned int def_speed;

    static constexpr unsigned int dutyMed = 50;
};

void L298N::lhsSpd(unsigned int v){
    _lhsPWM.dutyCycle(v);
}

void L298N::rhsSpd(unsigned int v){
    _rhsPWM.dutyCycle(v);
}

void L298N::lhsCW(){
    _lhsIN1.set_value(1);
    _lhsIN2.set_value(0);
}

void L298N::rhsCW(){
    _rhsIN1.set_value(1);
    _rhsIN2.set_value(0);
}

void L298N::lhsCCW(){
    _lhsIN1.set_value(0);
    _lhsIN2.set_value(1);
}

void L298N::rhsCCW(){
    _rhsIN1.set_value(0);
    _rhsIN2.set_value(1);
}

void L298N::lhsBrk(){
    _lhsIN1.set_value(0);
    _lhsIN2.set_value(0);
}

void L298N::rhsBrk(){
    _rhsIN1.set_value(0);
    _rhsIN2.set_value(0);
}