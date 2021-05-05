#include <iostream>
#include <memory>
#include <vector>

#include "RandomNumberGenerator.h"
#include "Task.h"
//#include "Machine.h"
#include "Operation.h"
using namespace std;

int CmaxJ;
int imax=INT_MAX;
/* ###############     function:  SetStartParametrs  ##################\
   Used to set a performed time of each operations of each Tasks from  shared_ptr <Task[]>.

    Parameters:
   Randomg == RandomNumberGenerator object used to generate random number
   Tasks_1 == intelligent array of Task
   Ntask == Number of Task
   NMaschines == Number of machines
*/
void SetStartParametrs(RandomNumberGenerator Randomg, shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines);

/* ###############     function:  ShowParametrs  ##################\
   Used to show information about Task in order established in the TabOrder1

    Parameters:
   TabOrder1 == The order array created with shared_ptr
   Tasks_1 == intelligent array of Task
   Ntask == Number of Task
   NMaschines == Number of machines
*/
void ShowParametrs(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);

/* ###############     function:  ObjectiveFunction  ##################\
   Used to create schedule in order established in TabOrder1

    Parameters:
   TabOrder1 == The order array created with shared_ptr
   Tasks_1 == intelligent array of Task
   Ntask == Number of Task
   NMaschines == Number of machines
*/
int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);

/* ###############     function:  ObjectiveFunction  ##################\
   Used to establish order by Johnson algorithm for 2 machines problem


    Parameters:
   TabOrder1 == The order array created with shared_ptr
   Tasks_1 == intelligent array of Task
   Ntask == Number of Task
   NMaschines == Number of machines
*/
void JohnsonAlgorithm_FP2(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);

/* ###############     function:  ObjectiveFunction  ##################\
   Used to look for min value of performed time of each operations of each Task from TaskVector


    Parameters:
   TaskVector == The Task array created with vector
   Index_buffor == Pointer for array [2] which store subscripts of Task and operation
   SizeM == Number of machines
*/
int MinPerformedTime(vector<Task> TaskVector, int *Index_buffor, int SizeM);




void JohnsonAlgorithm_multiple_machines(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);


void BF(shared_ptr <Task[]> Tasks_1, vector<Task> Nset,int NTask,int NMaschines, shared_ptr <int []> TabOrder1, int ite, int *tab, int i);



void SimpleBruteForce(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);



int Bound(shared_ptr <Task[]> Tasks_1, vector<Task> Nset, vector<Task> Gset, int NMaschines);



void BnB(shared_ptr <Task[]> Tasks_1, vector<Task> Nset, vector<Task> Gset,int NTask, int NMaschines, shared_ptr <int []> TabOrder1, int ite, int *tab, int i);



void BranchAndBound(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1);

