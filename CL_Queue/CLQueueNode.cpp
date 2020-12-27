//
//  CLQueueNode.cpp
//  CL_Queue
//
//  Created by Katie Trombetta on 10/30/20.
//

#include "CLQueueNode.hpp"
class Request;

CLQueueNode::CLQueueNode(Request *req): _request(req), _next(nullptr), _prev(nullptr) {}



CLQueueNode *CLQueueNode::next() {
    return _next;
}



void CLQueueNode::next(CLQueueNode *node) {
    _next = node;
}




CLQueueNode *CLQueueNode::prev(){
    return _prev;
}





void CLQueueNode::prev(CLQueueNode *node){
    _prev = node;
}



Request *CLQueueNode::request() {
    return _request;
}


