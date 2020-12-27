//
//  main.cpp
//  DIskSim
//
//  Created by Katie Trombetta on 11/10/20.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>

#include "EventQueue.hpp"
#include "EventNode.hpp"
#include "RequestEvent.hpp"
#include "TimerEvent.hpp"
#include "DiskDoneEvent.hpp"

#include "Queue.hpp"
#include "Request.hpp"
#include "Disk.hpp"
//#include "FCFSQueue.hpp"
#include "../FCFS_Queue/FCFSQueueNode.hpp"
#include "../ST_Queue/STQueue.hpp"
#include "../PU_Queue/PUQueue.hpp"
#include "../LU_QUEUE/LUQueue.hpp"
#include "../CL_Queue/CLQueue.hpp"


void writeTimerOutputFile(std::vector<std::vector<int>>numWaitingData, std::vector<std::string> waitQueueName){
    std::cout << std::endl << std::endl;
    std::ofstream outputStream;
    outputStream.open("../TIMER_output", std::ios::out);
    if( ! outputStream.is_open()) {
        std::cout << "Unable top open " << "../TIMER_output" << ". Terminating...";
        perror("Error when attempting to open the output file.");
        exit(5);
    }
    outputStream << "TIMER Report\r\n" << "Time" << std::setw(10) << waitQueueName[0] << std::setw(10) << waitQueueName[1] << std::setw(10) << waitQueueName[2] << std::setw(10) << waitQueueName[3] << std::setw(10) << waitQueueName[4] << "\r\n";
    
    double time = 50.00;
    for (int d = 0; d < numWaitingData[0].size(); d++){ // d < number of timer data for a queue
        outputStream << time << std::setw(10);
        for (int q = 0; q < numWaitingData.size(); q++){ // q < 5
            outputStream << numWaitingData[q][d] << std::setw(10);
        }
        outputStream << "\r\n";
        time += 50.00;
    }
    
    outputStream.close();
    std::ifstream inputStream;
    inputStream.open("../TIMER_output", std::ios::in);
    if ( ! inputStream.is_open()){
        std::cout << "ERROR opening " << "../TIMER_output" << " with inputstream." << std::endl;
        exit(4);
    }
    std::string line;
    while (getline(inputStream, line)){
        std::cout << line;
    }
}






void writeOutputSummaryFile(std::vector<std::vector<double>> summaryQueue, std::vector<std::string> waitQueueName){
    std::cout << std::endl << std::endl;
    std::ofstream outputStream;
    outputStream.open("../SUMMARY_output", std::ios::out);
    if( ! outputStream.is_open()) {
        std::cout << "Unable top open " << "../SUMMARY_output" << ". Terminating...";
        perror("Error when attempting to open the output file.");
        exit(2);
    }
     outputStream << "SUMMARY Report\r\n" << std::setw(5) << "Name" << std::setw(22) << "TimeInSystem" << std::setw(19) << "WaitTime" << std::setw(23) << "ServiceTime" << std::setw(17) << "NumInQue\r\n" << std::setw(14) << "Min" << std::setw(6) << "Max" << std::setw(6) << "Avg" << std::setw(10) << "Min" << std::setw(6) << "Max" << std::setw(6) << "Avg" << std::setw(9) << "Min" << std::setw(5) << "Max" << std::setw(6) << "Avg" << std::setw(11) << "Max" << std::setw(6) << "Avg\r\n";
    
    for (int i = 0; i < summaryQueue.size(); i++){
        outputStream << std::setw(2) << waitQueueName[i];
        if (i == 1)
            outputStream <<  std::setw(8);
        else if(i == 2)
            outputStream << std::setw(7);
        else if (i == 4){
            outputStream << std::setw(8);
        }
        else{
            outputStream << std::setw(10);
        }
        for (int d = 0; d < summaryQueue[i].size(); d++){
            outputStream << summaryQueue[i][d] << std::setw(7);
        }
        outputStream << "\r\n";
    }
    
    outputStream.close();
    std::ifstream inputStream;
    inputStream.open("../SUMMARY_output", std::ios::in);
    if ( ! inputStream.is_open()){
        std::cout << "ERROR opening " << "../SUMMARY_output" << " with inputstream." << std::endl;
        exit(4);
    }
    std::string line;
    while (getline(inputStream, line)){
        std::cout << line;
    }
}







