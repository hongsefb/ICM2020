#include<iostream>
    #ifndef DATACORE
        #define DATACORE
        #include"datacore.h"
    #endif

using namespace std;

int contbu[31][31] = { 0 };

void CalcPass(short ori, short des);
void PrintEdge();
void PrintTheTalbe();

void CalcPass(short ori, short des)
{
    if ((ori % 100 == 0) && (des % 100 == 0)) {
        contbu[WhoIsIt(ori)][WhoIsIt(des)]++;
    }
}

void PrintTheTalbe()
{
    PrintEdge();
    PrintNode();
}

void PrintNode()
{
    freopen("node.csv", "w", stdout);
    cout << "Id,Lable" << endl;
    for (int i = 1; i <= 30; i++) {
        cout<<i<<","<<Reverse_WhoIsIt(i);
    }
    fclose(stdout);
}

void PrintEdge()
{
    freopen("edge.csv", "w", stdout);
    cout << "Source,Target,Type,Weight" << endl;
    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 30; j++) {
            if (contbu[i][j] > 0&&(i!=j)) {
                cout << Reverse_WhoIsIt(i) << "," 
                     << Reverse_WhoIsIt(j) << ",Directed," 
                     << contbu[i][j] << endl;
            }
        }
    }
    fclose(stdout);
}