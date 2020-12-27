//
//  EventQueue.hpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#ifndef EventQueue_hpp
#define EventQueue_hpp

#include <iostream>
class EventNode;

class RequestEvent;
class TimerEvent;
class DiskDoneEvent;

class EventQueue{
public:
    EventQueue(): head(nullptr), tail(nullptr) {}
    void addRequestEvent(RequestEvent *requestEvent, int cRWHeadTrack, int cRWHeadSector);
    void addTimerEvent(TimerEvent *timerEvent, int cRWHeadTrack, int cRWHeadSector);
    void addDiskDoneEvent(DiskDoneEvent *diskDoneEvent, int cRWHeadTrack, int cRWHeadSector);


    TimerEvent *getTimerEvent();
    RequestEvent *getRequestEvent();
    DiskDoneEvent *getDiskDoneEvent();
    bool empty();
    void print();
    ~EventQueue();
    EventNode *getHead();
    
private:
    EventNode *head = nullptr, *tail = nullptr;
};

#endif /* EventQueue_hpp */
