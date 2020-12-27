README.txt
Project5


Created by Katie Trombetta on 11/5/20.
Copyright © 2020 Katie Trombetta. All rights reserved.


Author
Katie Trombetta


Help Received
N/A


Help Given
Nick Ivanov: I helped Nick with the general logic flow of Part 2 of this project.


Website Code
N/A


Project Features Omitted
Testing was performed on all queues but not as thoroughly as I wanted.



COMPILING INSTRUCTIONS

Whole Program:
g++ -std=c++17 CommonFiles/EventQueue.cpp CommonFiles/EventNode.cpp CommonFiles/Request.cpp CommonFiles/Disk.cpp CommonFiles/TimerEvent.cpp CommonFiles/RequestEvent.cpp CommonFiles/DiskDoneEvent.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp PU_Queue/PUQueue.cpp PU_Queue/PUQueueNode.cpp LU_QUEUE/LUQueue.cpp LU_QUEUE/LUQueueNode.cpp CL_Queue/CLQueue.cpp CL_Queue/CLQueueNode.cpp CommonFiles/main.cpp -o cf.x

FCFS:
g++ -std=c++17 CommonFiles/Request.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp FCFS_Queue/main.cpp -o fcfs.x


ST:
g++ -std=c++17 CommonFiles/Request.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp ST_Queue/main.cpp -o st.x


PU:
g++ -std=c++17 CommonFiles/Request.cpp PU_Queue/PUQueue.cpp PU_Queue/PUQueueNode.cpp PU_Queue/main.cpp -o pu.x


LU:
g++ -std=c++17 CommonFiles/Request.cpp PU_Queue/PUQueue.cpp PU_Queue/PUQueueNode.cpp LU_QUEUE/LUQueue.cpp LU_QUEUE/LUQueueNode.cpp LU_QUEUE/main.cpp -o lu.x


CL:
g++ -std=c++17 CommonFiles/Request.cpp CL_Queue/CLQueue.cpp CL_Queue/CLQueueNode.cpp CL_Queue/main.cpp -o cl.x




RUNNING INSTRUCTIONS

Whole Program:
./cf.x inputRequests.txt

FCFS:
./fcfs.x inputRequests.txt

ST:
./st.x inputRequests.txt

PU:
./pu.x inputRequests.txt

LU:
./lu.x inputRequests.txt

CL:
./cl.x inputRequests.txt