int main()
{

    int NumberTasks{0}, NumberMachines{0}, Seed{0}, i{0}, cmax{0};

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
    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << "cmax= " << cmax<<endl;
    // JohnsonAlgorithm_FP2(TaskTab, NumberTasks, NumberMachines, TabOrder);
    JohnsonAlgorithm_multiple_machines(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << "\n Johnson "<< NumberMachines<<" machines \n ";
    CmaxJ=ObjectiveFunction(TaskTab, NumberTasks, NumberMachines, TabOrder);
    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << "cmax= " << CmaxJ << endl<<endl<<endl;

    for(int i=0; i<NumberTasks; i++)
    {
        TabOrder[i]=i+1;
    }

    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);


    cout << "\n Brute Force "<< NumberMachines<<" machines \n ";
    SimpleBruteForce(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cmax=ObjectiveFunction(TaskTab, NumberTasks, NumberMachines, TabOrder);
    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << "cmax= " << cmax << endl<<endl<<endl;

    BranchAndBound(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << "\n Branch and Bound "<< NumberMachines<<" machines \n ";
    cmax=ObjectiveFunction(TaskTab, NumberTasks, NumberMachines, TabOrder);
    ShowParametrs(TaskTab, NumberTasks, NumberMachines, TabOrder);
    cout << "cmax= " << cmax << endl<<endl<<endl;
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



void JohnsonAlgorithm_FP2(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1)
{
    if(NMaschines==2)
    {
        auto l{0}, k{NTask}, i{0};
        vector <Task> Nset;
        int tab[2];

        for (i=0; i<NTask; i++)
        {
            Nset.push_back(Tasks_1[i]);

        }

        while(Nset.size()!=0)
        {
            MinPerformedTime(Nset,tab,NMaschines);
            /*cout<<"------------------test kodu--------------------------\n";

            cout<<NMaschines;
            cout<<"------------------test kodu--------------------------\n";*/
            if(Nset[tab[0]].Return_PerformedTime_Operation(0) < Nset[tab[0]].Return_PerformedTime_Operation(1))
                TabOrder1[l++]=Nset[tab[0]].Return_TaskID();

            else
                TabOrder1[(k--)-1]=Nset[tab[0]].Return_TaskID();

            Nset.erase(Nset.begin()+tab[0]);

        }
    }
    else
    {
        cout << "It's not a FP2! Number of machines must be 2!" << endl;
    }
}

void JohnsonAlgorithm_multiple_machines(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1)
{

    auto l{0}, k{NTask}, i{0};
    vector <Task> Nset;
    int tab[2];

    for (i=0; i<NTask; i++)
    {
        Nset.push_back(Tasks_1[i]);

    }

    if(NMaschines>=3)
    {
        while(Nset.size()!=0)
        {
            MinPerformedTime(Nset,tab,NMaschines);
            if(Nset[tab[0]].Return_PerformedTime_Operation(0)<Nset[tab[0]].Return_PerformedTime_Operation(NMaschines-1))
                TabOrder1[l++]=Nset[tab[0]].Return_TaskID();

            else
                TabOrder1[(k--)-1]=Nset[tab[0]].Return_TaskID();

            Nset.erase(Nset.begin()+tab[0]);

        }
    }
    else if(NMaschines==2)
    {
        JohnsonAlgorithm_FP2(Tasks_1, NTask, NMaschines,TabOrder1);
    }
    else
        cout<<"Wrong number of machines\n";

}




int MinPerformedTime(vector<Task> TaskVector, int *Index_buffor, int SizeM)
{
    auto i{0}, j{0}, minValue{1000000}, helpV{0};
    long sizeV=TaskVector.size();

    for(i=0; i<sizeV; i++)
    {
        helpV=min(minValue, TaskVector[i].Return_PerformedTime_Operation(j));
        if(minValue > helpV  )
        {
            minValue=helpV;
            Index_buffor[0]=i;
            Index_buffor[1]=j;
        }
    }
    for(i=0; i<sizeV; i++)
    {
        helpV=min(minValue, TaskVector[i].Return_PerformedTime_Operation(SizeM-1));
        if(minValue > helpV  )
        {
            minValue=helpV;
            Index_buffor[0]=i;
            Index_buffor[1]=j;
        }
    }
    return minValue;
}

void BF(shared_ptr <Task[]> Tasks_1, vector<Task> Nset,int NTask,int NMaschines, shared_ptr <int []> TabOrder1, int ite, int *tab, int i)
{
    auto  cc{0};
    tab[i]=Nset[ite].Return_TaskID();

    Nset.erase(Nset.begin()+ite);
    if(Nset.size()!=0)
    {
        for(int p=0; p<Nset.size(); ++p)
        {
            BF(Tasks_1, Nset,NTask,  NMaschines, TabOrder1, p, tab, i+1);
            // cout<<"przed poziomem "<<ite+1<<endl;
        }
    }
    else
    {
        int *tabpom=new int[NTask];
        for(int k=0; k<=NTask; ++k)
        {
            tabpom[k]=TabOrder1[k];
            TabOrder1[k]=tab[k];
        }
        cc=ObjectiveFunction(Tasks_1, NTask, NMaschines, TabOrder1);
        if(cc<imax)
        {
            imax=cc;
            //   cout<<imax<<endl;
            //  ShowParametrs(Tasks_1, NTask, NMaschines, TabOrder1);
        }
        else
        {

            for(int k=0; k<=NTask; ++k)
            {
                TabOrder1[k]=tabpom[k];

            }
        }
    }
}

void SimpleBruteForce(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1)
{
    auto  i{0};
    int *tmpTabOrder = new int[NTask];
    vector <Task> Nset;

    for (i=0; i<NTask; i++)
    {
        Nset.push_back(Tasks_1[i]);
    }

    for(int i=0; i<NTask; ++i)
    {
        BF(Tasks_1, Nset,NTask, NMaschines, TabOrder1, i, tmpTabOrder, 0);
    }
}

int Bound(shared_ptr <Task[]> Tasks_1, vector<Task> Nset, vector<Task> Gset, int NMaschines)
{
    auto maxCP{0};


//   cout<<"maxSuma----"<<maxSum<<endl;
    for(int i=0; i<NMaschines; ++i)
    {
        auto maxSum{0}, prepareSum{0};

        maxSum=Gset[Gset.size()-1].Return_TerminationTime_Operation(i);


        for(int j=0; j<Nset.size(); ++j)
        {
            prepareSum+=Nset[j].Return_PerformedTime_Operation(i);
        }
        /* cout<<"----- test ---\n";
         cout<<maxSum<<endl;
         cout<<"----- test 1---\n";
         cout<<prepareSum<<endl;*/
        if(maxCP<maxSum+prepareSum)
            maxCP=maxSum+prepareSum;
    }
    return maxCP;
}


void BnB(shared_ptr <Task[]> Tasks_1, vector<Task> Nset, vector<Task> Gset,int NTask, int NMaschines, shared_ptr <int []> TabOrder1, int ite, int *tab, int i)
{
    auto cc{0}, LB{0};
    tab[i]=Nset[ite].Return_TaskID();
    Gset.push_back(Nset[ite]);
    Nset.erase(Nset.begin()+ite);
    if(Nset.size()!=0)
    {
        LB=Bound(Tasks_1, Nset, Gset, NMaschines);

        if(LB<CmaxJ)
        {
            /* cout<<"LB-----"<<LB<<endl;
             cout<<"UB-----"<<CmaxJ<<endl;*/
            for(int p=0; p<Nset.size(); ++p)
            {
                BnB(Tasks_1, Nset, Gset, NTask, NMaschines, TabOrder1, p, tab, i+1 );
            }
        }
    }
    else
    {
        int *tabpom=new int[NTask];
        for(int k=0; k<=NTask; ++k)
        {
            tabpom[k]=TabOrder1[k];
            TabOrder1[k]=tab[k];
        }
        cc=ObjectiveFunction(Tasks_1, NTask, NMaschines, TabOrder1);
        if(cc<CmaxJ)
        {
            CmaxJ=cc;

        }
        else
        {

            for(int k=0; k<=NTask; ++k)
            {
                TabOrder1[k]=tabpom[k];

            }
        }
    }
}


void BranchAndBound(shared_ptr <Task[]> Tasks_1, int NTask, int NMaschines, shared_ptr <int []> TabOrder1)
{
    auto  i{0};
    int *tmpTabOrder = new int[NTask];
    vector <Task> Nset, Gset;


    for (i=0; i<NTask; i++)
    {
        Nset.push_back(Tasks_1[i]);
    }

    for(int i=0; i<NTask; ++i)
    {
        BnB(Tasks_1, Nset, Gset, NTask,  NMaschines, TabOrder1, i, tmpTabOrder, 0);
    }
}
