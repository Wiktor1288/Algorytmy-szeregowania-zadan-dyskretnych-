#ifndef Task_h
#define Task_h
#include "Operation.h"
#include <iostream>

class Task{

    static int AmountOFTask;      // Id of Task
    Operation *OperationsTab;   // Pointer to create array of operations
    int TermintaionTime;    // Time of termination task termination == Time of termination all operations contained 
    int StartTime;              // Time of start task and first operation
    int AmountOfOperations;   // Amount of operation == amount of machines
    int TaskID;

    /*
    SetStartTime
    used to set value of start time. It can be called by Task::Add_StartTime_Operation only.
    */
    void SetStartTime(int Value);

    /*
    SetStartTime
    used to set value of start time. It can be called by Task::Add_TerminationTime_Operation only.
    */
    void SetTerminationTime(int Value);

    public:
    Task(){
        TaskID=++AmountOFTask;
        OperationsTab=nullptr;
        TermintaionTime=0;
        StartTime=0;
        AmountOfOperations=0;
    }

    ~Task(){
        if(AmountOfOperations!=0)
        {
            delete [] OperationsTab;
        }
        else{
            delete OperationsTab;
        }
        AmountOFTask--;
    }

    Task(const Task &Ts){
        AmountOFTask++;
        TaskID=Ts.TaskID;
        AmountOfOperations=Ts.AmountOfOperations;
        TermintaionTime=Ts.TermintaionTime;
        StartTime=Ts.StartTime;
        if(Ts.AmountOfOperations !=0){
            OperationsTab=new Operation [AmountOfOperations];
            for(int i=0; i<AmountOfOperations; i++){
                OperationsTab[i]=Ts.OperationsTab[i];
            }
        }

        else
            OperationsTab=nullptr;

    }

    Task & operator=(const Task &Ts){

        if(this==&Ts)
            return *this;

        if(AmountOfOperations!=0){
            delete [] OperationsTab;
            TaskID=Ts.TaskID;
            AmountOfOperations=Ts.AmountOfOperations;
            TermintaionTime=Ts.TermintaionTime;
            StartTime=Ts.StartTime;
            OperationsTab=new Operation [AmountOfOperations];
            for(int i=0; i<AmountOfOperations; i++){
                OperationsTab[i]=Ts.OperationsTab[i];
            }
        }      

        else{
            delete OperationsTab;
            TaskID=Ts.TaskID;
            AmountOfOperations=Ts.AmountOfOperations;
            TermintaionTime=Ts.TermintaionTime;
            StartTime=Ts.StartTime;
            OperationsTab=Ts.OperationsTab;
        }

 
        return *this;
    }

    int ReturnValue(char IDValue);
    void TaskInit(int AmountOfOperations);
    void Add_PerformedTime_Operation(int Value, int OperatorID);
    void Add_StartTime_Operation(int Value, int OperatorID);
    void Add_TerminationTime_Operation(int Value, int OperatorID);
    int Return_PerformedTime_Operation(int OperatorID);
    int Return_StartTime_Operation(int OperatorID);
    int Return_TerminationTime_Operation(int OperatorID);
    int Return_TaskID();
 


};

#endif