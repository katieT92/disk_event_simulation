//
//  LUQueueNode.hpp
//  LU_QUEUE
//
//  Created by Katie Trombetta on 10/30/20.
//

#ifndef LUQueueNode_hpp
#define LUQueueNode_hpp

#include "../PU_Queue/PUQueue.hpp"
class Request;

class LUQueueNode {
public:
    LUQueueNode(Request *req, int cRWHeadTrack, int cRWHeadSector, int inDirection);
    LUQueueNode *next();
    void next(LUQueueNode *node);
    Request *request();
    int direction();
    void attach_track(Request *req, int cRWHeadTrack, int cRWHeadSector);
    PUQueue* getPUQueue();

private:
    PUQueue *_queue;
    LUQueueNode *_next;
    Request *_request;
    int _direction;
};


#endif /* LUQueueNode_hpp */
