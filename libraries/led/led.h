#ifndef LED_H_
#define LED_H_

#include "Arduino.h"


class Led {
    private:
        int _led;
        

    public:
        const int heartBeatInterval = 500;
        long int heartBeatTime = 0;
        bool heartBeatOn = false;

        Led(int pin);
        virtual void sendHeartBeat();

};

#endif /* LED_H_ */