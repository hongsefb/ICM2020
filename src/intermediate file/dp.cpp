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

int sum=0;

void dfs(int k,int n)
{
    if(k>n){
        if(sum<Min_Strategy_Num){
            Min_Strategy_Num=sum;
            for(int k=1;k<=29;k++){
                Min_Strategy[k]=strategy[k]; 
            }
        }
        return;
    }
    else{
        for(int i=1;i<=3;i++){
            strategy[k]=i;
            sum+=occupation_rank[k][strategy[k]];
            dfs(k+1,n);
            sum-=occupation_rank[k][strategy[k]];
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