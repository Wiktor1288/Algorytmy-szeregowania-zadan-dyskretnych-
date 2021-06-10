#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include "RandomNumberGenerator.h"
#include "Task.h"
#include "Operation.h"
#include <math.h>
using namespace std;

void SetStartParametrs(RandomNumberGenerator Randomg, shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines);
int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);
void NEHAlgorithm(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);
int ObjectiveFunction(vector <Task> Tasks_1, int NTask, int NMaschines, vector <int> TabOrder1);
void ShowParametrs(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);
void simulatedAnnealing(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);
void swapVector(vector <int> &VectorToSwap, int i, int j);
struct W_set
{
    int W;
    int j;
};

 
struct CustomQueue{

    bool operator ()( W_set & set1, W_set & set2){

        if( set1.W <= set2.W) { return true; }
    
        if(  set1.W > set2.W) { return false; }

        return false;
    }

};

//Custom type 
typedef std::priority_queue < W_set, std::vector < W_set >, CustomQueue > OrderByW;


int main()
{

    int NumberTasks{0}, NumberMachines{0}, Seed{0}, i{0}, cmax{0}, cmax1{0} ;
    float PRQ{0.0};

    cout << "Hello! I solve FP problem \n"
         << "Set the number of task: ";
    cin >> NumberTasks;
    cout << "Set the number of machines: ";
    cin >> NumberMachines;
    cout << "Set the seed: ";
    cin >> Seed;

    RandomNumberGenerator Random1(Seed);
    shared_ptr <Task []> TaskTab(new Task[NumberTasks]);
    shared_ptr <int []> TabOrder(new int[NumberTasks]);

    for(i=0; i<NumberTasks; i++)
        TabOrder[i]=i+1;
    for(i=0; i<NumberTasks; i++)
        TaskTab[i].TaskInit(NumberMachines);


    SetStartParametrs(Random1, TaskTab, NumberTasks, NumberMachines);
    cmax=ObjectiveFunction(TaskTab, NumberTasks, NumberMachines, TabOrder);
    NEHAlgorithm(TaskTab, NumberTasks, NumberMachines, TabOrder);
    
    cmax1=ObjectiveFunction(TaskTab, NumberTasks, NumberMachines, TabOrder);
    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << cmax1 << endl;
    
        

    simulatedAnnealing(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cmax=ObjectiveFunction(TaskTab, NumberTasks, NumberMachines, TabOrder);
    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);
    
    cout << cmax << endl ;

    PRQ=(float)((cmax-cmax1)*100)/cmax1;
    cout << "PRQ: " << PRQ;
    return 0;
}


void SetStartParametrs(RandomNumberGenerator Randomg, shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines)
{
    auto i{0}, j{0};

    for(i=0; i<NTask; i++)
    {
        for(j=0; j<NMaschines; j++)
        {
            Tasks_1[i].Add_PerformedTime_Operation(Randomg.nextInt(1,29),j);
        }
    }
}


void ShowParametrs(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines,shared_ptr <int []> TabOrder1)
{
    auto i{0}, j{0};

    for(i=0; i<NTask; i++)
    {
        cout << "ID: " << TabOrder1[i] << endl;
        for ( j=0; j<NMaschines; j++)
        {
            cout << j+1 << " Op: p= " << Tasks_1[TabOrder1[i]-1].Return_PerformedTime_Operation(j) << "   " <<
                 Tasks_1[TabOrder1[i]-1].Return_StartTime_Operation(j) << "   " <<
                 Tasks_1[TabOrder1[i]-1].Return_TerminationTime_Operation(j);
            cout << " \n";
        }
        cout << endl;

    }
}

int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1)
{

    auto i{0}, j{0}, Hp{0}, Hs{0}, Ht{0}, H1{0};
    for(j=0; j<NTask; j++)
    {
        Ht=0;
        for(i=0; i<NMaschines; i++)
        {
            if(j==0)
            {
                Hp=Tasks_1[TabOrder1[j]-1].Return_PerformedTime_Operation(i);
                Tasks_1[TabOrder1[j]-1].Add_StartTime_Operation(Ht,i);
                Hs=Tasks_1[TabOrder1[j]-1].Return_StartTime_Operation(i) ;
                Tasks_1[TabOrder1[j]-1].Add_TerminationTime_Operation(Hs+Hp,i);
                Ht=Tasks_1[TabOrder1[j]-1].Return_TerminationTime_Operation(i);
            }
            else
            {
                H1=Tasks_1[TabOrder1[j-1]-1].Return_TerminationTime_Operation(i);
                Hp=Tasks_1[TabOrder1[j]-1].Return_PerformedTime_Operation(i);
                Tasks_1[TabOrder1[j]-1].Add_StartTime_Operation(max(Ht,H1),i);
                Hs=Tasks_1[TabOrder1[j]-1].Return_StartTime_Operation(i) ;
                Tasks_1[TabOrder1[j]-1].Add_TerminationTime_Operation(Hs+Hp,i);
                Ht=Tasks_1[TabOrder1[j]-1].Return_TerminationTime_Operation(i);
            }
        }
    }

    return Ht;

}


