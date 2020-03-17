#ifndef IOSTREAM
    #define IOSTREAM
    #include<iostream>
#endif
#include<sstream>
using namespace std;

#define MatchesSize 39
#define PassingSize 23430
#define FullEventsSize 59272

int CountNum = 1;
int table[5] = { 0,0,6,16,29 };

void Separate_Data(int mode);
void Separate_mode1(string s);
void Separate_mode2(string s);
void Separate_mode3(string s);
int WhoIsIt(int a);
string Reverse_WhoIsIt(int a);
int WhatOccupation(int a);
char Reverse_WhatOccupation(int a);


struct
{
    short MatchID;
    short OpponentID;
    short Outcome;//win:1; tie:0; loss:-1
    short OwnScore;
    short OpponentScore;
    bool Side;//home:True; away:False;
    short CoachID;
}MatchesNode[MatchesSize];

struct
{
    short MatchID;
    short TeamID;//Huskies:0; Other:OtherNum;
    short OriginPlayerID;//first num:player; second num:F D M G; Last two digits:Team
    short DestinationPlayerID;
    bool MatchPeriod;//1H:False; 2H:True
    double EventTime;
    /*
    EventSubType:
     1:'Head pass'  2:'Simple pass'  3:'Launch'
     4:'High pass'  5:'Hand pass'    6:'Smart pass'
     7:'Cross'
    */
    short EventSubType;
    short EventOrigin_x, EventOrigin_y;
    short EventDestination_x, EventDestination_y;
}PassingNode[PassingSize];

struct
{
    short MatchID;
    short TeamID;//Huskies:0; Other:OtherNum;
    short OriginPlayerID;
    short DestinationPlayerID;
    bool MatchPeriod;//1H:False; 2H:True
    double EventTime;
    /*
      EventType:
      1:'Free Kick'  2:'Duel'  3:'Pass'  4:'Others on the ball'
      5:'Foul'       6:'Goalkeeper leaving line'  7:'Offside'
      8:'Save attempt'  9:'Shot'  10:'Substitution'  11:'Interruption'
    */
    short EventType;
    /*
    EventSubType:
    1:'Goal kick'  2:'Air duel'  3:'Throw in'  4:'Head pass'
    5:'Ground loose ball duel'  6:'Simple pass'  7:'Launch'
    8:'High pass'  9:'Touch'  10:'Ground defending duel'
    11:'Hand pass'  12:'Ground attacking duel'  13:'Foul'
    14:'Free kick cross'  15:'Goalkeeper leaving line'  16:''
    17:'Free Kick'  18:'Smart pass'  19:'Cross' 20:'Save attempt'
    21:'Corner'  22:'Clearance'  23:'Shot'  24:'Acceleration'
    25:'Reflexes'  26:'Substitution'  27:'Late card foul'
    28:'Simulation'  29:'Free kick shot'  30:'Protest'  31:'Hand foul'
    32:'Penalty'  33:'Violent Foul'  34:'Whistle'  35:'Out of game foul'
    36:'Ball out of the field'  37:'Time lost foul'
    */
    short EventSubType;
    short EventOrigin_x, EventOrigin_y;
    short EventDestination_x, EventDestination_y;
}FullEventsNode[FullEventsSize];

void Separate_Data(int mode)
{
    string s;
    switch (mode)
    {
    case 1:
        freopen("matches.csv", "r", stdin);
        CountNum=1;
        for(int k=1;k<=38;k++) {
            cin>>s;
            for (auto& i : s) {
                if (i == ',') { i = ' '; }
            }
            Separate_mode1(s);
        }
        break;
    case 2:
        freopen("passingevents.csv", "r", stdin);
        CountNum=1;
        for(int k=1;k<=23429;k++) {
            cin>>s;
            for (auto& i : s) {
                if (i == ',') { i = ' '; }
            }
            Separate_mode2(s);
        }
        break;
    case 3:
        freopen("fullevents(rev).csv", "r", stdin);
        CountNum=1;
        for(int k=1;k<=59271;k++){
            cin>>s;
            for (auto& i : s) {
                if (i == ',') { i = ' '; }
            }
            Separate_mode3(s);
        }
        break;
    default:
        cout << "Invaild Mode.";
        break;
    }
    fclose(stdin);
}

void Separate_mode1(string s)
{
    stringstream ss;
    ss << s;
    ss >> MatchesNode[CountNum].MatchID
        >> MatchesNode[CountNum].OpponentID
        >> MatchesNode[CountNum].Outcome
        >> MatchesNode[CountNum].OwnScore
        >> MatchesNode[CountNum].OpponentScore
        >> MatchesNode[CountNum].Side
        >> MatchesNode[CountNum].CoachID;
    CountNum++;
}

