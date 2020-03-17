#ifndef IOSTREAM
    #define IOSTREAM
    #include<iostream>
#endif

#ifndef DATACORE
    #define DATACORE
    #include"datacore.h"
#endif

using namespace std;

string one[7]={"",
               "Data1",
               "Data2",
               "Data3",
               "Data4",
               "Data5",
               "Data6"};
string two[6]={"",
               "Speed",
               "Shot",
               "Pass",
               "Dribbling",
               "Defense"};
string three[5]={"",
                 "Forward",
                 "Midfield",
                 "Defender",
                 "Goalkeeper"};

void PrintCNN()
{
    freopen("CNNnet.csv","w",stdout);
    cout<<"Source,Target,Type"<<endl;
    for(int i=1;i<=6;i++){
        for(int j=1;j<=5;j++){
            cout<<one[i]<<","<<two[j]<<",Directed"<<endl;
        }
    }
    for(int i=1;i<=5;i++){
        for(int j=1;j<=4;j++){
            cout<<two[i]<<","<<three[j]<<",Directed"<<endl;
        }
    }
    for(int i=1;i<=4;i++){
        cout<<three[i]<<",Output,Directed"<<endl;
    }
}