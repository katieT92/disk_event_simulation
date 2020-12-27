//
//  DiskDoneEvent.cpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#include "DiskDoneEvent.hpp"

DiskDoneEvent::DiskDoneEvent(double entrTime, double initTime, double curTime, int queueType){
    _time = curTime;
    _entrTime = entrTime;
    _initTime = initTime;
    _queueType = queueType;
}



double DiskDoneEvent::time(){
    return _time;
}



void DiskDoneEvent::time(double curTime){
    _time = curTime;
}


void DiskDoneEvent::print(){
    std::cout << time() << std::endl;
}



int DiskDoneEvent::getQueueType(){
    return _queueType;
}



double DiskDoneEvent::getInitTime(){
    return _initTime;
}




double DiskDoneEvent::getEntrTime(){
    return _entrTime;
}


