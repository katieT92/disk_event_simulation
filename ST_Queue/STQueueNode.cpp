//
//  STQueueNode.cpp
//  ST_Queue
//
//  Created by Katie Trombetta on 10/25/20.
//
#include "../FCFS_Queue/FCFSQueue.hpp"

#include "STQueueNode.hpp"
#include "../CommonFiles/Request.hpp"
//class Request;

STQueueNode::STQueueNode(Request *req, int cRWHeadTrack, int cRWHeadSector){
    _queue = new FCFSQueue();
    _queue->addRequest(req, cRWHeadTrack, cRWHeadSector);
    _next = nullptr;
    _track = req->track();
}



STQueueNode *STQueueNode::next() {
    return _next;
}



void STQueueNode::next(STQueueNode *node) {
    _next = node;
}



Request *STQueueNode::request() {
    return _queue->getRequest();
}



int STQueueNode::track(){
    return _track;
}




void STQueueNode::attach_track(Request *req, int cRWHeadTrack, int cRWHeadSector){
    _queue->addRequest(req, cRWHeadTrack, cRWHeadSector);
}





FCFSQueue* STQueueNode::getFCFSQueue(){
    return _queue;
}


