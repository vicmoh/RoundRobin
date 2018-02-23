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
    int processNumber;
    int threadNumber;
    int arrivalTime;
}CPU;

typedef struct{
    //main at the start
    int numberOfProcesses;
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
    CPU* cpu;
    Info* info;
    Mode* mode;
    Heap* heap;
    int quantity;
}Instance;

typedef struct{
    //IO & CPU time
    int IOTime;
    int CPUTime;
    //for the thread
    int threadNumber;
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
CPU* initCPU();
Info* initInfo();
Mode* initMode();
Heap* initHeap();
//helper vars for the main
int priorityCompare(const void* first, const void* second);
void setMode(Instance* vars, int argc, char** argv);
void printFinal(int finalTime, double turnAverage, double CPUUtilization);
void calculate(FILE* filePointer, int* endingTime, int* timeWasted, Instance* vars);

#endif
