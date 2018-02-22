/***************************
 * Name: Vicky Mohammad
 * Date: Feb 21, 2018
 ***************************/

#include "header.h"

/***********************************************
 * Constructors
 ***********************************************/

Instance* initVars(){
    Instance* new = malloc(sizeof(Instance));
    new->garbageCollector = initializeList(dummyPrint, dummyDelete, dummyCompare);
    new->schedule = initializeList(dummyPrint, dummyDelete, priorityCompare);
    new->cpu = initCPU();
    new->info = initInfo();
    new->mode = initMode();
    new->heap = initHeap();
    new->quantity = -1;
    insertBack(&new->garbageCollector, new->cpu);
    insertBack(&new->garbageCollector, new->info);
    insertBack(&new->garbageCollector, new->mode);
    insertBack(&new->garbageCollector, new->heap);
    return new;
}//end constructor

CPU* initCPU(){
    CPU* new = malloc(sizeof(CPU));;
    new->processNumber = 0;
    new->threadNumber = 0;
    new->arrivalTime = 0;
    return new;
}//end contructor

Info* initInfo(){
    Info* new = malloc(sizeof(Info));
    new->numberOfProcesses = 0;
    new->threadSwitch = 0;
    new->processSwitch = 0;
    new->processNumber = 0;
    new->numberOfThread = 0;
    return new;
}//end contructor

Mode* initMode(){
    Mode* new = malloc(sizeof(new));
    new->detailedMode = false;
    new->verboseMode = false;
    new->roundRobinMode = false;
    return new;
}//end constructor

Heap* initHeap(){
    Heap* new = calloc(1, sizeof(Heap));
    new->length = 0;
    new->totalIO = 0;
    new->totalCPU = 0;
    new->averageTime = 0;
    new->fullTime = 0;
    new->threadCount = 0;
    new->size = 0;
    return new;
}//end constructor

Thread* initThread(){
    Thread* new = calloc(1, sizeof(Thread));
    //IO & CPU time
    new->IOTime = 0;
    new->CPUTime = 0;
    //for the thread
    new->threadNumber = 0;
    new->arrivalTime = 0;
    new->numberOfCPU = 0;
    //temp CPU
    new->tempCPUTime = 0;
    new->tempIOTime = 0;
    new->tempTime = 0;
    new->temp = 0;
    return new;
}//end constructor

/***********************************************
 * Functions
 ***********************************************/

int priorityCompare(const void* first, const void* second){
    //dec casted object
    Thread* object1 = (Thread*)first;
    Thread* object2 = (Thread*)second;
    //check which is is greater
    if(object1->arrivalTime > object2->arrivalTime){
        return -1;
    }//end if
    if(object1->arrivalTime < object2->arrivalTime){
        return 1;
    }//end if
    return 0;
}//end func

void setMode(Instance* vars, int argc, char** argv){
    //the execution comandline
    for(int x=0; x<argc; x++){
        if(!strcmp("-d", argv[x])){
            vars->mode->detailedMode = true;
        }//end if
        if(!strcmp("-v", argv[x])){
            vars->mode->verboseMode = true;
        }//end if
        if(!strcmp("-r", argv[x])){
            vars->mode->roundRobinMode = true;
        }//end if
    }//end for
}//end func

void printFinal(int finalTime, double turnAverage, double CPUUtilization){
    printf("\n\nTotal Time required is %d units\n",finalTime);
    printf("Average Turnaround Time is %.2lf time units \n",turnAverage);
    printf("CPU Utilization is %.2lf \n",CPUUtilization*100);
}//end func

