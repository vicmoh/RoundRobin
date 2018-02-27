/***************************
 * Name: Vicky Mohammad
 * Date: Feb 21, 2018
 ***************************/

#include "header.h"

/***********************************************
 * constructors
 ***********************************************/

Instance* initVars(){
    Instance* new = malloc(sizeof(Instance));
    new->garbageCollector = initializeList(dummyDelete, dummyCompare);
    new->schedule = initializeList(dummyClean, priorityCompare);
    new->completed = initializeList(dummyClean, priorityCompare);
    new->info = initInfo();
    new->mode = initMode();
    new->heap = initHeap();
    new->quantum = -1;
    new->endingTime = 0;
    new->timeWasted = 0;
    new->endLoop = 0;
    insertBack(&new->garbageCollector, new->info);
    insertBack(&new->garbageCollector, new->mode);
    insertBack(&new->garbageCollector, new->heap);
    return new;
}//end constructor

Mode* initMode(){
    Mode* new = malloc(sizeof(new));
    new->detailedMode = false;
    new->verboseMode = false;
    new->roundRobinMode = false;
    return new;
}//end constructor

Info* initInfo(){
    Info* new = malloc(sizeof(Info));
    new->numberOfProcesses = 0;
    new->numberOfCPU = 0;
    //switch
    new->threadSwitch = 0;
    new->processSwitch = 0;
    //for during the process
    new->processNumber = 0;
    new->numberOfThread = 0;
    return new;
}//end contructor

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
    new->CPUTime = 0;//servive time
    new->fullTime = 0;
    //for the thread
    new->threadNumber = 0;
    new->processNumber = 0;
    new->arrivalTime = 0;
    //temp CPU
    new->tempCPUTime = 0;
    new->tempIOTime = 0;
    new->tempTime = 0;
    new->temp = 0;
    return new;
}//end constructor

/***********************************************
 * functions
 ***********************************************/

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
            int quantumValue = atoi(argv[x+1]);
            vars->mode->roundRobinMode = true;
            vars->quantum = quantumValue;
        }//end if
    }//end for
}//end func

void process1(FILE* filePointer, Instance* vars){
    //loop through the number of processes
    for(int x=0; x<vars->info->numberOfProcesses; x++){
        //dec vars
        vars->info->processNumber = 0;
        vars->info->numberOfThread = vars->info->processNumber;
        fscanf(filePointer, "%d %d", &vars->info->processNumber, &vars->info->numberOfThread);
        //calc
        vars->endingTime = vars->endingTime + (vars->info->threadSwitch * vars->info->numberOfThread);
        vars->timeWasted = vars->endingTime;
        
        //call the next process
        process2(filePointer, vars);

        //iterate through the process, calc and display each output depending on the mode
        ListIterator iterList = createIterator(vars->schedule);
        for(int y=0; y<getLength(vars->schedule); y++){
            bool ifNotComplete = true;
            Thread* thread = nextElement(&iterList);
            
            //check if the process is already compleated
            ListIterator completeIter = createIterator(vars->completed); 
            for(int z=0; z<getLength(vars->completed); z++){
                Thread* completeThread = nextElement(&completeIter);
                if(thread->processNumber == completeThread->processNumber && thread->threadNumber == completeThread->threadNumber){
                    ifNotComplete = false;
                }//end if
            }//end for

            if(ifNotComplete == true){
                if(thread->threadNumber == 1){
                    vars->heap->fullTime = vars->heap->fullTime + vars->info->processSwitch;
                }//end if
                vars->heap->fullTime = vars->heap->fullTime + (thread->CPUTime + thread->IOTime + vars->info->threadSwitch);
                vars->heap->threadCount = vars->heap->threadCount + 1;
                vars->heap->averageTime = vars->heap->averageTime + (vars->heap->fullTime - thread->arrivalTime);
                printThread(thread, vars);
            }//end if
            insertFront(&vars->completed, thread);
        }//end for

    }//end for
}//end func

void process2(FILE* filePointer, Instance* vars){
    //loop the number of thread
    for(int y=0; y<vars->info->numberOfThread; y++){
        //init the thread 
        Thread* thread = initThread();
        insertSorted(&vars->garbageCollector, thread);
        //scan the cpu
        fscanf(filePointer, "%d %d %d", &thread->threadNumber, &thread->arrivalTime, &vars->info->numberOfCPU);
        vars->endLoop = vars->info->numberOfCPU-1;

        //call the next process
        process3(filePointer, thread, vars);
        
        //scan the next
        fscanf(filePointer, "%d %d", &thread->temp, &thread->tempCPUTime);
        thread->CPUTime = thread->CPUTime + thread->tempCPUTime;
        vars->heap->totalCPU = vars->heap->totalCPU + thread->CPUTime;
        vars->heap->totalIO = vars->heap->totalIO + thread->IOTime;
        thread->processNumber = vars->info->processNumber;

        //insert the thread to the list
        insertSorted(&vars->schedule, thread);         
    }//end for
}//end func