std::vector<double> writeOutputQueueFile(std::vector<std::vector<std::vector<double>>> &allQueueData, int queueTypeIdx, std::ofstream &outputStream, std::string queueName, std::string queueFileName, std::vector<std::vector<int>> &numInQ){
    
    outputStream.open(queueFileName, std::ios::out);
    if( ! outputStream.is_open()) {
        std::cout << "Unable top open " << queueFileName << ". Terminating...";
        perror("Error when attempting to open the output file.");
        exit(2);
    }
    
    outputStream << "\r\n" << queueName << " REPORT\r\n";
    outputStream << std::setw(2) << "#" << std::setw(10) << "Trac" << std::setw(10) << "Sec" << std::setw(10) << "Entr" << std::setw(10) << "Init" << std::setw(10) << "Comp" << std::setw(10) << "Wait" << std::setw(10) << "Serv" << std::setw(10) << "    TmInSys \r\n";
    
    std::vector<double> summaryStats;
    double minTmInSys, maxTmInSys, minWait, maxWait, minServ, maxServ, maxNumInQ;
    double avgTmInSys = 0, avgWait = 0, avgServ = 0, avgNumInQ = 0;
    
    minTmInSys = allQueueData[queueTypeIdx][0][7];
    maxTmInSys = allQueueData[queueTypeIdx][0][7];
    minWait = allQueueData[queueTypeIdx][0][5];
    maxWait = allQueueData[queueTypeIdx][0][5];
    minServ = allQueueData[queueTypeIdx][0][6];
    maxServ = allQueueData[queueTypeIdx][0][6];
    maxNumInQ = numInQ[queueTypeIdx][0];
    
    for(int q = 1; q < allQueueData[queueTypeIdx].size(); q++){
        outputStream << q << std::setw(10);
        
        if (allQueueData[queueTypeIdx][q][7] < minTmInSys)
            minTmInSys = allQueueData[queueTypeIdx][q][7];
        if (allQueueData[queueTypeIdx][q][7] > maxTmInSys)
            maxTmInSys = allQueueData[queueTypeIdx][q][7];
        
        if (allQueueData[queueTypeIdx][q][5] < minWait)
            minWait = allQueueData[queueTypeIdx][q][5];
        if (allQueueData[queueTypeIdx][q][5] > maxWait)
            maxWait = allQueueData[queueTypeIdx][q][5];
        
        if (allQueueData[queueTypeIdx][q][6] < minServ)
            minServ = allQueueData[queueTypeIdx][q][6];
        if (allQueueData[queueTypeIdx][q][6] > maxServ)
            maxServ = allQueueData[queueTypeIdx][q][6];
            
        for (int d = 0; d < allQueueData[queueTypeIdx][q - 1].size(); d++){
            outputStream << allQueueData[queueTypeIdx][q - 1][d] << std::setw(10);
            if (d == 7) // tminsys
                avgTmInSys += allQueueData[queueTypeIdx][q - 1][d];
            if (d == 5) // wait
                avgWait += allQueueData[queueTypeIdx][q - 1][d];
            if (d == 6) // serv
                avgServ += allQueueData[queueTypeIdx][q - 1][d];
        }
        outputStream << "\r\n";
    }
    for (int i  = 0; i < numInQ[queueTypeIdx].size(); i++){
        avgNumInQ += numInQ[queueTypeIdx][i];
        if (numInQ[queueTypeIdx][i] > maxNumInQ)
            maxNumInQ = numInQ[queueTypeIdx][i];
    }
    
    avgTmInSys /= (allQueueData[queueTypeIdx].size() - 1);
    avgWait /= (allQueueData[queueTypeIdx].size() - 1);
    avgServ /= (allQueueData[queueTypeIdx].size() - 1);
    avgNumInQ /= (numInQ[queueTypeIdx].size());
    
    summaryStats.push_back(minTmInSys);
    summaryStats.push_back(maxTmInSys);
    summaryStats.push_back(avgTmInSys);
    summaryStats.push_back(minWait);
    summaryStats.push_back(maxWait);
    summaryStats.push_back(avgWait);
    summaryStats.push_back(minServ);
    summaryStats.push_back(maxServ);
    summaryStats.push_back(avgServ);
    summaryStats.push_back(maxNumInQ);
    summaryStats.push_back(avgNumInQ);

    outputStream.close();
    std::ifstream inputStream;
    inputStream.open(queueFileName, std::ios::in);
    if ( ! inputStream.is_open()){
        std::cout << "ERROR opening " << queueName << "/" << queueFileName << " with inputstream." << std::endl;
        exit(3);
    }
    std::string line;
    while (getline(inputStream, line)){
        std::cout << line;
    }
    
    return summaryStats;
}







