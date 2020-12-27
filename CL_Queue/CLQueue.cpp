//
//  CLQueue.cpp
//  CL_Queue
//
//  Created by Katie Trombetta on 10/30/20.
//

#include "CLQueue.hpp"
#include "../CommonFiles/Request.hpp"



void CLQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    CLQueueNode *rNode = new CLQueueNode(request);

    if (empty())
        head = tail = rNode;
    else{ // not empty
        bool inner = request->track() >= cRWHeadTrack;
        CLQueueNode *curNode = head;
        if (flip == nullptr){ // all inner or all outer
            if (inner){
                if (head->request()->track() < cRWHeadTrack){
                    insertAsHead(rNode);
                    flip = head->next();    // point flip at head->next
                }
                else{
                    while(curNode != nullptr && request->track() >= curNode->request()->track())
                        curNode = curNode->next();
                    if (curNode != nullptr){
                        if (curNode == head)
                            insertAsHead(rNode);
                        else
                            insertBetween(rNode, curNode);
                    }
                    else
                        insertAsTail(rNode);
                }
            }
            else{
                if (head->request()->track() < cRWHeadTrack){ // also outer
                    while(curNode != nullptr && request->track() >= curNode->request()->track()){
                        curNode = curNode->next();
                    }
                    if(curNode != nullptr){
                        if (curNode == head)
                            insertAsHead(rNode);
                        else
                            insertBetween(rNode, curNode);
                    }
                    else
                        insertAsTail(rNode);
                }
                else{ // direction is outer but all the nodes are inner
                    insertAsTail(rNode);
                    flip = tail; //point flip at tail
                }
                
            }
        }
        else{ // flip is not nullptr, it is pointing at the first outer node after inner nodes
            if(inner){
                while(curNode != flip && request->track() >= curNode->request()->track()){
                    curNode = curNode->next();
                }
                if (curNode != flip){
                    if (curNode == head)
                        insertAsHead(rNode);
                    else
                        insertBetween(rNode, curNode);
                }
                else
                    insertBetween(rNode, curNode);
            }
            else{
                curNode = flip;
                while(curNode != nullptr && request->track() >= curNode->request()->track()){
                    curNode = curNode->next();
                }
                if (curNode != nullptr){
                    if (curNode == flip){
                        insertBetween(rNode, curNode);
                        flip = rNode; // point flip at this node
                    }
                    else
                        insertBetween(rNode, curNode);
                }
                else
                    insertAsTail(rNode);
            }
        }
    }
}






Request *CLQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling CLQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    CLQueueNode *clNode = head;
    Request *request = clNode->request();

    head = head->next();
    if (head == nullptr){
        tail = nullptr;
    }
    else{
        head->prev(nullptr);
        if (flip == head)
            flip = nullptr;
    }
    delete clNode;
    return request;
}






bool CLQueue::empty() {
    return head == nullptr;
}






void CLQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}






CLQueue::~CLQueue() {
    while( head != nullptr ) {
        CLQueueNode *node = head;
        head = node->next();
        delete node;
    }
}






void CLQueue::insertAsHead(CLQueueNode *rNode){
    rNode->next(head); // insert track as the head
    head->prev(rNode);
    head = rNode;
}






void CLQueue::insertAsTail(CLQueueNode *rNode){
    tail->next(rNode); //insert as tail
    rNode->prev(tail);
    tail = rNode;
}






void CLQueue::insertBetween(CLQueueNode *rNode, CLQueueNode *curNode){
    curNode->prev()->next(rNode);  //insert in between curNode->prev and curNode
    rNode->prev(curNode->prev());
    rNode->next(curNode);
    curNode->prev(rNode);
}
