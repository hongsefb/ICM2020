#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

ifstream infile;

#define MatchesSize 39
#define PassingSize 23431
#define FullEventsSize 59273

struct MatchesNode
{
    short MatchID;
    short OpponentID;
    short Outcome;//win:1; tie:0; loss:-1
    short OwnScore;
    short OpponentScore;
    bool Side;//home:True; away:False;
    short CoachID;
};

struct PassingNode
{
    short MatchID;
    short TeamID;//Huskies:0; Other:OtherNum;
    string OriginPlayerID;
    string DestinationPlayerID;
    bool MatchPeriod;//1H:False; 2H:True
    double EventTime;
    /*
    EventSubType:
     1:'Head pass'  2:'Simple pass'  3:'Launch'
     4:'High pass'  5:'Hand pass'    6:'Smart pass'
     7:'Cross'
    */
    short EventSubType;
    short EventOrigin_x,EventOrigin_y;
    short EventDestination_x,EventDestination_y;
};

struct FullEventsNode
{
    short MatchID;
    short TeamID;//Huskies:0; Other:OtherNum;
    string OriginPlayerID;
    string DestinationPlayerID;
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
    short EventOrigin_x,EventOrigin_y;
    short EventDestination_x,EventDestination_y;
};

bool Process_data(string InFileName,int mode);
inline bool Separate_Data(string onelinedata,int mode,int count,MatchesNode (&Data)[39]);

int main()
{
    string FileName;
    cin>>FileName;
    if(!Process_data(FileName,1)){return -1;}
}

/*
mode 1:Maches
mode 2:PassingEvents
mode 3:FullEvents
*/

bool Process_data(string InFileName,int mode)
{
    int i=1;
    string onelinedata;
    infile.open(InFileName+".csv",ifstream::in);
    if(!infile.is_open()){return false;}
    switch (mode)
    {
    case 1:
        static MatchesNode Data[MatchesSize];
        infile>>onelinedata;
        while (infile>>onelinedata){
        if(!Separate_Data(onelinedata,mode,i,Data)){return false;}
        i++;
        }
        break;
    
    case 2:
        static PassingNode Data[PassingSize];
        break;
    
    case 3:
        static FullEventsNode Data[FullEventsSize];
        break;
    
    default:
        return false;
        break;
    }
    
    
}

inline bool Separate_Data(string onelinedata,int mode,int count,MatchesNode (&Data)[39])
{
    size_t ppos=0,pos=onelinedata.find(',');
    stringstream s;
    switch(mode){
        case 1:
            s<<onelinedata.substr(ppos,pos+1);
            s>>Data[count].MatchID;
            ppos=pos+1;pos=onelinedata.find(',',ppos);
            int tmp=ppos;
            while(!isdigit(onelinedata[tmp])){tmp++;}
            ppos=tmp;
            s<<onelinedata.substr(ppos,pos+1);
            s>>Data[count].OpponentID;
            ppos=pos+1;pos=onelinedata.find(',',ppos);
            if(onelinedata[ppos]=='w'){Data[count].Outcome=1;}
            else if(onelinedata[ppos]=='t'){Data[count].Outcome=0;}
            else if(onelinedata[ppos]=='l'){Data[count].Outcome=-1;}
            ppos=pos+1;pos=onelinedata.find(',',ppos);
            s<<onelinedata.substr(ppos,pos+1);
            s>>Data[count].OwnScore;
            ppos=pos+1;pos=onelinedata.find(',',ppos);
            s<<onelinedata.substr(ppos,pos+1);
            s>>Data[count].OpponentScore;
            ppos=pos+1;pos=onelinedata.find(',',ppos);
            if(onelinedata[ppos]=='h'){Data[count].Side=true;}
            else if(onelinedata[ppos]=='a'){Data[count].Side=false;}
            s<<onelinedata[onelinedata.length()];
            s>>Data[count].CoachID;
            break;
    }
    
}