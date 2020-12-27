//
//  EventNode.cpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#include "EventNode.hpp"
#include "TimerEvent.hpp"
#include "RequestEvent.hpp"
#include "DiskDoneEvent.hpp"

void EventNode::addTimer(TimerEvent *timer) {
    timerEvent = timer;
    isTimer = true;
}


void EventNode::addRequest(RequestEvent *request) {
    requestEvent = request;
    isRequest = true;
}


void EventNode::addDiskDone(DiskDoneEvent *dDone) {
    ddoneEvent = dDone;
    isDDone = true;
}


TimerEvent* EventNode::getTimer() {
    return timerEvent;
}


RequestEvent* EventNode::getRequest() {
    return requestEvent;
}



DiskDoneEvent* EventNode::getDiskDone() {
    return ddoneEvent;
}


bool EventNode::isTimerEvent() {
    return isTimer;
}


bool EventNode::isRequestEvent() {
    return isRequest;
}


bool EventNode::isDiskDoneEvent() {
    return isDDone;
}

EventNode* EventNode::next(){
    return _next;
}


void EventNode::next(EventNode *next){
    _next = next;
}


double EventNode::getNodeTime(){
    if (isRequestEvent()){
        return getRequest()->time();
    }
    else if (isTimerEvent()){
        return getTimer()->time();
    }
    else{
        return getDiskDone()->time();
    }
    return 0;
}


