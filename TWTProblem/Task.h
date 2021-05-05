#ifndef Task_h
#define Task_h

#include <iostream>

class Task{
static int AmountOfTask;    // Task ID
int CompleteTime;        // End time of a Task
int StartTime;              // Start time of a task 'S'
int PerformedTime;          // time of duration of task 'p'
int DelayTime;              // delay of task 'T'
int Weight;                 // weight of task /penalty factor 'w'
int Deadline;               // demand deadline 'd'
int WT;



public:
int IdOfTask;
Task(){
    IdOfTask=++AmountOfTask;
    CompleteTime=0;
    StartTime=0;
    PerformedTime=0;
    DelayTime=0;
    Weight=0;
    Deadline=0;
    WT=0;
}
void AddCompleteTime(int Ctime);
void AddStartTime(int Stime);
void AddPerformedTime(int Ptime);
void AddDelayTime(int Dtime);
void AddWeight(int Weight);
void AddDeadline(int Deadline);
void AddWT(int Value);
int ShowValueOfVariable(char FirstLetter);

};

#endif