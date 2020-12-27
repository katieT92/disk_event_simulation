//
//  PUQueue.hpp
//  PU_Queue
//
//  Created by Katie Trombetta on 10/28/20.
//

#ifndef PUQueue_hpp
#define PUQueue_hpp

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "PUQueueNode.hpp"


class Request;

class PUQueue: public Queue {
public:
    PUQueue(): head(nullptr), tail(nullptr) {}
    
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~PUQueue();
    
private:
    PUQueueNode *head, *tail;
};

#endif /* PUQueue_hpp */
