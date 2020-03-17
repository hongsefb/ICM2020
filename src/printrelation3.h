#include<iostream>
#ifndef DATACORE
    #define DATACORE
    #include"datacore.h"
#endif
using namespace std;

bool matrix[12][38];
void PrintFERelation()
{
for(int i=1;i<PassingSize;i++){
        matrix[FullEventsNode[i].EventType]
              [FullEventsNode[i].EventSubType]=true;
    }
    freopen("relation.txt", "w", stdout);
    for(int i=1;i<=11;i++){
        cout<<i<<": ";
        for(int j=1;j<=37;j++){
            if(matrix[i][j]){cout<<j<<" ";}
        }
        cout<<endl;
    }
}
