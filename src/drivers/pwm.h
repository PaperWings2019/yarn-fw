/*
* pwm: class pwm driver
* SdtElectronics 2021.3
*/

#pragma once

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdexcept>
#include <array>
#include <charconv>

class pwm{
  public:
    pwm(const std::string& path);

    void dutyCycle(unsigned int duty);
    void frequency(unsigned int freq);
    inline void highTnSec(unsigned int time);
    inline void perdTnSec(unsigned int perd);

    void enable();
    void disable();

    ~pwm();
    
    static void exportPwm(const char* path, size_t id);
  private:
    const int dutyFd;
    const int perdFd;
    const int enFd;
    unsigned int period;
};

void pwm::highTnSec(unsigned int time){
    std::array<char, 16> str;
    std::to_chars(str.data(), str.data() + str.size(), time);
    write(dutyFd, str.data(), 16);
}

void pwm::perdTnSec(unsigned int perd){
    std::array<char, 16> str;
    std::to_chars(str.data(), str.data() + str.size(), period);
    write(period, str.data(), 16);
}