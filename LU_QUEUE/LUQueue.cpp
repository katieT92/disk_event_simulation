//
//  LUQueue.cpp
//  LU_QUEUE
//
//  Created by Katie Trombetta on 10/30/20.
//

#include "LUQueue.hpp"
#include "../CommonFiles/Request.hpp"

void LUQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    LUQueueNode *rNode;
    bool added = false;
    if ( empty() ){
        rNode = new LUQueueNode(request, cRWHeadTrack, cRWHeadSector, request->track() >= cRWHeadTrack ? 1 : 0);
        head = tail = rNode;
        added = true;
    }
    else{
        if (head->direction() == 1){
            if (request->track() >= cRWHeadTrack){
                head->attach_track(request, cRWHeadTrack, cRWHeadSector);
                added = true;
            }
        }
        else{
            if (request->track() <= cRWHeadTrack){
                head->attach_track(request, cRWHeadTrack, cRWHeadSector);
                added = true;
            }
        }
        if (!added){
            if (!head->next()){
                rNode = new LUQueueNode(request, cRWHeadTrack, cRWHeadSector, head->direction() == 1? 0 : 1);
                head->next(rNode);
                tail = rNode;
            }
            else
                head->next()->attach_track(request, cRWHeadTrack, cRWHeadSector);
        }
    }
}



Request *LUQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling LUQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    LUQueueNode *luNode = head;
    Request *request = luNode->request();
    if (head != nullptr && head->getPUQueue()->empty()){
        head = head->next();
        delete luNode->getPUQueue();
    }
    if (head == nullptr){
        tail = nullptr;
    }
    //delete LUNode;
    return request;
}






bool LUQueue::empty() {
    return head == nullptr;
}






void LUQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->getPUQueue()->print();
}







LUQueue::~LUQueue() {
    while( head != nullptr ) {
        LUQueueNode *node = head;
        head = node->next();
        delete node;
    }
}

