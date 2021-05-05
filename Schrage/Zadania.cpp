#include "Zadania.hpp"

int Task::AmountOfTask=0;

void Task::AddTPripare(int Time1){

    TimeOfPripare=Time1;
}

void Task::AddTExecution(int Time1){

    TimeOfExecution=Time1;
}

void Task::AddStartMoment(int TimeTerminationPreviousTask){
    if(TimeTerminationPreviousTask>TimeOfPripare)
        StartMoment=TimeTerminationPreviousTask;

    else
        StartMoment=TimeOfPripare;
}

void Task::AddTermiantion(){
    if(StartMoment!=0)
        Termiantion=StartMoment+TimeOfExecution;
}



int Task::ShowValueOfVariable(char FirstLetter){

    if(FirstLetter=='P'){
        return TimeOfPripare;
    }
    else if(FirstLetter=='E')
    {
        return TimeOfExecution;
    }
    else if(FirstLetter=='I')
    {
        return IdOfTask;
    }
    else if(FirstLetter=='M')
    {
        return StartMoment;
    }
    else if(FirstLetter=='T')
    {
        return Termiantion;
    }
    else if(FirstLetter=='Q')
    {
        return PositionInQueue;
    }
    else if(FirstLetter=='H')
    {
        return TimeOfHandover;
    }
    else
    {
    std::cout <<" Wrong choice of parametr in Task::ShowValueOfVariable";
    exit(0);
    }
    

}


void Task::AddPosition(int position){
    PositionInQueue=position;
}


void Task::AddTHandober(int Time1){
    TimeOfHandover=Time1;
}