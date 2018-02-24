/***************************
 * Name: Vicky Mohammad
 * Date: Feb 21, 2018
 ***************************/

--------------<<< HOW TO RUN THE PROGRAM >>>--------------
* Type "make" to compile
* To run FCFS, type "./bin/run -r 10 < input_file.txt"
* To run Round Robin, type "./bin/run -d -r 10 < input_file.txt"
* To run Verbose Mode, type "./bin/run -v 10 < input_file.txt"

-------------<<< RESTRICTION & LIMITATION >>>-------------
* Program will crash if there is comments in the input files
So, make sure to have no comments for the input files
* The Round Robin may not give the right output calculation

---------------------<<< REFERENCE >>>---------------------
* I use linklist API that I created from the CIS*2750 course

---------------------<<< REPORT >>>---------------------

1) For my algorithm my program simulator includes switch overhead 
   time for every new thread occurs.
2) My program simulation also includes the switch overhead if thread
   moves from the ready states to the running state and the CPU is on idle
3) My program simulation  does not compensate for switching if a thread moves 
   from running state to blocked state.
4) During the process if therad is interrupted, it does not include
   switch overhead on my simulation.