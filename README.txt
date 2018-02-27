/***************************
 * Name: Vicky Mohammad
 * Date: Feb 21, 2018
 ***************************/

--------------<<< HOW TO RUN THE PROGRAM >>>--------------
PLEASE READ!!! Due to using LinkList API, I have to create folders
such include for the header files To run the program.

* Type "make" to compile
(if inputFile.txt is in a folder use "./the_folder_name/inputFile.txt 
to run the program rather than just the name of the file")

* To run FCFS, type "./bin/run -r 10 < inputFile.txt"
* To run Round Robin, type "./bin/run -d -r 10 < inputFile.txt"
* To run Verbose Mode, type "./bin/run -v 10 < inputFile.txt"

-------------<<< RESTRICTION & LIMITATION >>>-------------
* Program will crash if there is comments in the input files
  So, make sure to have no comments for the input files
* The Round Robin may not give the right output calculation
* a number (quantum) MUST BE AFTER "-r" or it will give
  the wrong ouput, so please make SURE TO PUT NUMBER AFTER "-r"

---------------------<<< REFERENCE >>>---------------------
* I use linklist API that I created from the CIS*2750 course

---------------------<<< REPORT >>>---------------------

1) Does your simulator include switch overhead for the first ready state to running state transition?
2) Does your simulator include switch overhead if a thread moves from ready state to running state and the CPU is idle?  
3) Does your simulator include switch overhead if a thread moves from running state to blocked state and the ready queue is empty? 
4) Does your simulation include switch overhead if a thread is interrupted (due to a time slice) and either the ready queue
   is empty or the thread has the highest priority?

1) For my algorithm, my program simulator includes switch overhead 
   time for every new thread occurs.
2) My program simulation also includes the switch overhead if thread
   moves from the ready states to the running state and the CPU is on idle
3) My program simulation does not compensate for switching if a thread moves 
   from running state to blocked state.
4) During the process if thread is interrupted, it does not include
   switch overhead on my simulation.