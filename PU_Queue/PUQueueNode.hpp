//
//  PUQueueNode.hpp
//  PU_Queue
//
//  Created by Katie Trombetta on 10/28/20.
//

#ifndef PUQueueNode_hpp
#define PUQueueNode_hpp

class Request;

class PUQueueNode {
public:
    PUQueueNode(Request *req);
    PUQueueNode *next();
    void next(PUQueueNode *node);
    Request *request();

private:
    PUQueueNode *_next;
    Request *_request;
};

#endif /* PUQueueNode_hpp */
