//
//  RequestEvent.cpp
//  CommonFiles
//
//  Created by Katie Trombetta on 11/10/20.
//

#include "RequestEvent.hpp"

RequestEvent::RequestEvent(double rTime, int rTrack, int rSector): _time(rTime), _track(rTrack), _sector(rSector){}



int RequestEvent::track(){
    return _track;
}



int RequestEvent::sector(){
    return _sector;
}



double RequestEvent::time(){
    return _time;
}



void RequestEvent::print(){
    std::cout << time() << "\t" << track() << "\t" << sector() << std::endl;
}
