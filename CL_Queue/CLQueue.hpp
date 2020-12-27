//
//  CLQueue.hpp
//  CL_Queue
//
//  Created by Katie Trombetta on 10/30/20.
//

#ifndef CLQueue_hpp
#define CLQueue_hpp

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "CLQueueNode.hpp"

class Request;

class CLQueue: public Queue {
    
public:
    CLQueue(): head(nullptr), tail(nullptr), flip(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~CLQueue();

private:
    CLQueueNode *head, *tail, *flip;
    void insertAsHead(CLQueueNode *rNode);
    void insertAsTail(CLQueueNode *rNode);
    void insertBetween(CLQueueNode *rNode, CLQueueNode *curNode);


};


#endif /* CLQueue_hpp */
