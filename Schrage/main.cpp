#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include "RandomNumberGenerator.h"
#include "compareTasks.hpp"
#include "Zadania.hpp"
using namespace std;

typedef std::priority_queue < Task, std::vector < Task >, TaskComparingTimeP > QueueOfTimeP;
typedef std::priority_queue < Task, std::vector < Task >, TaskComparingTimeH > QueueOfTimeH;



void AddTasksParametrs(RandomNumberGenerator Random_2, shared_ptr <Task[]> Tasks_1, int size_1);
int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);
int LookforMinR(vector<Task> TaskVector);
int LookforMaxH(vector<Task> TaskVector);
void ShowInformation(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);
shared_ptr <int []>  SchrageAlgorithm(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);
shared_ptr <int []>  SchrageAlgorithmQueue(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);
void SchragePMTN(shared_ptr <Task[]> Tasks_1, int size_1);


int main(){

    auto i{0}, Number{0}, SeedValue{0};


    cout << "Podaj ilość zadań:  " ;
    cin >> Number;
    cout << endl << "Podaj źródło:  ";
    cin >> SeedValue;

    RandomNumberGenerator Random_1(SeedValue);
    shared_ptr <Task[]> TaskTab(new Task[Number]);
    shared_ptr <int []> TabOrder(new int[Number]);
    
    
    for(i=0; i<Number; i++)
        TabOrder[i]=i;
    cout << "Zadania wygenerowane z danymi: " << endl;
    AddTasksParametrs(Random_1, TaskTab, Number);
    auto Cmaxx=ObjectiveFunction(TaskTab,TabOrder,Number);
    ShowInformation(TaskTab,TabOrder,Number);
    cout << endl << endl << "Cmax:  " << Cmaxx << endl;

    cout << "Schrage z MIN MAX: " << endl;
    TabOrder=SchrageAlgorithm(TaskTab,TabOrder,Number);
    Cmaxx=ObjectiveFunction(TaskTab,TabOrder,Number);
    ShowInformation(TaskTab,TabOrder,Number);
    cout << endl << endl << "Cmax:  " << Cmaxx << endl;

    cout << "Schrage z Kolejka: " << endl;
    cout <<endl;
    TabOrder=SchrageAlgorithmQueue(TaskTab,TabOrder,Number);
    Cmaxx=ObjectiveFunction(TaskTab,TabOrder,Number);
    ShowInformation(TaskTab,TabOrder,Number);
    cout << endl << endl << "Cmax:  " << Cmaxx << endl;

    
    SchragePMTN(TaskTab,Number);

    return 0;
}



void AddTasksParametrs(RandomNumberGenerator Random_2, shared_ptr <Task[]> Tasks_1, int size_1)
{
    auto i{0}, A{0}, X{29};

    for ( i = 0; i < size_1; i++){
        Tasks_1[i].AddTExecution(Random_2.nextInt(1,29));
        A=A+Tasks_1[i].ShowValueOfVariable('E');
    }
    X=A;
    for ( i = 0; i < size_1; i++){
        Tasks_1[i].AddTPripare(Random_2.nextInt(1,A));
    }
    for ( i = 0; i < size_1; i++){
        Tasks_1[i].AddTHandober(Random_2.nextInt(1,X));
    }
}

int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder_1, int size_1){
    auto i{0}, Cmax{0};

    Tasks_1[TabOrder_1[0]].AddStartMoment(Tasks_1[TabOrder_1[0]].ShowValueOfVariable('P'));
    Tasks_1[TabOrder_1[0]].AddTermiantion();
    Cmax=Tasks_1[TabOrder_1[0]].ShowValueOfVariable('T')+Tasks_1[TabOrder_1[0]].ShowValueOfVariable('H');
    for(i=1; i<size_1; i++){
        Tasks_1[TabOrder_1[i]].AddStartMoment(max(Tasks_1[TabOrder_1[0]].ShowValueOfVariable('P'), Tasks_1[TabOrder_1[i-1]].ShowValueOfVariable('T')));
        Tasks_1[TabOrder_1[i]].AddTermiantion();
        Cmax=max(Cmax,Tasks_1[TabOrder_1[i]].ShowValueOfVariable('T')+Tasks_1[TabOrder_1[i]].ShowValueOfVariable('H'));
    }

    return Cmax;
}


void ShowInformation(shared_ptr <Task[]> TaskTab, shared_ptr <int []> TabOrder, int size_1){
    auto i{0};
        cout << "ID:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('I') << " | ";
    }

    cout << endl << "r:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('P') << " | ";
    }

    cout << endl << "p:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('E') << " | ";
    }

    cout << endl << "q:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('H') << " | ";
    }

    cout << endl << "S:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('M') << " | ";
    }

    cout << endl << "C:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('T') << " | ";
    }

    cout << endl << "C+q:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('T')+TaskTab[TabOrder[i]].ShowValueOfVariable('H') << " | ";
    }

}


