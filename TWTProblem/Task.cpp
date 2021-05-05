#include "Task.h"
#include <iostream>

int Task::AmountOfTask=0;

void Task::AddCompleteTime(int Ctime){

    if(Ctime > 0){
        CompleteTime=Ctime;
    }
    else 
        std::cout << "Complete time can't be lower than 0 \n";
    
}


void Task::AddStartTime(int Stime){
    if(Stime >= 0 ){
        StartTime=Stime;
    }
    else 
        std::cout << "Start time can't be lower than 0 \n";

}


void Task::AddPerformedTime(int Ptime){
    if(Ptime > 0){
        PerformedTime=Ptime;
    }
    else 
        std::cout << "Performed time can't be lower than 0 \n";
}


void Task::AddDelayTime(int Dtime){
    if(Dtime > 0 ){
        DelayTime=Dtime;
    }
    else 
        std::cout << "Delay time can't be lower than 0 \n";

}


void Task::AddWeight(int Weight){
    if(Weight > 0 ){
        this->Weight=Weight;
    }
    else 
        std::cout << "Weight can't be lower than 0 \n";

}


void Task::AddDeadline(int Deadline){
    if(Deadline > 0 ){
        this->Deadline=Deadline;
    }
    else 
        std::cout << "Deadline can't be lower than 0 \n";
}

void Task::AddWT(int Value){
    if(Value>=0){
        WT=Value;
    }
    else 
        std::cout << "WT can't be lower than 0 \n";

}


int Task::ShowValueOfVariable(char FirstLetter){

    if(FirstLetter == 'C'){
        return CompleteTime;
    }
    if(FirstLetter == 'P'){
        return PerformedTime;
    }
    if(FirstLetter == 'S'){
        return StartTime;
    }
    if(FirstLetter == 'W'){
        return Weight;
    }
    if(FirstLetter == 'D'){
        return DelayTime;
    }
    if(FirstLetter == 'L'){
        return Deadline;
    }
    if(FirstLetter == 'T'){
        return WT;
    }
    else{
        std::cout << "Wrong choice in Task::ShowValueOfVariable \n";
        exit(1);
    }

}