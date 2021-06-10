#include "Task.h"

int Task::AmountOFTask=0;

int Task::ReturnValue(char IDValue){
    if(IDValue == 'T')
        return TermintaionTime;
    
    else if(IDValue == 'S')
        return StartTime;

    else{
        std::cout <<"Wrong choice in Task::ReturnValue \n";
        exit(3);
    }
}



void Task::SetStartTime(int Value){
    StartTime=Value;
}


void Task::SetTerminationTime(int Value){
    TermintaionTime=Value;
}


void Task::TaskInit(int AmountOfOperations){
    if(this->AmountOfOperations == 0 && AmountOfOperations > 0){
        this->AmountOfOperations=AmountOfOperations;
        OperationsTab=new Operation [AmountOfOperations];
    }

    else{
        std::cout <<"It's not good idea, message from Task::TaskInit  \n";
    }
}


void Task::Add_PerformedTime_Operation(int Value, int OperatorID){
    if(AmountOfOperations!=0 && OperatorID < AmountOfOperations && OperatorID >= 0){
        OperationsTab[OperatorID].AddValue('P',Value);
    }
    else{
        std::cout << "You don't have any Operation \n";
    }

}


void Task::Add_StartTime_Operation(int Value, int OperatorID){
    if(AmountOfOperations!=0 && OperatorID < AmountOfOperations && OperatorID >= 0){
        OperationsTab[OperatorID].AddValue('S',Value);
        if(OperatorID == 0)
            SetStartTime(Value);
    }
    else{
        std::cout << "You don't have any Operation \n";
    }
}


void Task::Add_TerminationTime_Operation(int Value, int OperatorID){
    if(AmountOfOperations!=0 && OperatorID < AmountOfOperations && OperatorID >= 0){
        OperationsTab[OperatorID].AddValue('T',Value);

        if(OperatorID == 0)
            SetTerminationTime(Value);
    }
    else{
        std::cout << "You don't have any operation \n";
    }
}


int Task::Return_PerformedTime_Operation(int OperatorID){
    if(AmountOfOperations!=0 && OperatorID < AmountOfOperations && OperatorID >= 0){
       return OperationsTab[OperatorID].ReturnValue('P');
    }
    else{
        std::cout << "You don't have any Operation \n";
        exit(6);
    }
}


int Task::Return_StartTime_Operation( int OperatorID){
    if(AmountOfOperations!=0 && OperatorID < AmountOfOperations && OperatorID >= 0){
       return OperationsTab[OperatorID].ReturnValue('S');
    }
    else{
        std::cout << "You don't have any Operation \n";
        exit(6);
    }
}


int Task::Return_TerminationTime_Operation(int OperatorID){
    if(AmountOfOperations!=0 && OperatorID < AmountOfOperations && OperatorID >= 0){
       return OperationsTab[OperatorID].ReturnValue('T');
    }
    else{
        std::cout << "You don't have any Operation \n";
        exit(6);
    }
}

int Task::Return_TaskID(){
    return TaskID;
}
