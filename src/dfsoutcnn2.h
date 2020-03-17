#ifndef IOSTREAM
    #define IOSTREAM
    #include<iostream>
#endif

#ifndef DATACORE
    #define DATACORE
    #include"datacore.h"
#endif

#ifndef CNN
    #define CNN
    #include"cnn.h"
#endif
using namespace std;

int Min_Strategy[30]={0};

void OutputCNN(int Iteration_Times);
int FindMin(int a,int b,int c);
void PrintOccDiff(int Iteration_Times);


void OutputCNN(int Iteration_Times)
{
    #ifdef OUT_TO_FILE
    freopen("strategy.txt","w",stdout);
    #endif
    for(int i=1;i<=Iteration_Times;i++){
        int tmp;
        tmp=FindMin(occupation_rank[i][1],
                     occupation_rank[i][2],
                     occupation_rank[i][3]);
        if(abs(occupation_rank[i][WhatOccupation(i)]-occupation_rank[i][tmp])>1){
            Min_Strategy[i]=tmp;
        }
        else{Min_Strategy[i]=WhatOccupation(i);}
    }
    PrintOccDiff(Iteration_Times);
    #ifdef OUT_TO_FILE
    rewind(stdout);
    fclose(stdout);
    #endif
}

int FindMin(int a,int b,int c)
{
    int index=1;
    if(a<=b){
        if(a<=c){index=1;}
        else{index=3;}
    }
    else{
        if(b<=c){index=2;}
        else{index=3;}
    }
    return index;
}

void PrintOccDiff(int Iteration_Times)
{
    for(int i=1;i<=Iteration_Times;i++){
        if(WhatOccupation(i)!=Min_Strategy[i]){
            cout<<Reverse_WhoIsIt(i)<<"->"
                <<Reverse_WhatOccupation(Min_Strategy[i])<<endl;
        }
    }
}