//
//  main.cpp
//  CL_Queue
//
//  Created by Katie Trombetta on 10/30/20.
//

#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include "../CommonFiles/Request.hpp"
#include "CLQueue.hpp"
#include <tuple>

void addTest5(CLQueue *q, Request *r, int t, int s);
std::tuple<int,int> getTest5(CLQueue *q, int t, int s);

CLQueue *createCLQueueFromInputFile( int argc, char *argv[] ) {
    std::cout << "CL -- Main function.\n";

    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }
    auto *queue = new CLQueue();

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, 0, 0);
    }

    return queue;
}






Request *generateRandomRequest() {
    // Randomly generates and returns a request. The time of each
    // subsequent request is larger than that of the previous one.

    static int currentTime = 0;

    enum {
        MAX_TIME_INTERVAL = 100,
        MAX_TRACK = 12,
        MAX_SECTOR = 30
    };

    currentTime += (int) (random() % MAX_TIME_INTERVAL + 1);   // advance current time by at most 100 msecs
    int track = (int) (random() % MAX_TRACK);
    int sector = (int) (random() % MAX_SECTOR);

    return new Request(currentTime, track, sector);
}







enum Actions {
    ADD_A_REQUEST = 0,
    GET_A_REQUEST = 5,
    INSPECT_QUEUE = 9,
};



const int ACTION_RANGE = 10;






CLQueue *createCLQueueFromRandomValues(int numRequestsToGenerate, int numTestsToRun) {
    auto *queue = new CLQueue();
    srandom(getpid());

    int numRequestsGenerated = 0, numTestsRun = 0, numRequestsInTheQueue = 0;
    int currentTrack = 0, currentSector = 0;
    double previousTimeStamp = 0.0;

    while ( numTestsRun < numTestsToRun ) {
        Request *request = nullptr;
        int actionRange = (int) (random() % ACTION_RANGE);
        if (numRequestsGenerated < numRequestsToGenerate && actionRange >= ADD_A_REQUEST && actionRange < GET_A_REQUEST) {
            std::cout << "Testing addRequest\n";
            request = generateRandomRequest();
            std::cout << "Adding the following request to the CLQueue.\n";
            request->print();
            queue->addRequest(request, currentTrack, currentSector);
            numRequestsGenerated++;
            numRequestsInTheQueue++;
        } else if (actionRange < INSPECT_QUEUE) {
            std::cout << "Testing getRequest\n";
            if (queue->empty())
                std::cout << "CLQueue is empty.\n";
            else {
                request = queue->getRequest();
                std::cout << "Removed the following request from the CLQueue via getRequest.\n";
                request->print();
                previousTimeStamp = request->time();
                delete request; // We do not have a use for this request any longer.
                currentTrack = request->track();
                currentSector = request->sector();
                numRequestsInTheQueue--;
            }
        } else {
            std::cout << "Testing whether the queue is empty or not.\n";
            if (numRequestsInTheQueue != 0 && queue->empty()) {
                std::cout << "CLQueue::empty() returns true, but the queue should have " <<
                          numRequestsInTheQueue << " elements in it." << std::endl;
                exit(1);
            } else if (numRequestsInTheQueue == 0 && !queue->empty()) {
                std::cout << "CLQueue::empty() returns false, but the queue should be empty." << std::endl;
                exit(1);
            }
        }
        numTestsRun++;
    }

    while(! queue->empty() ) {
        std::cout << "Removed the following request from the CLQueue after having tested the queue.\n";
        auto *request = queue->getRequest();
        request->print();
        delete request;
        numRequestsInTheQueue--;
    }

    if( numRequestsInTheQueue > 0 ) {
        std::cout << "In the process of testing, the CLQueue lost " << numRequestsInTheQueue <<
            ". This means the queue contains a bug!\n";
    } else if(numRequestsInTheQueue < 0) {
        std::cout << "In the process of testing, the CLQueue did not remove " << -numRequestsInTheQueue <<
                  "requests as a result of getRequest having been called. This means the queue contains a bug!\n";
    }

    return queue;
}




int main(int argc, char *argv[]) {

    const int randomTest = true;
    CLQueue *queue = nullptr;

    if( randomTest )
        queue = createCLQueueFromRandomValues(200, 100);
    else
       queue = createCLQueueFromInputFile(argc, argv);

    queue->print();
    delete queue;



    /*
     BEGIN MANUAL TESTING OF FCFS QUEUE
     */
    
    Request *r1 = new Request(0, 1, 1);
    Request *r2 = new Request(1, 9, 1);
    Request *r3 = new Request(2, 8, 1);
    Request *r4 = new Request(3, 1, 1);
    Request *r5 = new Request(4, 1, 1);
    Request *r6 = new Request(5, 1, 1);
    Request *r7 = new Request(6, 1, 1);
    Request *r8 = new Request(7, 1, 1);
    Request *r9 = new Request(8, 1, 1);
    
    
    
    std::cout << "\n\n**************************************\n";
    std::cout << "Begin manual testing of the FCFS Queue\n";
    std::cout << "**************************************\n\n";

    /* the crwheaddtrack and the crwheadsector start at track 0, sector 0*/
    std::tuple<int,int> tup = std::make_tuple(0,0);
    std::tuple<int,int> pair;

    auto *q = new CLQueue();

    addTest5(q, r1, 0, 0);
    pair = getTest5(q, std::get<0>(tup), std::get<1>(tup));
    addTest5(q, r2, std::get<0>(pair), std::get<1>(pair));
    addTest5(q, r3, std::get<0>(pair), std::get<1>(pair));
    pair = getTest5(q, std::get<0>(pair), std::get<1>(pair));
    pair = getTest5(q, std::get<0>(pair), std::get<1>(pair));
    addTest5(q, r4, std::get<0>(pair), std::get<1>(pair));
    addTest5(q, r5, std::get<0>(pair), std::get<1>(pair));
    addTest5(q, r6, std::get<0>(pair), std::get<1>(pair));
    pair = getTest5(q, std::get<0>(pair), std::get<1>(pair));
    addTest5(q, r7, std::get<0>(pair), std::get<1>(pair));
    pair = getTest5(q, std::get<0>(pair), std::get<1>(pair));
    pair = getTest5(q, std::get<0>(pair), std::get<1>(pair));

    
    
    return 0;
}





void addTest5(CLQueue *q, Request *r, int t, int s){
    std::cout << "Adding request: ";
    r->print();
    q->addRequest(r, t, s);
    std::cout << "Printing queue:\n";
    q->print();
    std::cout << std::endl;
}

std::tuple<int,int> getTest5(CLQueue *q, int t, int s){
    std::cout << "Getting request -> Printing queue before get:\n";
    q->print();
    std::cout << "Request we're getting: ";
    Request *gotRequest = q->getRequest();
    gotRequest->print();
    std::cout << "Printing queue after get: \n";
    q->print();
    std::cout << std::endl;
    
    std::tuple<int,int> tuple = std::make_tuple(gotRequest->track(), gotRequest->sector());
    return tuple;
}
