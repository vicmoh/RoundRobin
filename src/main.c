/***************************
 * Name: Vicky Mohammad
 * Date: Feb 21, 2018
 ***************************/

//import lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"

//dec macros
#define debug if(true)printf

/***********************************************
 * Header functions
 ***********************************************/

typedef struct{
    char fileName[256];
    List garbageCollector;
    CPU cpu;
    Info info;
    Mode mode;
}Instance;

typedef struct{
    int processNumber;
    int threadNumber;
    int arrivalTime;
}CPU;

typedef struct{
    int numberOfProcesses;
    int threadSwitch;
    int processSwitch;
}Info;

typedef struct{
    bool detailedMode;
    bool verboseMode;
    bool roundRobinMode;
}Mode;

Instance initVars();
CPU initCPU();
Info initInfo();
Mode initMode();
int mode(Instance* vars);

/***********************************************
 * Main helper functions
 ***********************************************/

Instance initVars(){
    Instance new = calloc(1 ,sizeof(Instance));
    new->cpu = initCPU();
    new->info = initInfo();
    new->mode = initMode();
    
    return new;
}//end constructor

CPU initCPU(){
    CPU new = calloc(1 ,sizeof(CPU));;
    new->processNumber = 0;
    new->threadNumber = 0;
    new->processSwitch = 0;
    return new;
}//end contructor

Info initInfo(){
    Info new = calloc(1 ,sizeof(Info));
    new->numberOfProcesses = 0;
    new->threadSwitch = 0;
    new->processSwitch = 0;
    return new;
}//end contructor

Mode initMode(){
    Mode new = calloc(1 ,sizeof(new));
    new->detailedMode = false;
    new->verboseMode = false;
    new->roundRobinMode = false;
    return new;
}//end constructor

int mode(Instance* vars){
    return 0;
}//end func

/***********************************************
 * Main function to run the program
 ***********************************************/

int main(int argc, char** argv){
    //dec vars
    Instance vars = initVars();

    //the execution comandline
    for(int x=0; x<argc; x++){
        if(!strcmp("-d", argv[x])){
            detailedMode = true;
        }
    }//end for
    
    return 0;
}//end int