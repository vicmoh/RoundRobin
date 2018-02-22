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
}Instance;

Instance* initInstance(){
    Instance* newVars = calloc(1, sizeof(Instance));
    return newVars;
}//end constructor

void readFile(char* fileName){
    FILE* filePointer = fopen(fileName, "r");
    fprintf(fileName, );
    fclose(filePointer);
}//end func

int main(int argc, char** argv){
     
    return 0;
}//end int