void process3(FILE* filePointer, Thread* thread, Instance* vars){
    for(int z=0; z<vars->endLoop; z++){
        fscanf(filePointer, "%d %d %d", &thread->temp, &thread->tempCPUTime, &thread->tempIOTime);
        thread->tempTime = thread->tempTime + (thread->tempCPUTime + thread->tempIOTime);
        //check the check if it reach 0
        if(!((thread->tempTime - vars->quantum) < 0)){
            if(vars->quantum >= 0){
                thread->CPUTime = thread->CPUTime - vars->quantum;
                thread->IOTime = thread->IOTime - vars->quantum;
            }//end if
        }//end if
        thread->CPUTime = thread->CPUTime + thread->tempCPUTime;
        thread->IOTime = thread->IOTime + thread->tempIOTime;
    }//end for
}//end func

int priorityCompare(const void* first, const void* second){
    //dec casted object
    Thread* object1 = (Thread*)first;
    Thread* object2 = (Thread*)second;
    //check which is is greater
    if(object1->arrivalTime > object2->arrivalTime){
        //debug("priority compare return -1\n");
        return 1;
    }//end if
    if(object1->arrivalTime < object2->arrivalTime){
        //debug("priority compare return 1\n");
        return -1;
    }//end if
    return 0;
}//end func

void printThread(Thread* thread, Instance* vars){
    if(vars->mode->detailedMode == true) {
        printf("Thread %d of Process %d: \n", thread->threadNumber, thread->processNumber);
        printf("arrival time: %d \n",thread->arrivalTime);
        printf("service time: %d units \n",thread->CPUTime);
        printf("I/O time: %d units \n",thread->IOTime);
        printf("turnaround time: %d units \n", vars->heap->fullTime - thread->arrivalTime) ;
        printf("finish time: %d units \n\n",vars->heap->fullTime);
    }//end if
    if(vars->mode->verboseMode == true) {
        int newToReady = vars->heap->fullTime - thread->arrivalTime - thread->IOTime - thread->CPUTime;
        int readyToRunning = vars->heap->fullTime - thread->CPUTime;
        int runningToTerminated = vars->heap->fullTime;
        printf("At time %d: Thread %d of Process %d moves from new to ready\n", newToReady, thread->threadNumber, vars->info->processNumber);
        printf("At time %d: Thread %d of Process %d moves from ready to running\n", readyToRunning, thread->threadNumber, vars->info->processNumber);
        printf("At time %d: Thread %d of Process %d moves from running to terminated\n", runningToTerminated, thread->threadNumber, vars->info->processNumber);
    }//end if
}//end func

void printFinal(int finalTime, double turnAverage, double CPUUtilization){
    printf("\nTotal Time required is %d units\n",finalTime);
    printf("Average Turnaround Time is %.2lf time units \n",turnAverage);
    printf("CPU Utilization is %.2lf%s\n",CPUUtilization*100, "\%");
}//end func

/***********************************************
 * main function to run the program
 ***********************************************/

int main(int argc, char** argv){//good
    //dec vars
    Instance* vars = initVars();
    strcpy(vars->fileName, argv[argc-1]);
    debug("debug argument number: %d\n", argc);
    debug("debug file name: %s\n", vars->fileName);

    //open the file
    //FILE* filePointer = fopen(vars->fileName, "r");
    // if(filePointer == NULL){
    //     printf("Invalid file name: %s\n", vars->fileName);
    //     clearList(&vars->garbageCollector);
    //     free(vars);
    //     return 0;
    // }//end if
    setMode(vars, argc, argv);

    //scan the first line and then calculate the time
    fscanf(stdin, "%d %d %d", &vars->info->numberOfProcesses, &vars->info->threadSwitch, &vars->info->processSwitch);
    vars->timeWasted = vars->info->numberOfProcesses * vars->info->processSwitch; 
    vars->endingTime = vars->info->numberOfProcesses * vars->info->processSwitch;
    process1(stdin, vars);
    
    vars->endingTime = vars->endingTime + (vars->heap->totalCPU + vars->heap->totalIO);
    debug("debug threadCount: %d\n", vars->heap->threadCount);
    double totalAverage = (double)vars->heap->averageTime / (double)vars->heap->threadCount;
    double CPUUtilization = (double)(vars->endingTime - vars->timeWasted) / (double)vars->endingTime;
    printFinal(vars->endingTime, totalAverage, CPUUtilization);

    //free and exit
    //fclose(filePointer);
    clearList(&vars->garbageCollector);
    clearList(&vars->schedule);
    free(vars);
    return 0;
}//end int