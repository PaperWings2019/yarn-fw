#include <string>
#include "pwm.h"

pwm::pwm(const std::string& path): 
    dutyFd(open((path + "duty_cycle").c_str(), O_WRONLY)),
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
    if(write(enFd, "1", 1) < 0){
        throw std::runtime_error(strerror(errno));
    }
}

void pwm::disable(){
    if(write(enFd, "0", 1) < 0){
        throw std::runtime_error(strerror(errno));
    }
}

pwm::~pwm(){
    close(dutyFd);
    close(perdFd);
    close(enFd);
}

void pwm::exportPwm(const std::string& path, size_t id){
    int fd = open((path + "export").c_str(), O_WRONLY);
    if(fd < 0){
        throw std::runtime_error(strerror(errno));
    }
    std::array<char, 3> str;
    char* strBeg = str.data();
    auto [ptr, e] = std::to_chars(strBeg, strBeg + str.size(), id);
    if(write(fd, strBeg, ptr - strBeg)< 0){
        throw std::runtime_error(strerror(errno));
    }
    close(fd);
}