int ObjectiveFunction(vector <Task> Tasks_1, int NTask, int NMaschines, vector <int> TabOrder1){

     auto i{0}, j{0}, Hp{0}, Hs{0}, Ht{0}, H1{0};
    for(j=0; j<NTask; j++)
    {
        Ht=0;
        for(i=0; i<NMaschines; i++)
        {
            if(j==0)
            {
                Hp=Tasks_1[TabOrder1[j]-1].Return_PerformedTime_Operation(i);
                Tasks_1[TabOrder1[j]-1].Add_StartTime_Operation(Ht,i);
                Hs=Tasks_1[TabOrder1[j]-1].Return_StartTime_Operation(i) ;
                Tasks_1[TabOrder1[j]-1].Add_TerminationTime_Operation(Hs+Hp,i);
                Ht=Tasks_1[TabOrder1[j]-1].Return_TerminationTime_Operation(i);
            }
            else
            {
                H1=Tasks_1[TabOrder1[j-1]-1].Return_TerminationTime_Operation(i);
                Hp=Tasks_1[TabOrder1[j]-1].Return_PerformedTime_Operation(i);
                Tasks_1[TabOrder1[j]-1].Add_StartTime_Operation(max(Ht,H1),i);
                Hs=Tasks_1[TabOrder1[j]-1].Return_StartTime_Operation(i) ;
                Tasks_1[TabOrder1[j]-1].Add_TerminationTime_Operation(Hs+Hp,i);
                Ht=Tasks_1[TabOrder1[j]-1].Return_TerminationTime_Operation(i);
            }
        }
    }

    return Ht;
}



void NEHAlgorithm(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1){

    auto k{0}, i{0}, sum{0}, j{0};
    W_set *Help1=new W_set[NTask];
    OrderByW Wset, Helpset;
    vector <Task> VectorHelp1;
    vector <int> orderhelp1, orderhelp2, orderhelp3;


    for(i=0 ;i<NTask; i++){
        sum=0;
        for(j=0; j<NMaschines; j++){
            sum += Tasks_1[i].Return_PerformedTime_Operation(j);
        }
        Help1[i].j=i+1;
        Help1[i].W=sum;
        Wset.push(Help1[i]);
       
    }

    Helpset=Wset;
    while (Wset.size()!=0)
    {
        j=Wset.top().j;
        cout << j << endl;
        orderhelp1.insert(orderhelp1.begin(), k+1);
 
        VectorHelp1.push_back(Tasks_1[j-1]);
       
        orderhelp3=orderhelp1;
        for(i=0; i <= k; i++){
            
            orderhelp2=orderhelp3;
            orderhelp2.erase(orderhelp2.begin()+0);
            orderhelp2.insert(orderhelp2.begin() + i, k+1);
        
            if(ObjectiveFunction(VectorHelp1, VectorHelp1.size(), NMaschines, orderhelp2) <
                                                ObjectiveFunction(VectorHelp1, VectorHelp1.size(), NMaschines, orderhelp1))
            {
              orderhelp1=orderhelp2;
            }

            
  
            
            orderhelp2.erase(orderhelp2.begin() + i);

        }
        
        orderhelp2.push_back(k+1);
        orderhelp2=orderhelp1;
        Wset.pop();
        k++;
    }
   
   for(i=0; i<NTask; i++){
        TabOrder1[orderhelp1[i]-1]=Helpset.top().j;
        Helpset.pop();
     }
}


void simulatedAnnealing(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1){

    

    auto T{300}, i{0}, k{0}, Tend{0}, L{200}, j{0}, Cmax1{0}, Cmax2{0}, DeltaCmax{0};
    auto r{0.00};
    RandomNumberGenerator Random1(132);
    
    vector <int> orderhelp1, orderhelp2, orderhelp3;
    vector <Task> VectorHelp1;

    for(i=0; i<NTask; i++){
        orderhelp1.push_back(i+1);
        VectorHelp1.push_back(Tasks_1[i]);
    } 
    orderhelp3=orderhelp1;
   
    while(T>Tend){
        for(k = 1; k < L; k++){
            do{
                i=Random1.nextInt(0,NTask-1);
                j=Random1.nextInt(0,NTask-1);
            } while( i == j);
            orderhelp2=orderhelp1;
            swapVector(orderhelp2, i, j);
            Cmax1 = ObjectiveFunction(VectorHelp1, NTask, NMaschines, orderhelp2);
            Cmax2 = ObjectiveFunction(VectorHelp1, NTask, NMaschines, orderhelp1);
            
            if( Cmax1 > Cmax2){
                DeltaCmax=Cmax1-Cmax2;
                r=Random1.nextFloat(0 , 1);
                if(r >= exp(DeltaCmax/T)){
                    orderhelp2=orderhelp1;
                }
            }
            orderhelp1=orderhelp2;
            if(ObjectiveFunction(VectorHelp1, NTask, NMaschines, orderhelp1) < ObjectiveFunction(VectorHelp1, NTask, NMaschines, orderhelp3)){
                orderhelp3=orderhelp1;
            }
            

        }

T-=1;



    }

    for(i=0; i<NTask; i++){
        TabOrder1[i]=orderhelp3[i];
    }


}


void swapVector(vector <int> &VectorToSwap, int i, int j){

    auto k{0};

    k=VectorToSwap[j];
    VectorToSwap[j]=VectorToSwap[i];
    VectorToSwap[i]=k;
}
