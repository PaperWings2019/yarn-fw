#include "pwm.h"

pwm::pwm(const char* path): _path(path),
                            dPath(_path + "/duty_cycle"),
                            fPath(_path + "/period"),
                            ePath(_path + "enable"){
    
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
    int fd = open(ePath.c_str(), O_WRONLY);
    if(fd < 0){
        throw std::runtime_error(strerror(errno));
    }
    write(fd, "1", 2);
}

void pwm::disable(){
    int fd = open(ePath.c_str(), O_WRONLY);
    if(fd < 0){
        throw std::runtime_error(strerror(errno));
    }
    write(fd, "0", 2);
}

pwm::~pwm(){

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