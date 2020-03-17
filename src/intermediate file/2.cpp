#include <iostream>
#include <sstream>
using namespace std;
#define PassingSize 23430

struct
{
    short MatchID;
    short TeamID;
    short OriginPlayerID;
    short DestinationPlayerID;
    bool MatchPeriod; 
    double EventTime;
    short EventSubType;
    short EventOrigin_x, EventOrigin_y;
    short EventDestination_x, EventDestination_y;
} PassingNode[PassingSize];
int CountNum = 1;
int contbu[31][31] = {0};
int table[5] = {0, 0, 6, 16, 29};

void Separate_Data(string s)
{
    stringstream ss, ss2, ss3;
    string tmp1, tmp2;
    ss << s;
    ss >> PassingNode[CountNum].MatchID 
       >> PassingNode[CountNum].TeamID 
       >> tmp1 
       >> tmp2 
       >> PassingNode[CountNum].MatchPeriod 
       >> PassingNode[CountNum].EventTime 
       >> PassingNode[CountNum].EventSubType 
       >> PassingNode[CountNum].EventOrigin_x 
       >> PassingNode[CountNum].EventOrigin_y 
       >> PassingNode[CountNum].EventDestination_x 
       >> PassingNode[CountNum].EventDestination_y;
    if (isalpha(tmp1[0])){
        tmp1[0] = tmp1[0] - ('a' - 1) + '0';
        ss2 << tmp1;
        ss2 >> PassingNode[CountNum].OriginPlayerID;
        PassingNode[CountNum].OriginPlayerID = 
        (-PassingNode[CountNum].OriginPlayerID);
    }
    else{
        ss2 << tmp1;
        ss2 >> PassingNode[CountNum].OriginPlayerID;
    }
    if (isalpha(tmp2[0])){
        tmp2[0] = tmp2[0] - ('a' - 1) + '0';
        ss3 << tmp2;
        ss3 >> PassingNode[CountNum].DestinationPlayerID;
        PassingNode[CountNum].DestinationPlayerID = 
        (-PassingNode[CountNum].DestinationPlayerID);
    }
    else{
        ss3 << tmp2;
        ss3 >> PassingNode[CountNum].DestinationPlayerID;
    }
    CountNum++;
}

void do_it(short ori, short des)
{
    if ((ori % 100 == 0) && (des % 100 == 0)){
        contbu[WhoIsIt(ori)][WhoIsIt(des)]++;
    }
}

int WhoIsIt(int a)
{
    int fir, sec;
    if (a > 0){
        fir = a / 1000;
        sec = (a / 100) % 10;
        return table[sec] + fir;
    }
    if (a < 0){
        a = -a;
        fir = (a / 1000) + 9;
        sec = (a / 100) % 10;
        return table[sec] + fir;
    }
}

string Reverse_WhoIsIt(int a)
{
    string s;
    if (a <= 6){
        s += 'F';
        s += a + '0';
    }
    else{
        s += 'D';
        a -= 6;
        if (a <= 9){
            s += a + '0';
        }
        else if (a == 10){
            s += (a / 10) + '0';
            s += (a % 10) + '0';
        }
        else{
            s = "";
            s += 'M';
            a -= 10;
            if (a <= 9){
                s += a + '0';
            }
            else if ((a >= 10) && (a <= 13)){
                s += (a / 10) + '0';
                s += (a % 10) + '0';
            }
            else{
                s = "G1";
            }
        }
    }
    return s;
}
void PrintEdge()
{
    cout << "Source,Target,Type,Weight" << endl;
    for (int i = 1; i <= 30; i++)
    {
        for (int j = 1; j <= 30; j++)
        {
            if (contbu[i][j] > 0 && (i != j))
            {
                cout << Reverse_WhoIsIt(i) << "," 
                     << Reverse_WhoIsIt(j) << ",Directed," 
                     << contbu[i][j] << endl;
            }
        }
    }
}

int main()
{
    string OneLine;
    freopen("passingevents.csv", "r", stdin);
    while (cin >> OneLine){
        for (auto &i : OneLine){
            if (i == ','){i = ' ';}
        }
        Separate_Data(OneLine);
    }
    for (int i = 1; i <= PassingSize; i++){
        do_it(PassingNode[i].OriginPlayerID, 
              PassingNode[i].DestinationPlayerID);
    }
    freopen("edge.csv", "w", stdout);
    PrintEdge();
    return 0;
}