void printThread(Thread* thread, Instance* vars){
    if(vars->mode->detailedMode == true) {
        printf("\nThread %d of Process %d: \n", thread->threadNumber, vars->info->numberOfProcesses);
        printf("arrival time: %d \n",thread->arrivalTime);
        printf("service time: %d units \n",thread->CPUTime);
        printf("I/O time: %d units \n",thread->IOTime);
        printf("turnaround time: %d units \n", vars->heap->fullTime - thread->arrivalTime) ;
        printf("finish time: %d units \n\n",vars->heap->fullTime);
    }//end if
    if(vars->mode->verboseMode == true) {
        printf("At time %d: Thread %d of Process %d moves from %s to %s\n", vars->heap->fullTime - thread->arrivalTime - thread->IOTime - thread->CPUTime, thread->threadNumber, vars->info->processNumber, "new", "ready");
        printf("At time %d: Thread %d of Process %d moves from %s to %s\n", vars->heap->fullTime - thread->CPUTime, thread->threadNumber, vars->info->processNumber, "ready", "running");
        printf("At time %d: Thread %d of Process %d moves from %s to %s\n", vars->heap->fullTime, thread->threadNumber, vars->info->processNumber, "running", "terminated"/*thread->endState*/);
    }//end if
}//end func

void calculate(FILE* filePointer, int* endingTime, int* timeWasted, Instance* vars){
    //loop through the number of processes
    for(int x=0; x<vars->info->numberOfProcesses; x++){
        //dec vars
        vars->info->processNumber = 0;
        vars->info->numberOfThread = 0;
        fscanf(filePointer, "%d %d", &vars->info->processNumber, &vars->info->numberOfThread);
        //calc
        endingTime = endingTime + (vars->info->threadSwitch * vars->info->numberOfThread);
        timeWasted = timeWasted + (vars->info->threadSwitch * vars->info->numberOfThread);

        //loop the number of thread
        for(int y=0; y<vars->info->numberOfThread; y++){
            //init the thread 
            Thread* thread = initThread();
            insertBack(&vars->garbageCollector, thread);
            //scan the cpu
            fscanf(filePointer, "%d %d %d", &thread->threadNumber, &thread->arrivalTime, &thread->numberOfCPU);
            int endLoop = thread->numberOfCPU-1;
            for(int z=0; z<endLoop; z++){
                fscanf(filePointer, "%d %d %d", &thread->temp, &thread->tempCPUTime, &thread->tempIOTime);
                thread->tempTime = thread->tempTime + (thread->tempCPUTime + thread->tempIOTime);
                //check the check if it reach 0
                if(!((thread->tempTime - vars->quantity) < 0)){
                    if(vars->quantity >= 0){
                        thread->CPUTime = thread->CPUTime - vars->quantity;
                        thread->IOTime = thread->IOTime - vars->quantity;
                    }//end if
                }//end if
                thread->CPUTime = thread->CPUTime + thread->CPUTime;
                thread->IOTime = thread->IOTime + thread->tempIOTime;
            }//end for
            fscanf(filePointer, "%d %d", &thread->temp, &thread->tempCPUTime);
            thread->CPUTime = thread->CPUTime + thread->tempCPUTime;
            vars->heap->totalCPU = vars->heap->totalCPU + thread->CPUTime;
            vars->heap->totalIO = vars->heap->totalIO + thread->IOTime;

            insertFront(&vars->schedule, thread);            
        }//end for

    }//end for
}//end func

/***********************************************
 * Main function to run the program
 ***********************************************/

int main(int argc, char** argv){
    //dec vars
    Instance* vars = initVars();
    strcpy(vars->fileName, argv[argc-1]);
    debug("File name: %s\n", vars->fileName);

    //open the file
    FILE* filePointer = fopen(vars->fileName, "r");
    if(filePointer == NULL){
        printf("Invalid file name: %s\n", vars->fileName);
        clearList(&vars->garbageCollector);
        free(vars);
        return 0;
    }//end if
    setMode(vars, argc, argv);

    //scan the first line and then calculate the time
    fscanf(filePointer, "%d %d %d", &vars->info->numberOfProcesses, &vars->info->threadSwitch, &vars->info->processSwitch);
    int timeWasted = vars->info->numberOfProcesses * vars->info->numberOfProcesses; 
    int endingTime = timeWasted;
    calculate(filePointer, &endingTime, &timeWasted, vars);
    
    //free and exit
    fclose(filePointer);
    clearList(&vars->garbageCollector);
    free(vars);
    return 0;
}//end int