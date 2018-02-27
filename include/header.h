#ifndef _HEADER_H_
#define _HEADER_H_

//import lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"

//dec macros
#define debug if(true)printf

typedef struct{
    //main at the start
    int numberOfProcesses;
    int numberOfCPU;
    //switch
    int threadSwitch;
    int processSwitch;
    //after main when parsing
    int processNumber;
    int numberOfThread;
}Info;

typedef struct{
    bool detailedMode;
    bool verboseMode;
    bool roundRobinMode;
}Mode;

typedef struct {
  int length;
  int totalIO;
  int totalCPU;
  int averageTime;
  int fullTime;
  int threadCount;
  int size;
} Heap;

typedef struct{
    char fileName[256];
    List garbageCollector;
    List schedule;
    Info* info;
    Mode* mode;
    Heap* heap;
    int quantum;
    int endingTime;
    int timeWasted;
    int endLoop;
}Instance;

typedef struct{
    //IO & CPU time
    int IOTime;
    int CPUTime;
    int fullTime;
    //for the thread
    int threadNumber;
    int processNumber;
    int arrivalTime;
    int numberOfCPU;
    //temp CPU
    int tempCPUTime;
    int tempIOTime;
    int tempTime;
    int temp;
}Thread;

//constructors
Instance* initVars();
Mode* initMode();
Info* initInfo();
Heap* initHeap();
//helper vars for the main
void setMode(Instance* vars, int argc, char** argv);
void process1(FILE* filePointer, Instance* vars);
void process2(FILE* filePointer, Instance* vars);
void process3(FILE* filePointer, Thread* thread, Instance* vars);
int priorityCompare(const void* first, const void* second);
void printThread(Thread* thread, Instance* vars);
void printFinal(int finalTime, double turnAverage, double CPUUtilization);

#endif