RequestEvent *generateRandomRequest() {
    static int currentTime = 0;

    enum {
        MAX_TIME_INTERVAL = 50,
        MAX_TRACK = 100,
        MAX_SECTOR = 30
    };

    currentTime += (int) (random() % MAX_TIME_INTERVAL + 1);   // advance current time by at most 100 msecs
    int track = (int) (random() % MAX_TRACK);
    int sector = (int) (random() % MAX_SECTOR);

    return new RequestEvent(currentTime, track, sector);
}

enum Actions {
    ADD_A_REQUEST = 0,
    GET_A_REQUEST = 5,
    INSPECT_QUEUE = 9,
};




EventQueue *createEventQueue(int numRequestsToGenerate, std::vector<Disk *> &disks, std::vector<std::vector<int>> &numWaitingData, std::vector<std::vector<std::vector<double>>> &indivQueueData, bool randomTest, int argc, char *argv[]) {
    
    auto *eQueue = new EventQueue();
    srandom(getpid());
    double curTime = 0.0;
    TimerEvent *timerEvent = new TimerEvent(50.0);
    int track = 0, sector = 0;
    double fileTime = 0.0;
    std::ifstream inputStream;
    std::string line;
    RequestEvent* request = nullptr;
    double sectorDist = 0.0;

    if (randomTest)
        request = generateRandomRequest();
    else{
        if( argc != 2) {
            std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
            exit(1);
        }
        inputStream.open(argv[1], std::ios::in);
        if( ! inputStream.is_open()) {
            std::cout << "Unable top open " << argv[1] << ". Terminating...";
            perror("Error when attempting to open the input file.");
            exit(1);
        }
        if (inputStream){
            inputStream >> fileTime >> track >> sector;
            request = new RequestEvent(fileTime, track, sector);
        }
    }
    eQueue->addRequestEvent(request, 0, 0);
    eQueue->addTimerEvent(timerEvent, 0, 0);
    int numRequestsGenerated = 1;

    
    while (!eQueue->empty()){
        if (eQueue->getHead()->isRequestEvent()){
            //processRequestEvent
            RequestEvent *rEvent = eQueue->getRequestEvent();
            Request *req = new Request(rEvent->time(), rEvent->track(), rEvent->sector());
            curTime = rEvent->time();
            
            for(int i = 0; i < disks.size(); i++){
                
                std::vector<double> requestData;
                requestData.push_back(req->track()); // Trac
                requestData.push_back(req->sector()); //Sec
                requestData.push_back(req->time()); // Entr
                indivQueueData[i].push_back(requestData);

                if (disks[i]->idle()){
                    disks[i]->idle(false);
                    sectorDist = req->sector() - disks[i]->getCurSector() >= 0 ? req->sector() - disks[i]->getCurSector() : 29 - disks[i]->getCurSector() + req->sector();
                    DiskDoneEvent *ddEvent = new DiskDoneEvent(curTime, curTime, (curTime + ((abs(req->track() - disks[i]->getCurTrack()) * 3.0) + (sectorDist * 0.1) + 0.1) ), disks[i]->getType());
                    disks[i]->setCurTrack(rEvent->track());
                    disks[i]->setCurSector(rEvent->sector() + 1);
                    eQueue->addDiskDoneEvent(ddEvent, disks[i]->getCurTrack(), disks[i]->getCurSector());
                }
                
                else{
                    disks[i]->getQueue()->addRequest(req, disks[i]->getCurTrack(), disks[i]->getCurSector());
                    disks[i]->setNumWaiting(disks[i]->getNumWaiting() + 1);
                }
            }
            
            if (randomTest){
                if (numRequestsGenerated < numRequestsToGenerate){
                    RequestEvent *reqEvent = generateRandomRequest();
                    numRequestsGenerated++;
                    eQueue->addRequestEvent(reqEvent, reqEvent->track(), reqEvent->sector());
                }
            }
            else{
                if (inputStream.peek() != -1){
                    inputStream >> fileTime >> track >> sector;
                    RequestEvent *reqEvent = new RequestEvent(fileTime, track, sector);
                    eQueue->addRequestEvent(reqEvent, reqEvent->track(), reqEvent->sector());
                }
            }
        }
        
        
        else if (eQueue->getHead()->isDiskDoneEvent()){
            
            DiskDoneEvent *ddEvent = eQueue->getDiskDoneEvent();
            int queueType = ddEvent->getQueueType() - 1;
            auto *disk = disks[queueType];

            int vectorIdx = 0;
            for (std::vector<double> ddRequestData : indivQueueData[queueType] ){
                if (ddRequestData[2] == ddEvent->getEntrTime() && ddRequestData.size() < 8){
                    indivQueueData[queueType][vectorIdx].push_back(ddEvent->getInitTime()); // 3 Init
                    indivQueueData[queueType][vectorIdx].push_back(ddEvent->time()); // 4 Comp
                    indivQueueData[queueType][vectorIdx].push_back(indivQueueData[queueType][vectorIdx][3] - indivQueueData[queueType][vectorIdx][2]); //5 Wait (Init - Entr)
                    indivQueueData[queueType][vectorIdx].push_back(indivQueueData[queueType][vectorIdx][4] - indivQueueData[queueType][vectorIdx][3]); //6 Serv (Comp - Init)
                    indivQueueData[queueType][vectorIdx].push_back(indivQueueData[queueType][vectorIdx][4] - indivQueueData[queueType][vectorIdx][2]); //7 TmInSys (Comp - Entr)
                    break;
                }
                vectorIdx++;
            }
            curTime = ddEvent->time();
            
            if (!disk->getQueue()->empty()){
                Request *req = disk->getQueue()->getRequest();
                disk->setNumWaiting(disk->getNumWaiting() - 1);
                sectorDist = req->sector() - disk->getCurSector() >= 0 ? req->sector() - disk->getCurSector() : 29 - disk->getCurSector() + req->sector();
                if (req->time() > curTime){
                    ddEvent = new DiskDoneEvent(req->time(), req->time(), (req->time() + ((abs(req->track() - disk->getCurTrack()) * 3.0) + (sectorDist * 0.1) + 0.1) ), disk->getType());
                }
                else{
                    ddEvent = new DiskDoneEvent(req->time(), curTime, (curTime + ((abs(req->track() - disk->getCurTrack()) * 3.0) + (sectorDist * 0.1) + 0.1) ), disk->getType());
                }
                disk->setCurTrack(req->track());
                disk->setCurSector(req->sector() + 1);
                eQueue->addDiskDoneEvent(ddEvent, disk->getCurTrack(), disk->getCurSector());
            }
            else{
                disk->idle(true);
            }
        }
        
        
        else {  /* ************** the next request in the eQueue is a timerEvent *************** */
            TimerEvent *tEvent = eQueue->getTimerEvent();
            curTime = tEvent->time();
            
            for (int i = 0; i < numWaitingData.size(); i++){
                numWaitingData[i].push_back(disks[i]->getNumWaiting());
            }
            if (!eQueue->empty()){
                TimerEvent *timerEvent = new TimerEvent(curTime + 50.0);
                eQueue->addTimerEvent(timerEvent, 0, 0);
            }
        }
    }
    
    return eQueue;
}



