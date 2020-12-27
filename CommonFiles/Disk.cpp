//
//  Disk.cpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/11/20.
//

#include "Disk.hpp"


Disk::Disk(Queue* queue, int type){
    this->queue = queue;
    this->type = type;
    idle(true);
}


void Disk::idle(bool idle){
    _idle = idle;
}



bool Disk::idle(){
    return _idle;
}


Queue* Disk::getQueue(){
    return queue;
}




int Disk::getType(){
    return type;
}





void Disk::setCurTrack(int curTrack){
    _curTrack  = curTrack;
}





void Disk::setCurSector(int curSector){
    _curSector = curSector;
}





int Disk::getCurTrack(){
    return _curTrack;
}





int Disk::getCurSector(){
    return _curSector;
}




void Disk::setNumWaiting(int numWaiting){
    _numWaiting = numWaiting;
}



int Disk::getNumWaiting(){
    return _numWaiting;
}




//initialize this track nd sector

// we need the number of times that we have interuppted, having been given a timer event

// when we pull a timer event form the event queue, tell each disk we have a timer event

//ask for the number of entries in each quueue so that we can write it in our output file, in main

// then the disk itself keeps track of how many times it has received a process timer, and uses a cumulative varibale to store the number of entries in its queue so we can divide by the number of times interrupted to get the average number of entires in it queue.




