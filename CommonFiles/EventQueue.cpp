//
//  EventQueue.cpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#include "EventQueue.hpp"
#include "RequestEvent.hpp"
#include "TimerEvent.hpp"
#include "DiskDoneEvent.hpp"
#include "EventNode.hpp"


void EventQueue::addRequestEvent(RequestEvent *requestEvent, int cRWHeadTrack, int cRWHeadSector) {
    EventNode *eNode = new EventNode();
    eNode->addRequest(requestEvent);
    if( empty() ) {
        head = tail = eNode;
    } else {
        EventNode *curNode = head;
        while(curNode->next() != nullptr && requestEvent->time() >= curNode->next()->getNodeTime()){
            curNode = curNode->next();
        }
        if (curNode->next() == nullptr){
            if (requestEvent->time() >= curNode->getNodeTime()){
                curNode->next(eNode);
                tail = eNode;
            }
            else{
                eNode->next(curNode);
                head = eNode;
            }
        }
        else{
            eNode->next(curNode->next());
            curNode->next(eNode);
        }
    }
}




void EventQueue::addTimerEvent(TimerEvent *timerEvent, int cRWHeadTrack, int cRWHeadSector) {
    EventNode *eNode = new EventNode();
    eNode->addTimer(timerEvent);
    if( empty() ) {
        head = tail = eNode;
    } else {
        EventNode *curNode = head;
        while(curNode->next() != nullptr && timerEvent->time() >= curNode->next()->getNodeTime()){
            curNode = curNode->next();
        }
        if (curNode->next() == nullptr){
            if (timerEvent->time() >= curNode->getNodeTime()){
                curNode->next(eNode);
                tail = eNode;
            }
            else{
                eNode->next(curNode);
                head = eNode;
            }
        }
        else{
            eNode->next(curNode->next());
            curNode->next(eNode);
        }
    }
}





void EventQueue::addDiskDoneEvent(DiskDoneEvent *diskDoneEvent, int cRWHeadTrack, int cRWHeadSector){
    EventNode *eNode = new EventNode();
    eNode->addDiskDone(diskDoneEvent);
    if( empty() ) {
        head = tail = eNode;
    } else {
        EventNode *curNode = head;
        while(curNode->next() != nullptr && diskDoneEvent->time() >= curNode->next()->getNodeTime()){
            curNode = curNode->next();
        }
        if (curNode->next() == nullptr){
            if (diskDoneEvent->time() >= curNode->getNodeTime()){
                curNode->next(eNode);
                tail = eNode;
            }
            else{
                eNode->next(curNode);
                head = eNode;
            }
        }
        else{
            eNode->next(curNode->next());
            curNode->next(eNode);
        }
    }
}





TimerEvent* EventQueue::getTimerEvent(){
    //crazy shit happens here whenever a itmer event is gotten from the equeue
    if( empty() ) {
        std::cout << "Calling EventNode::getTimer() on an empty queue. Terminating...\n";
        exit(1);
    }
    EventNode *eNode = head;
    TimerEvent *tEvent = eNode->getTimer();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete eNode;
    return tEvent;
}






RequestEvent *EventQueue::getRequestEvent() {
    if( empty() ) {
        std::cout << "Calling EventNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    EventNode *eNode = head;
    RequestEvent *rEvent = eNode->getRequest();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete eNode;
    return rEvent;
}






DiskDoneEvent *EventQueue::getDiskDoneEvent() {
    if( empty() ) {
        std::cout << "Calling EventNode::getDiskDone() on an empty queue. Terminating...\n";
        exit(1);
    }
    EventNode *eNode = head;
    DiskDoneEvent *ddEvent = eNode->getDiskDone();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete eNode;
    return ddEvent;
}







bool EventQueue::empty() {
    return head == nullptr;
}




void EventQueue::print() {
    for(auto cur = head; cur; cur = cur->next() ){
        if (cur->isRequestEvent()){
            cur->getRequest()->print();
        }
        else if (cur->isTimerEvent()){
            cur->getTimer()->print();
        }
        else{
            cur->getDiskDone()->print();
        }
    }
        
}




EventQueue::~EventQueue() {
    while( head != nullptr ) {
        EventNode *eNode = head;
        head = eNode->next();
        delete eNode;
    }
}





EventNode* EventQueue::getHead(){
    return head;
}

