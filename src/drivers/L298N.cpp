#include "L298N.h"

L298N::L298N(       pwm& lhsPWM,         pwm& rhsPWM,
            gpiod::line& lhsIN1, gpiod::line& lhsIN2,
            gpiod::line& rhsIN1, gpiod::line& rhsIN2): 
            _lhsPWM(lhsPWM), _rhsPWM(rhsPWM),
            _lhsIN1(lhsIN1), _lhsIN2(lhsIN2),
            _rhsIN1(rhsIN1), _rhsIN2(rhsIN2){
    lhsPWM.frequency(1500);
    rhsPWM.frequency(1500);
    lhsPWM.dutyCycle(0);
    rhsPWM.dutyCycle(0);
    lhsPWM.enable();
    rhsPWM.enable();
    _lhsIN1.request({"", gpiod::line_request::DIRECTION_OUTPUT, 0});
    _lhsIN2.request({"", gpiod::line_request::DIRECTION_OUTPUT, 0});
    _rhsIN1.request({"", gpiod::line_request::DIRECTION_OUTPUT, 0});
    _rhsIN2.request({"", gpiod::line_request::DIRECTION_OUTPUT, 0});
}