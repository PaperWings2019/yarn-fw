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
    
    static void exportPwm(const std::string& path, size_t id);

  private:
    const int dutyFd;
    const int perdFd;
    const int enFd;
    unsigned int period;
};

void pwm::highTnSec(unsigned int time){
    std::array<char, 16> str;
    char* strBeg = str.data();
    auto [ptr, e] = std::to_chars(strBeg, strBeg + str.size(), time);
    if(write(dutyFd, strBeg, ptr - strBeg) < 0){
        throw std::runtime_error(strerror(errno));
    }
}

void pwm::perdTnSec(unsigned int perd){
    period = perd;
    std::array<char, 16> str;
    char* strBeg = str.data();
    auto [ptr, e] = std::to_chars(strBeg, strBeg + str.size(), perd);
    if(write(perdFd, strBeg, ptr - strBeg) < 0){
        throw std::runtime_error(strerror(errno));
    }
}
