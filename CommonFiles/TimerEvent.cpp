//
//  TimerEvent.cpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#include "TimerEvent.hpp"


TimerEvent::TimerEvent(double curTime){
    _time = curTime;
}



double TimerEvent::time(){
    return _time;
}



void TimerEvent::time(double curTime){
    _time = curTime;
}


void TimerEvent::print(){
    std::cout << time() << std::endl;
}
