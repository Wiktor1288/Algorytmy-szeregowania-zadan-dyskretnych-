#ifndef Task_h
#define Task_h

#include <iostream>

class Task{
static int AmountOfTask;    // Task ID
int IdOfTask;
int TerminationTime;        // End time of a Task
int StartTime;              // Start time of a task 'S'
int PerformedTime;          // time of duration of task 'p'
int DelayTime;              // delay of task 'T'
int Weight;                 // weight of task /penalty factor 'w'
int Deadline;               // demand deadline 'd'



public:
Task(){
    IdOfTask=++AmountOfTask;
    TerminationTime=0;
    StartTime=0;
    PerformedTime=0;
    DelayTime=0;
    Weight=0;
    Deadline=0;
}

};

#endif