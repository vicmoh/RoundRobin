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

typedef struct{
    char fileName[256];
    CPU cpu;
}Instance;

typedef struct{
    int process;
    int thread;
    int arrivalTime;
}CPU;

typedef struct{
    int numberOfProcesses;
    int threadSwitch;
    int process
}INFO;

Instance* initInstance(){
    Instance* newVars = calloc(1, sizeof(Instance));
    return newVars;
}//end constructor

void readFile(char* fileName, CPU* cpu){
    FILE* filePointer = fopen(fileName, "r");
    fscanf(fileName, "%d %d %d", );
    fclose(filePointer);
}//end func

int main(int argc, char** argv){
    
    return 0;
}//end int