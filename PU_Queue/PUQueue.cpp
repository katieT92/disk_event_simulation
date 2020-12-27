//
//  PUQueue.cpp
//  PU_Queue
//
//  Created by Katie Trombetta on 10/28/20.
//

#include "PUQueue.hpp"
#include "../CommonFiles/Request.hpp"

void PUQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    PUQueueNode *rNode = new PUQueueNode(request);
    if ( empty() )
        head = tail = rNode;
    else {
        PUQueueNode *nextNode = head;
        Request *RWRequest = new Request(0, cRWHeadTrack, 0);
        PUQueueNode *curNode = new PUQueueNode(RWRequest);
        curNode->next(nextNode);
        bool added = false;
        
        while (nextNode && !added){
            int curTrack = curNode->request()->track();
            int nextTrack = nextNode->request()->track();
            if (curTrack < nextTrack){
                if (request->track() >= curTrack && request->track() < nextTrack){ // its in range
                    rNode->next(nextNode);
                    if (nextNode == head)
                        head = rNode;
                    else
                        curNode->next(rNode);
                    added = true;
                }
                else{
                    curNode = curNode->next();
                    nextNode = nextNode->next();
                }
            }
            else if (curTrack > nextTrack){
                if (request->track() <= curTrack && request->track() > nextTrack){
                    rNode->next(nextNode);
                    if (nextNode == head)
                        head = rNode;
                    else
                        curNode->next(rNode);
                    added = true;
                }
                else{
                    curNode = curNode->next();
                    nextNode = nextNode->next();
                }
            }
            else {
                curNode = curNode->next();
                nextNode = nextNode->next();
            }
        }
        if (!added){
            curNode->next(rNode);
            tail = rNode;
        }
    }
}





Request *PUQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling PUQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    PUQueueNode *puNode = head;
    Request *request = puNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete puNode;
    return request;
}






bool PUQueue::empty() {
    return head == nullptr;
}






void PUQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}







PUQueue::~PUQueue() {
    while( head != nullptr ) {
        PUQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
