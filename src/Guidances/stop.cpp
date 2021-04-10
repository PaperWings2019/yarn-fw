#include "guidance.h"

class stop: public guidance{
    public: 
        /* 
         * the sensor should work only if we need it to work
         * so it is reasonable and necessary to set the state of the sensor to save energy
         */ 
        void startSensor(); //start the sensor
        void endSensor(); //turn down the sensor
        
        int getTheOutput(); //return the output of sensor
        int stopTheRover(int); //return a value(PWM) to stop the rover if triggered(by certain color square)
};