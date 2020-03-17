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

void OutputCNN(int Iteration_Times);
void dfs(int k,int n);
void PrintOccDiff();

int strategy[30]={0};
int Min_Strategy_Num=0xfffffff;
int Min_Strategy[30]={0};
int DfsSum=0;

void OutputCNN(int Iteration_Times)
{
    memset(strategy,0,sizeof(strategy));
    dfs(1,Iteration_Times);
    for(int k=1;k<=29;k++){
        cout<<Min_Strategy[k]<<" ";
    }
    cout<<endl<<endl;
    #ifdef OUT_TO_FILE
    freopen("strategy.txt","w",stdout);
    #endif
    PrintOccDiff();
    #ifdef OUT_TO_FILE
    rewind(stdout);
    fclose(stdout);
    #endif
}

void dfs(int k,int n)
{
    if(k>n){
        if(DfsSum<Min_Strategy_Num){
            Min_Strategy_Num=DfsSum;
            for(int k=1;k<=29;k++){
                Min_Strategy[k]=strategy[k]; 
            }
        }
        return;
    }
    else{
        for(int i=1;i<=3;i++){
            strategy[k]=i;
            DfsSum+=occupation_rank[k][strategy[k]];
            dfs(k+1,n);
            DfsSum-=occupation_rank[k][strategy[k]];
        }
    }
    return;
}

void PrintOccDiff()
{
    for(int i=1;i<=29;i++){
        if(WhatOccupation(i)!=Min_Strategy[i]){
            cout<<Reverse_WhoIsIt(i)<<"->"
                <<Reverse_WhatOccupation(Min_Strategy[i])<<endl;
        }
    }
}