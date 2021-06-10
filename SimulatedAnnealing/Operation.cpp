#include "Operation.h"
#include <iostream>

void Operation::AddValue(char IDValue, int Value){
    if(IDValue == 'P')
        PerformedTime=Value;

    else if(IDValue == 'S')
        StartTime=Value;

    else if(IDValue == 'T')
        TerminationTime=Value;

    else{
        std::cout <<"Wrong choice in Operation::AddValue \n";
        exit(1);
    }
}

int Operation::ReturnValue(char IDValue){
    if(IDValue == 'P')
        return PerformedTime;

    else if(IDValue == 'S')
        return StartTime;

    else if(IDValue == 'T')
        return TerminationTime;

    else{
        std::cout <<"Wrong choice in Operation::ReturnValue \n";
        exit(2);
    }
}