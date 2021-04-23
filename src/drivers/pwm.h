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
#include <string>
#include <stdexcept>
#include <array>
#include <charconv>

class pwm{
  public:
    pwm(const char* path);

    void dutyCycle(unsigned int duty);
    void frequency(unsigned int freq);
    inline void highTnSec(unsigned int time);
    inline void perdTnSec(unsigned int perd);

    void enable();
    void disable();

    ~pwm();
    
    static void exportPwm(const char* path, size_t id);
  private:
    const std::string _path;
    const std::string dPath;
    const std::string fPath;
    const std::string ePath;
    unsigned int period;
};

void pwm::highTnSec(unsigned int time){
    int fd = open(dPath.c_str(), O_WRONLY);
    if(fd < 0){
        throw std::runtime_error(strerror(errno));
    }
    std::array<char, 16> str;
    std::to_chars(str.data(), str.data() + str.size(), time);
    write(fd, str.data(), 16);
    close(fd);
}

void pwm::perdTnSec(unsigned int perd){
    int fd = open(fPath.c_str(), O_WRONLY);
    if(fd < 0){
        throw std::runtime_error(strerror(errno));
    }
    std::array<char, 16> str;
    std::to_chars(str.data(), str.data() + str.size(), period);
    write(fd, str.data(), 16);
    close(fd);
}