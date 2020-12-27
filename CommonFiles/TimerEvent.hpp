//
//  TimerEvent.hpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#ifndef TimerEvent_hpp
#define TimerEvent_hpp

#include <iostream>

class TimerEvent {
public:
    TimerEvent(double curTime);
    double time();
    void time(double curTime);
    void print();

private:
    double _time;
};

#endif /* TimerEvent_hpp */
