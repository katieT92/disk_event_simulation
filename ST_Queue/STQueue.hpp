//
//  ST_Queue.hpp
//  ST_Queue
//
//  Created by Katie Trombetta on 10/25/20.
//

#ifndef ST_Queue_hpp
#define ST_Queue_hpp

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "STQueueNode.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"


class Request;

class STQueue: public Queue {
public:
    STQueue(): head(nullptr), tail(nullptr) {}
    
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~STQueue();
    
private:
    STQueueNode *head, *tail;
};


#endif /* ST_Queue_hpp */
