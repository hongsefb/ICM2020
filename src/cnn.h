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

#include<algorithm>
#include<iomanip>
#include<cstring>

using namespace std;

#define CNNscale1 6
#define CNNscale2 5
#define CNNscale3 4

struct 
{
    int frequency=0;
    bool collected[39][2]={false};

}PlayingFrequency[31];
double kernel_1[CNNscale1+1][CNNscale2+1];
double kernel_2[CNNscale2+1][CNNscale3+1];
double teammate_behavior[31][7]={0};//1,2,3,8,9,11
double teammate_ability[31][6]={0};//speed,shot,pass,dribbling,defense
double teammate_occupation[31][5]={0};//1:F 2:D 3:M 4:G
int occupation_rank[30][5]={0};


void InputKernel();
void HandleFirstLayer();
void HandleSecondLayer();
void softmax(double* x, int row, int column);
void FindRank(double *ori,int *des,int nrow,int ncolumn,int mode);
int Ascending(const void * p, const void * q);
int Descending(const void * p, const void * q);


void InputCNN()
{
    InputKernel();
    HandleFirstLayer();
    softmax((double*)teammate_ability,31,6);

    #ifdef OUT_TO_FILE
    freopen("behavior.txt","w",stdout);
    #endif
    for (int i = 1; i<=30; i++){
        for (int j = 1; j<=6; j++){
            cout<<setw(9)<<teammate_behavior[i][j];
        }
        cout<<endl;
    }

    cout<<endl<<endl;

    #ifdef OUT_TO_FILE
    freopen("ability.txt","w",stdout);
    #endif
    for (int i = 1; i<=30; i++){
        teammate_ability[i][5]*=10;
    }
    for (int i = 1; i<=30; i++){
        for (int j = 1; j<=5; j++){
            teammate_ability[i][j]*=100;
            cout<<setw(9)<<teammate_ability[i][j];
        }
        cout<<endl;
    }

    cout<<endl<<endl;

    #ifdef OUT_TO_FILE
    freopen("occupation.txt","w",stdout);
    #endif
    HandleSecondLayer();
    for (int i = 1; i<=29; i++){
        for (int j = 1; j<=4; j++){
            cout<<setw(9)<<teammate_occupation[i][j];
        }
        cout<<endl;
    }

    FindRank((double *)teammate_occupation,(int *)occupation_rank,29,4,2);
    cout<<endl<<endl;

    #ifdef OUT_TO_FILE
    freopen("occupation_rank.txt","w",stdout);
    #endif
    for(int i=1;i<=29;i++){
        for(int j=1;j<=4;j++){
            cout<<setw(9)<<occupation_rank[i][j];
        }
        cout<<endl;
    }
}

void InputKernel()
{
    string s;
    freopen("kernel1.csv","r",stdin);
    for(int i=1;i<=CNNscale1;i++){
        cin>>s;
        for (auto& i : s) {
                if (i == ',') { i = ' '; }
            }
        stringstream ss;
        ss<<s;
        for(int j=1;j<=CNNscale2;j++){
            ss>>kernel_1[i][j];
        }
    }
    fclose(stdin);
    freopen("kernel2.csv","r",stdin);
    for(int i=1;i<=CNNscale2;i++){
        cin>>s;
        for (auto& i : s) {
                if (i == ',') { i = ' '; }
            }
        stringstream ss;
        ss<<s;
        for(int j=1;j<=CNNscale3;j++){
            ss>>kernel_2[i][j];
        }
    }
    fclose(stdin);
}


void HandleFirstLayer()
{
    for(int i=1;i<FullEventsSize;i++){
    if(FullEventsNode[i].OriginPlayerID%100==0){
        int a=WhoIsIt(FullEventsNode[i].OriginPlayerID);

        if(!PlayingFrequency[a].collected[FullEventsNode[i].MatchID][FullEventsNode[i].MatchPeriod]){
            PlayingFrequency[a].frequency++;
            PlayingFrequency[a].
            collected[FullEventsNode[i].MatchID][FullEventsNode[i].MatchPeriod]=true;
        }

        switch (FullEventsNode[i].EventType)
        {
        case 1:
            teammate_behavior[a][1]+=1.0;
            break;
        case 2:
            teammate_behavior[a][2]+=1.0;
            break;
        case 3:
            teammate_behavior[a][3]+=1.0;
            break;
        case 8:
            teammate_behavior[a][4]+=1.0;
            break;
        case 9:
            teammate_behavior[a][5]+=1.0;
            break;
        case 11:
            teammate_behavior[a][6]+=1.0;
            break;
        default:
            break;
            }
        }
    }
    for (int i = 1; i<=30; i++){
        for (int j = 1; j<=6; j++){
            teammate_behavior[i][j]/=PlayingFrequency[i].frequency;
            teammate_behavior[i][j]*=100.0;
            if(teammate_behavior[i][j]>0.000001){
            teammate_behavior[i][j]=log2(teammate_behavior[i][j]);}
        }
    }
    for(int j=1;j<=6;j++){
        for(int i=1;i<=30;i++){
            for(int k=1;k<=5;k++){
                teammate_ability[i][k]+=teammate_behavior[i][j]*kernel_1[j][k];
            }
        }
    }
}

void HandleSecondLayer()
{
    for(int j=1;j<=5;j++){
        for(int i=1;i<=30;i++){
            for(int k=1;k<=4;k++){
                teammate_occupation[i][k]+=kernel_2[j][k]*teammate_ability[i][j];
            }
        }
    }
}

void softmax(double *x,int row, int column)
{
    for (int j = 0; j < row; ++j)
    {
        double max = 0.0;
        double sum = 0.0;
        for (int k = 0; k < column; ++k)
            if (max < x[k + j*column])
                max = x[k + j*column];
        for (int k = 0; k < column; ++k)
        {
            x[k + j*column] = exp(x[k + j*column] - max);// prevent data overflow
            sum += x[k + j*column];
        }
        for (int k = 0; k < column; ++k) x[k + j*column] /= sum;
    }
}

void FindRank(double *ori,int *des,int nrow,int ncolumn,int mode)
{
    switch (mode)
    {
    case 1://row_max
        for(int i=1;i<=nrow;i++){
            size_t b = (sizeof(double)) * ((size_t)ncolumn + 1);
            double* a=(double *)malloc(b);
            for(int j=1;j<=ncolumn;j++){
                a[j]=ori[i*(ncolumn+1)+j];
            }
            qsort(a+1,ncolumn,sizeof(double),Descending);
            for(int j=1;j<=ncolumn;j++){
                for(int k=1;k<=ncolumn;k++){
                    if(a[k]==ori[i*(ncolumn+1)+j]){
                        des[i*(ncolumn+1)+j]=k;
                        break;
                    }
                }
            }
        }
        break;
    case 2://column_max
        for(int i=1;i<=ncolumn;i++){
            size_t b = (sizeof(double)) * ((size_t)nrow + 1);
            double* a=(double *)malloc(b);
            for(int j=1;j<=nrow;j++){
                a[j]=ori[j*(ncolumn+1)+i];
            }
            sort(a+1,a+nrow+1,greater<double>());
            for(int j=1;j<=nrow;j++){
                for(int k=1;k<=nrow;k++){
                    if(a[k]==ori[j*(ncolumn+1)+i]){
                        des[j*(ncolumn+1)+i]=k;
                        break;
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}

int Ascending(const void * p, const void * q)
{
    return *(double *)q<*(double *)p;
}

int Descending(const void * p, const void * q)
{
    return *(double *)p>*(double *)q;
}