void Separate_mode2(string s)
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
    if (isalpha(tmp1[0])) {
        tmp1[0] = tmp1[0] - ('a' - 1) + '0';
        ss2 << tmp1;
        ss2 >> PassingNode[CountNum].OriginPlayerID;
        PassingNode[CountNum].OriginPlayerID = (-PassingNode[CountNum].OriginPlayerID);
    }
    else {
        ss2 << tmp1;
        ss2 >> PassingNode[CountNum].OriginPlayerID;
    }
    if (isalpha(tmp2[0])) {
        tmp2[0] = tmp2[0] - ('a' - 1) + '0';
        ss3 << tmp2;
        ss3 >> PassingNode[CountNum].DestinationPlayerID;
        PassingNode[CountNum].DestinationPlayerID = (-PassingNode[CountNum].DestinationPlayerID);
    }
    else {
        ss3 << tmp2;
        ss3 >> PassingNode[CountNum].DestinationPlayerID;
    }
    CountNum++;
}

void Separate_mode3(string s)
{
    stringstream ss, ss2, ss3;
    string tmp1, tmp2;
    ss << s;
    ss >> FullEventsNode[CountNum].MatchID
        >> FullEventsNode[CountNum].TeamID
        >> tmp1
        >> tmp2
        >> FullEventsNode[CountNum].MatchPeriod
        >> FullEventsNode[CountNum].EventTime
        >> FullEventsNode[CountNum].EventType
        >> FullEventsNode[CountNum].EventSubType
        >> FullEventsNode[CountNum].EventOrigin_x
        >> FullEventsNode[CountNum].EventOrigin_y
        >> FullEventsNode[CountNum].EventDestination_x
        >> FullEventsNode[CountNum].EventDestination_y;
    if (isalpha(tmp1[0])) {
        tmp1[0] = tmp1[0] - ('a' - 1) + '0';
        ss2 << tmp1;
        ss2 >> FullEventsNode[CountNum].OriginPlayerID;
        FullEventsNode[CountNum].OriginPlayerID = (-FullEventsNode[CountNum].OriginPlayerID);
    }
    else {
        ss2 << tmp1;
        ss2 >> FullEventsNode[CountNum].OriginPlayerID;
    }
    if (isalpha(tmp2[0])) {
        tmp2[0] = tmp2[0] - ('a' - 1) + '0';
        ss3 << tmp2;
        ss3 >> FullEventsNode[CountNum].DestinationPlayerID;
        FullEventsNode[CountNum].DestinationPlayerID = (-FullEventsNode[CountNum].DestinationPlayerID);
    }
    else if (tmp2[0] == '-') { FullEventsNode[CountNum].DestinationPlayerID = 0; }
    else {
        ss3 << tmp2;
        ss3 >> FullEventsNode[CountNum].DestinationPlayerID;
    }
    CountNum++;

}

int WhoIsIt(int a)
{
    int fir, sec;
    if (a > 0) {
        fir = a / 1000;
        sec = (a / 100) % 10;
        return table[sec] + fir;
    }
    if (a < 0) {
        a = -a;
        fir = (a / 1000) + 9;
        sec = (a / 100) % 10;
        return table[sec] + fir;
    }
    cout<<"WhoIsIt";
    exit(1);
}

string Reverse_WhoIsIt(int a)
{
    string s,tmp;
    stringstream ss;
    if(a<=0){cout<<"Reverse_WhoIsIt";exit(1);}
    else if(a<=6){s="F";ss<<a;ss>>tmp;s=s+tmp;}
    else if(a<=16){a-=6;s="D";ss<<a;ss>>tmp;s=s+tmp;}
    else if(a<=29){a-=16;s="M";ss<<a;ss>>tmp;s=s+tmp;}
    else if(a==30){s="G1";}
    else{cout<<"Reverse_WhoIsIt";exit(1);}
    return s;
}

int WhatOccupation(int a)
{
    int b;
    if (a <= 6) {b=1;}
    else if(a<=16){b=2;}
    else if(a<=29){b=3;}
    else if(a==30){b=4;}
    else{cout<<"WhatOccupation";exit(1);}
    return b;
}

char Reverse_WhatOccupation(int a)
{
    if(a==1){return 'F';}
    else if(a==2){return 'D';}
    else if(a==3){return 'M';}
    else if(a==4){return 'G';}
    else{cout<<"Reverse_WhatOccupation";exit(1);}
}