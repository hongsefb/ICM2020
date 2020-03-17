#ifndef IOSTREAM
    #define IOSTREAM
    #include<iostream>
#endif

#ifndef CMATH
    #define CMATH
    #include<cmath>
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

int FindTopTen(int a,int column);
void OutputCNN();

void OutputCNN()
{
    int Right_Player[4][11]={0};
    for(int i=1;i<=3;i++){
        for(int j=1,k=1;(j<=29)&&(k<=10);j=Right_Player[i][k]+1,k++){
            Right_Player[i][k]=FindTopTen(j,i);
        }
    }
    /*for(int i=1;i<=3;i++){
        for(int j=1;j<=10;j++){
            cout<<setw(5)<<Right_Player[i][j]<<"  ";
        }
        cout<<endl;
    }*/
    bool coll[30]={false};
    for(int i=1;i<=3;i++){
        for(int j=1;j<=10;j++){
            if(WhatOccupation(Right_Player[i][j])==i){
                coll[Right_Player[i][j]]=true;
            }
        }
    }

    #ifdef OUT_TO_FILE
    freopen("strategy.txt","w",stdout);
    #endif
    for(int i=1;i<=3;i++){
        for(int j=1;j<=10;j++){
            if(WhatOccupation(Right_Player[i][j])!=i&&!coll[Right_Player[i][j]]){
                cout<<Reverse_WhoIsIt(Right_Player[i][j])<<"->"<<Reverse_WhatOccupation(i)<<endl;
            }
        }
    }
    #ifdef OUT_TO_FILE
    fclose(stdout);
    #endif
}

int FindTopTen(int a,int column)
{
    while(occupation_rank[a][column]>10&&a<=29){
        a++;
    }
    if(a<=29){return a;}
}