//
//  DiskDoneEvent.hpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#ifndef DiskDoneEvent_hpp
#define DiskDoneEvent_hpp

#include <iostream>

class DiskDoneEvent{
public:
    DiskDoneEvent(double entrTime, double initTime, double curTime, int queueType);
    double time();
    void time(double curTime);
    void print();
    int getQueueType();
    double getInitTime();
    double getEntrTime();


private:
    double _time;
    double _initTime;
    double _entrTime;
    int _queueType;
};

#endif /* DiskDoneEvent_hpp */
