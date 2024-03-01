#include <iostream>
#include "CSweeper.h"
#if _WIN32 || _WIN64
#include <windows.h>
#else
//dont
#endif
int ReadTutorial = 0;
int DebugOpt = 0;
int Spacing = 0;
using namespace std;
int main(){ //Most code in CSweeper.h
    int a, play = 1;
    while(play == 1){
        stats tracker;
        if(Spacing == 1){cout<<"\n";}
        cout<<"| Input Anything to Begin |"<<endl;
        cin.ignore();
        if(Spacing == 1){cin.ignore();}
        tutorial(tracker,ReadTutorial,DebugOpt);
#if _WIN64 || _WIN32
        Sleep(4000);
#endif
        cout<<"\n";
        cout<<"| Would you like to play again? |\n| 1. [Yes] |\n| 2. [No] |\n";
        cin>>a;
        if(a==1){
            play = 1;
            Spacing = 1; //Adds spacing that does not appear after the first play through.
            ReadTutorial = 1; //Does not show the tutorial again after first reading.
            DebugOpt = 1; //Does not ask again if you would like to enable debug. Currently, Debug only works in
            // the first play through.
        }
        else{
            play = 0;
        }
    }
    cout<<"| Goodbye! |";
    Sleep(2000);
    return 0;
}
