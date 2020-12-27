//
//  LUQueue.hpp
//  LU_QUEUE
//
//  Created by Katie Trombetta on 10/30/20.
//

#ifndef LUQueue_hpp
#define LUQueue_hpp

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "LUQueueNode.hpp"

class Request;

class LUQueue: public Queue {

public:
    LUQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~LUQueue();

private:
    LUQueueNode *head, *tail;
};

#endif /* LUQueue_hpp */
