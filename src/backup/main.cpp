//#define OUT_TO_FILE

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

using namespace std;

int main()
{
    for(int i=1;i<=3;i++){
        Separate_Data(i);
    }
    
}