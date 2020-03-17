void dfs(int k,int n)
{
    for(int i=1;i<=3;i++)
    {
        if(pack[k]==false)
        {
            strategy[k]=i;//Problem
            pack[k]=true;
            if(k<n){dfs(k+1,n);}
            else 
            {
                int sum=0;
                for(int j=1;j<=28;j++){
                    sum+=occupation_rank[j][strategy[j]];
                }
                for(int b=1;b<=3;b++)
                {
                    strategy[n]=b;
                    sum+=occupation_rank[n][b];
                    if(sum<Min_Strategy_Num){
                        Min_Strategy_Num=sum;
                        for(int k=1;k<=29;k++){
                            Min_Strategy[k]=strategy[k];
                        }
                    }
                    sum-=occupation_rank[n][b];
                }
            }
            pack[i]=false;
        }
    }
}