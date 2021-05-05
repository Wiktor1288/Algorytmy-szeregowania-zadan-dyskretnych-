#include <iostream>
#include <memory>
#include <vector>
#include "Task.h"
#include "RandomNumberGenerator.h"

using namespace std;
void GenerateRandomData(RandomNumberGenerator RandomObject, shared_ptr <Task []> Tasks, int SizeT);
void ShowTasks(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int[]> Order);
int main()
{
auto NumberOfTask{0}, Seed{0};
cout<<"Seed value: ";
cin >> Seed; 
cout<<"\nNumber of Tasks: ";
cin >> NumberOfTask; 
RandomNumberGenerator Random1(Seed);
shared_ptr <Task []> TaskTab(new Task[NumberOfTask]);
shared_ptr <int[]> TabOrder(new int[NumberOfTask]);
for(auto i=0; i<NumberOfTask; i++)
    TabOrder[i]=i;
GenerateRandomData(Random1, TaskTab, NumberOfTask);
ShowTasks(TaskTab, NumberOfTask, TabOrder);
return 0;
}

void GenerateRandomData(RandomNumberGenerator RandomObject, shared_ptr <Task []> Tasks, int SizeT){
    auto  i{0}, A{0};

    for(i=0; i<SizeT; i++){
        Tasks[i].AddPerformedTime(RandomObject.nextInt(1,29));
        A+=Tasks[i].ShowValueOfVariable('P');
    }

    for(i=0; i<SizeT; i++){
        Tasks[i].AddWeight(RandomObject.nextInt(1,9));
    }

        for(i=0; i<SizeT; i++){
        Tasks[i].AddDeadline(RandomObject.nextInt(1,29));
    }
}

void ShowTasks(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int[]> Order){

    auto i{0};

    for(; i<SizeT; i++){
    cout << endl << "ID: " << Tasks[Order[i]].IdOfTask << endl;
    cout << Tasks[Order[i]].ShowValueOfVariable('P') << "  " << Tasks[Order[i]].ShowValueOfVariable('W')
                          <<  "  " << Tasks[Order[i]].ShowValueOfVariable('L') << "  " << Tasks[Order[i]].ShowValueOfVariable('C')
                          << "  " << Tasks[Order[i]].ShowValueOfVariable('D') << endl;

    }
}