int main(int argc, char *argv[]){
    const int randomTest = false;
    EventQueue *eQueue = nullptr;
    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();
    Queue *pu = new PUQueue();
    Queue *lu = new LUQueue();
    Queue *cl = new CLQueue();

    enum {FCFS = 1, ST = 2, PU = 3, LU = 4, CL = 5};
    
    Disk *fcfsDisk = new Disk(fcfs, 1);
    Disk *stDisk = new Disk(st, 2);
    Disk *puDisk = new Disk(pu, 3);
    Disk *luDisk = new Disk(lu, 4);
    Disk *clDisk = new Disk(cl, 5);

    std::vector<Disk *> disks;
    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);
    disks.push_back(puDisk);
    disks.push_back(luDisk);
    disks.push_back(clDisk);
    
    std::vector<std::vector<int>> numWaitingData{ {},{},{},{},{} };
    std::vector<std::vector<std::vector<double>>> indivQueueData{ {},{},{},{},{} };
    std::vector<std::vector<double>> summaryQueue{};
    std::vector<std::string> waitQueueFileName{"../FCFS_output", "../STRACK_output", "../PICKUP_output", "../LOOK_output", "../CLOOK_output"};
    std::vector<std::string> waitQueueName{"FCFS", "STRACK", "PICK_UP", "LOOK", "C_LOOK"};

    eQueue = createEventQueue(10, disks, numWaitingData, indivQueueData, randomTest, argc, argv);
    eQueue->print();
    delete eQueue;

    for (int i = 0; i < waitQueueFileName.size(); i++){
        std::ofstream outputStream;
        std::vector<double> curQueueSummary = writeOutputQueueFile(indivQueueData, i, outputStream, waitQueueName[i], waitQueueFileName[i], numWaitingData);
        summaryQueue.push_back(curQueueSummary);
    }
    
    //now we have the summary queue full.
    writeOutputSummaryFile(summaryQueue, waitQueueName);
    writeTimerOutputFile(numWaitingData, waitQueueName);

    
    return 0;
}