shared_ptr <int []>  SchrageAlgorithm(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1){

    auto k{0}, t{0}, i{1},j{0};
    vector <Task> Gset;
    vector <Task> Nset;
    
    
    for (i=0; i<size_1; i++){
        Nset.push_back(Tasks_1[i]);
    }


    
    t=Nset[LookforMinR(Nset)].ShowValueOfVariable('P');
    

    while(Gset.size()!=0 || Nset.size()!=0){
        while( Nset.size()!=0 && Nset[LookforMinR(Nset)].ShowValueOfVariable('P')<=t){
            j=LookforMinR(Nset);
            Gset.push_back(Nset[j]);
            Nset.erase(Nset.begin()+j);
        }
        if(Gset.size()!=0){
            j=LookforMaxH(Gset);
            TabOrder[k]=Gset[j].ShowValueOfVariable('I')-1;
            t+=Gset[j].ShowValueOfVariable('E');
            Gset.erase(Gset.begin()+j);
            k+=1;
        }
        else{
            t=Nset[LookforMinR(Nset)].ShowValueOfVariable('P');
        }

    }


    return TabOrder;

}


int LookforMinR(vector<Task> TaskVector){
    auto i{0}, minValue{0},x{0};
    int sizeV=TaskVector.size();
    minValue=TaskVector[0].ShowValueOfVariable('P');
    for(i=0; i<sizeV; i++)
       minValue = min(minValue,TaskVector[i].ShowValueOfVariable('P'));

    for(i=0; i<sizeV; i++){
        if(TaskVector[i].ShowValueOfVariable('P')==minValue){
            x=i;
            break;
        }
            
    }

    return x;
}

int LookforMaxH(vector<Task> TaskVector){
    auto i{0}, maxValue{0},x{0};
    int sizeV=TaskVector.size();
    maxValue=TaskVector[0].ShowValueOfVariable('H');
    for(i=1; i<sizeV; i++)
       maxValue = max(maxValue ,TaskVector[i].ShowValueOfVariable('H'));

    for(i=0; i<sizeV; i++){
        if(TaskVector[i].ShowValueOfVariable('H')==maxValue){
            x=i;
            break;
        }
    }

    return x;
}


shared_ptr <int []>  SchrageAlgorithmQueue(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1){
    auto k{0}, t{0}, i{1};
    QueueOfTimeP Nset;
    QueueOfTimeH Gset;
    
    for(i=0; i<size_1; i++){
        Nset.push(Tasks_1[i]);
    }
    
   Task TaskForHelp1=Nset.top();
   Task TaskForHelp2=Nset.top();
    

    while(Gset.size()!=0 || Nset.size()!=0){
        while( Nset.size()!=0 && TaskForHelp1.ShowValueOfVariable('P')<=t){
            Gset.push(TaskForHelp1);
            Nset.pop();
            TaskForHelp1=Nset.top();
        }
        if(Gset.size()!=0){
            TaskForHelp2=Gset.top();
            TabOrder[k]=TaskForHelp2.ShowValueOfVariable('I')-1;
            t+=TaskForHelp2.ShowValueOfVariable('E');
            Gset.pop();
            k+=1;
        }
        else{
            t=TaskForHelp1.ShowValueOfVariable('P');
        }
    }
    return TabOrder;
}


void SchragePMTN(shared_ptr <Task[]> Tasks_1, int size_1){
    auto k{0}, t{0}, i{1}, Cmax{0};
    QueueOfTimeP Nset;
    QueueOfTimeH Gset;
    vector <int> TabOrder, Tabp;
    for(i=0; i<size_1; i++){
        Nset.push(Tasks_1[i]);
    }
    
    Task TaskForHelp1=Nset.top();
    Task TaskForHelp2=Nset.top();
   

    while(Gset.size()!=0 || Nset.size()!=0){
        while( Nset.size()!=0 && (TaskForHelp1=Nset.top()).ShowValueOfVariable('P')<=t){
            Gset.push(TaskForHelp1);
            Nset.pop();
            if(TaskForHelp1.ShowValueOfVariable('H')> TaskForHelp2.ShowValueOfVariable('H')){
                TaskForHelp2.AddTExecution(t-TaskForHelp1.ShowValueOfVariable('P'));
                t=TaskForHelp1.ShowValueOfVariable('P');
                
                if (TaskForHelp2.ShowValueOfVariable('E')>0){
                    Gset.push(TaskForHelp2);
                } 
            }
            
        }
        if(Gset.size()!=0){
            TaskForHelp2=Gset.top();
            TabOrder.push_back(TaskForHelp2.ShowValueOfVariable('I'));
            Tabp.push_back(t);
            t+=TaskForHelp2.ShowValueOfVariable('E');
            Gset.pop();
            k+=1;
            Cmax=max(Cmax,t+TaskForHelp2.ShowValueOfVariable('H'));
        }
        else{
            t=(TaskForHelp1=Nset.top()).ShowValueOfVariable('P');
        }
    }
    
    int ka=TabOrder.size();
    int ak=Tabp.size();
    
    cout << endl <<"Schrage z przerwaniami" << endl << "ID: ";
    for(i=0; i<ka; i++)
    {
        cout<< TabOrder[i] <<" | ";
    }
    
    cout <<endl << "Przerwanie: ";
    for(i=0; i<ak; i++)
    {
        cout<< Tabp[i] << " | ";
    }
    cout << endl << "Cmax: " <<Cmax << endl;
    
}