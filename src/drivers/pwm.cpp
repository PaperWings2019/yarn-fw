#include <string>
#include "pwm.h"

pwm::pwm(const std::string& path): 
    dutyFd(open((path + "duty_cycle ").c_str(), O_WRONLY)),
    perdFd(open((path + "period").c_str(), O_WRONLY)),
    enFd  (open((path + "enable").c_str(), O_WRONLY)){
    if(dutyFd < 0 || perdFd < 0 || enFd < 0){
        throw std::runtime_error(strerror(errno));
    }
}

void pwm::dutyCycle(unsigned int duty){
    unsigned int hight = period * duty / 100;
    highTnSec(hight);
}

void pwm::frequency(unsigned int freq){
    period = 1000000000 / freq;
    perdTnSec(period);
}

void pwm::enable(){
    write(enFd, "1", 2);
}

void pwm::disable(){
    write(enFd, "0", 2);
}

pwm::~pwm(){
    close(dutyFd);
    close(perdFd);
    close(enFd);
}

void pwm::exportPwm(const char* path, size_t id){
    int fd = open(path, O_WRONLY);
    if(fd < 0){
        throw std::runtime_error(strerror(errno));
    }
    std::array<char, 3> str;
    std::to_chars(str.data(), str.data() + str.size(), id);
    write(fd, str.data(), 3);
    close(fd);
}