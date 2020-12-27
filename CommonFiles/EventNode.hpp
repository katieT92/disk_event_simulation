//
//  EventNode.hpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#ifndef EventNode_hpp
#define EventNode_hpp

class TimerEvent;
class RequestEvent;
class DiskDoneEvent;

class EventNode {
public:
    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),
                 isTimer(false), isRequest(false), isDDone(false), _next(nullptr) {}
    
    void addTimer(TimerEvent *timer);
    void addRequest(RequestEvent *request);
    void addDiskDone(DiskDoneEvent *dDone);
    
    TimerEvent *getTimer();
    RequestEvent *getRequest();
    DiskDoneEvent *getDiskDone();
    
    bool isTimerEvent();
    bool isRequestEvent();
    bool isDiskDoneEvent();
    EventNode *next();
    void next(EventNode *next);
    double getNodeTime();

    
private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;
    bool isTimer, isRequest, isDDone;
    EventNode *_next;
};


#endif /* EventNode_hpp */
