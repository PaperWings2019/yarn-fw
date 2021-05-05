#include <algorithm>

#include "quiver.h"

quiver::quiver(L298N& dev): _dev(dev){
}

void quiver::speed(int v){
    const bool dir = (v >= 0);
    v = dir ? v : -v;

    if(dir){
        _dev.lhsCW();
        _dev.rhsCW();
    }else{
        _dev.lhsCCW();
        _dev.rhsCCW();
    }

    _dev.lhsSpd(static_cast<unsigned int>(v));
    _dev.rhsSpd(static_cast<unsigned int>(v));
    cur_speed = static_cast<unsigned int>(v);
}

void quiver::yaw(int diff){
    int lhs = static_cast<int>(cur_speed) - diff;
    int rhs = static_cast<int>(cur_speed) + diff;
    _dev.lhsSpd(std::clamp(lhs, 0, 100));
    _dev.rhsSpd(std::clamp(rhs, 0, 100));
}

void quiver::forth(){
    _dev.lhsCW();
    _dev.rhsCW();
    _dev.lhsSpd(cur_speed);
    _dev.rhsSpd(cur_speed);
}

void quiver::spin(int diff){
    if(diff > 0){
        _dev.lhsCCW();
        _dev.rhsCW();
    }else{
        _dev.rhsCCW();
        _dev.lhsCW();
        diff = -diff;
    }
    _dev.lhsSpd(static_cast<unsigned int>(diff));
    _dev.rhsSpd(static_cast<unsigned int>(diff));
}
