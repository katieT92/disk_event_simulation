//
//  ST_Queue.cpp
//  ST_Queue
//
//  Created by Katie Trombetta on 10/25/20.
//
#include "../FCFS_Queue/FCFSQueue.hpp"

#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"

void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode *rNode;
    if( empty() ) {
        rNode = new STQueueNode(request, cRWHeadTrack, cRWHeadSector);
        head = tail = rNode;
    }
    else {
        STQueueNode *curNode = head;
        if (request->track() == cRWHeadTrack){
            if (request->track() != curNode->track()){
                rNode = new STQueueNode(request, cRWHeadTrack, cRWHeadSector);
                rNode->next(head);
                head = rNode;
            }
            else{
                head->attach_track(request, cRWHeadTrack, cRWHeadSector);
            }
        }
        else{
            while (curNode != nullptr && request->track() != curNode->track()){
                curNode = curNode->next();
            }
            if (curNode == nullptr){
                rNode = new STQueueNode(request, cRWHeadTrack, cRWHeadSector);
                tail->next(rNode);
                tail = rNode;
            }
            else{
                curNode->attach_track(request, cRWHeadTrack, cRWHeadSector);
            }
        }
    }
}



Request *STQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    STQueueNode *stNode = head;
    Request *request = stNode->request();
    if (head != nullptr && head->getFCFSQueue()->empty()){
        head = head->next();
        delete stNode->getFCFSQueue();
    }
    if (head == nullptr){
        tail = nullptr;
    }
    return request;
}






bool STQueue::empty() {
    return head == nullptr;
}






void STQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->getFCFSQueue()->print();
}







STQueue::~STQueue() {
    while( head != nullptr ) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
