//
//  LUQueueNode.cpp
//  LU_QUEUE
//
//  Created by Katie Trombetta on 10/30/20.
//

#include "LUQueueNode.hpp"
//#include "Request.hpp"
class Request;

LUQueueNode::LUQueueNode(Request *req, int cRWHeadTrack, int cRWHeadSector, int inDirection){
    _queue = new PUQueue();
    _queue->addRequest(req, cRWHeadTrack, cRWHeadSector);
    _next = nullptr;
    _direction = inDirection;
}



LUQueueNode *LUQueueNode::next() {
    return _next;
}



void LUQueueNode::next(LUQueueNode *node) {
    _next = node;
}



Request *LUQueueNode::request() {
    return _queue->getRequest();
}



int LUQueueNode::direction(){
    return _direction;
}




void LUQueueNode::attach_track(Request *req, int cRWHeadTrack, int cRWHeadSector){
    _queue->addRequest(req, cRWHeadTrack, cRWHeadSector);
}





PUQueue* LUQueueNode::getPUQueue(){
    return _queue;
}
