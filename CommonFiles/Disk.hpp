//
//  Disk.hpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/11/20.
//

#ifndef Disk_hpp
#define Disk_hpp
#include <string>
#include "Queue.hpp"

class Disk {
public:
    Disk(Queue* queue, int type);
    void idle(bool idle);
    bool idle();
    Queue *getQueue();
    int getType();
    void setCurTrack(int curTrack);
    void setCurSector(int curSector);
    int getCurTrack();
    int getCurSector();
    void setNumWaiting(int numWaiting);
    int getNumWaiting();

private:
    Queue *queue;
    int type;
    bool _idle = true;
    int _curTrack = 0;
    int _curSector = 0;
    int _numWaiting = 0;
};

#endif /* Disk_hpp */
