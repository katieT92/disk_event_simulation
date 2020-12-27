//
//  RequestEvent.hpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#ifndef RequestEvent_hpp
#define RequestEvent_hpp

#include <iostream>

class RequestEvent {
public:
    RequestEvent(double rTime, int rTrack, int rSector);
    int track();
    int sector();
    double time();
    void print();
    
private:
    double _time;
    int _track, _sector;
};

#endif /* RequestEvent_hpp */
