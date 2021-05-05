#ifndef comapreTasks_hpp
#define comapreTasks_hpp
#include <iostream>
#include "Zadania.hpp"
 
struct TaskComparingTimeP{

    bool operator ()( Task & task1, Task & task2){

        if( task1.ShowValueOfVariable('P')>= task2.ShowValueOfVariable('P')){return true;}
       
        if( task1.ShowValueOfVariable('P') < task2.ShowValueOfVariable('P') ){ return false;}

        return false;
    }

};


struct TaskComparingTimeH{

    bool operator ()( Task & task1, Task & task2){

        if( task1.ShowValueOfVariable('H') <= task2.ShowValueOfVariable('H') ){return true;}
       
       if( task1.ShowValueOfVariable('H') > task2.ShowValueOfVariable('H') ){return false;}

       return false;
    }

};

#endif