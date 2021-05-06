#include <iostream>
#include <memory>
#include <vector>
#include <climits>
#include "Task.h"
#include "RandomNumberGenerator.h"

using namespace std;
int Fmax=INT_MAX;
void GenerateRandomData(RandomNumberGenerator RandomObject, shared_ptr <Task []> Tasks, int SizeT);
/* ShowTask
    Basic function for display instance and data
*/
void ShowTasks(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int[]> Order);
int Objectivefunction(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int[]> Order);
void GreedyAlgorithm(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int []> Order); 

void BF(shared_ptr<Task[]> Tasks_1, vector<Task> Nset, int NTask, shared_ptr<int[]> TabOrder1,int ite, int *tab, int i);
void BruteForce(shared_ptr<Task[]> Tasks_1, int Ntask, shared_ptr<int[]> TabOrder1);

int main()
{
auto NumberOfTask{0}, Seed{0}, F{0};
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
Objectivefunction(TaskTab, NumberOfTask, TabOrder);
ShowTasks(TaskTab, NumberOfTask, TabOrder);
cout<<"\n-------BruteForce--------\n";
BruteForce(TaskTab, NumberOfTask, TabOrder);
F=Objectivefunction(TaskTab, NumberOfTask, TabOrder);
ShowTasks(TaskTab, NumberOfTask, TabOrder);
cout<<"\n---------------------"<<F<<"\n";
cout << "greedy \n"; 
GreedyAlgorithm(TaskTab, NumberOfTask, TabOrder);
Objectivefunction(TaskTab, NumberOfTask, TabOrder);
ShowTasks(TaskTab, NumberOfTask, TabOrder);

return 0;
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
                          << "  " << Tasks[Order[i]].ShowValueOfVariable('D') << "  " << Tasks[Order[i]].ShowValueOfVariable('T') << endl;

    }
}

int Objectivefunction(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int[]> Order){

    auto i{0}, sum{0}, F{0};

    for(; i<SizeT; i++){
        if(i==0){
            Tasks[Order[i]].AddStartTime(0);
            Tasks[Order[i]].AddCompleteTime(Tasks[Order[i]].ShowValueOfVariable('P'));
            Tasks[Order[i]].AddDelayTime(max(Tasks[Order[i]].ShowValueOfVariable('C')-Tasks[Order[i]].ShowValueOfVariable('L'), 0));
        }
        else{
            Tasks[Order[i]].AddStartTime(Tasks[Order[i-1]].ShowValueOfVariable('C'));
            Tasks[Order[i]].AddCompleteTime(Tasks[Order[i]].ShowValueOfVariable('P')+Tasks[Order[i]].ShowValueOfVariable('S'));
            Tasks[Order[i]].AddDelayTime(max(Tasks[Order[i]].ShowValueOfVariable('C')-Tasks[Order[i]].ShowValueOfVariable('L'), 0));
         }

         sum=Tasks[Order[i]].ShowValueOfVariable('D')*Tasks[Order[i]].ShowValueOfVariable('W');
         Tasks[Order[i]].AddWT(sum);
         F+=Tasks[Order[i]].ShowValueOfVariable('T');
    }

    return F;
}


void GreedyAlgorithm(shared_ptr <Task []> Tasks, int SizeT, shared_ptr <int []> Order){

    auto i{0}, j{0}, minV{0}, IDmin{0};
    vector<Task> Nset;

    for(i=0; i<SizeT; i++){
        Nset.push_back(Tasks[i]);
    }
    
    for(i=0; i<SizeT; i++){
        minV=Nset[0].ShowValueOfVariable('L');
        for(j=0; j<SizeT-i; j++){ 
            if(minV >= Nset[j].ShowValueOfVariable('L')){
                Order[i]=Nset[j].IdOfTask-1;
                IDmin=j;
                minV=Nset[j].ShowValueOfVariable('L');
            }
        }
        Nset.erase(Nset.begin() + IDmin);
    }

}

void BF(shared_ptr<Task[]> Tasks_1, vector<Task> Nset, int NTask, shared_ptr<int[]> TabOrder1,int ite, int *tab, int i)
{
auto Fc{0};

tab[i]=Nset[ite].IdOfTask-1;
//if(Nset[ite].IdOfTask==1)
//cout<<"------test-- "<<Nset[ite].ShowValueOfVariable('W')<<" "<<Nset[ite].ShowValueOfVariable('L')<<" "<<Nset[ite].ShowValueOfVariable('P')<<" \n";
Nset.erase(Nset.begin()+ite);

if(Nset.size()!=0)
{
    for(int p=0; p<Nset.size(); ++p)
    {    
        //cout<<"przed poziomem "<<ite+1<<endl;
        BF(Tasks_1, Nset, NTask, TabOrder1, p, tab, i+1);
    }
}
else
{
    int *tabpom=new int[NTask];
    for(int k=0; k<NTask; ++k)
    {
        tabpom[k]=TabOrder1[k];
        TabOrder1[k]=tab[k];
    }
            Fc=Objectivefunction(Tasks_1, NTask, TabOrder1);
        if(Fc<Fmax)
        {
            Fmax=Fc;
        }
        else
        {
            for(int k=0; k<NTask; ++k)
            {
                TabOrder1[k]=tabpom[k];
            }
        }
}
}



void BruteForce(shared_ptr<Task[]> Tasks_1, int NTask, shared_ptr<int[]> TabOrder1)
{
  
    int *tmpTabOrder = new int[NTask];
    vector <Task> Nset;

    for (int i=0; i<NTask; i++)
    {
        Nset.push_back(Tasks_1[i]);
    }

    for(int i=0; i<NTask; ++i)
    {
        BF(Tasks_1, Nset, NTask,  TabOrder1, i, tmpTabOrder, 0);
    }
}
