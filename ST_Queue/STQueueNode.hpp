//
//  STQueueNode.hpp
//  ST_Queue
//
//  Created by Katie Trombetta on 10/25/20.
//

#ifndef STQueueNode_hpp
#define STQueueNode_hpp
#include "../FCFS_Queue/FCFSQueue.hpp"

//#include "FCFSQueue.hpp"
class Request;

class STQueueNode{
public:
    STQueueNode(Request *req, int cRWHeadTrack, int cRWHeadSector);
    STQueueNode *next();
    void next(STQueueNode *node);
    Request *request();
    int track();
    void attach_track(Request *req, int cRWHeadTrack, int cRWHeadSector);
    FCFSQueue* getFCFSQueue();

private:
    FCFSQueue *_queue;
    STQueueNode *_next;
    Request *_request;
    int _track;
};

#endif /* STQueueNode_hpp */
