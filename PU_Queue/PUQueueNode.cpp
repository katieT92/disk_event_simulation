//
//  PUQueueNode.cpp
//  PU_Queue
//
//  Created by Katie Trombetta on 10/28/20.
//

#include "PUQueueNode.hpp"


class Request;

PUQueueNode::PUQueueNode(Request *req) : _request(req), _next(nullptr) {}

PUQueueNode *PUQueueNode::next() {
    return _next;
}

void PUQueueNode::next(PUQueueNode *node) {
    _next = node;
}

Request *PUQueueNode::request() {
    return _request;
}
