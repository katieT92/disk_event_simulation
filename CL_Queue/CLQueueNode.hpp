//
//  CLQueueNode.hpp
//  CL_Queue
//
//  Created by Katie Trombetta on 10/30/20.
//

#ifndef CLQueueNode_hpp
#define CLQueueNode_hpp

class Request;

class CLQueueNode {
public:
    CLQueueNode(Request *req);
    CLQueueNode *next();
    void next(CLQueueNode *node);
    CLQueueNode *prev();
    void prev(CLQueueNode *node);
    Request *request();

private:
    CLQueueNode *_next;
    CLQueueNode *_prev;
    Request *_request;
};


#endif /* CLQueueNode_hpp */
