//
// Created by matth on 11/22/2023.
//

#ifndef CSWEEPER_V_1_1_4_CSWEEPER_H
#define CSWEEPER_V_1_1_4_CSWEEPER_H
#include <string>
class stats{ //
public:
    int Scan = 0; //Used loosely to track the amount of repeats. Barely Works :(
    float Turns = 0;
    int Opens = 0;
    int Marks = 0;
    int Score = 0;
    int ScoreOpen = 0;
    int ScoreMark = 0;
    int FalseMark = 0;
    int NoMark = 1; //Special Win Condition: Winning a game without using [MARK].
    int NoMineLeftBehind = 0; //Special Win Condition: Winning a game with ALL mines marked by [MARK].
    int RiskyOpen = 0; //Special Open Condition: Opening a tile that has no hints to where mines are.
    int LuckyNumber = 0; //Special Open Condition: Open a tile containing an 8. (Extremely Unlikely)
    float MultiTotal = 0;
    float AvgMulti = 0;
    int Completion = 0;
    int NoRetry = 0; //Used to end the game
};
void tutorial(stats,int,int); // LINE 37 Sends through ReadTutorial and DebugOpt. Requires ReadTutorial
void Menu(stats,int); // LINE 57 Requires DebugOpt
void Begin(int,int,stats,int); // LINE 114
int scan(int[16][30],int[16][30],int,int,int,int,stats,int); // LINE 417
//void playing(int[][30],int[][30],std::string[][31],int,int,int,stats); // LINE 492
void resume(int[][30],int[][30],std::string[][31],int,int,std::string,int,int,int,stats,int,int); // LINE 604
void win(stats);
void lose(stats);
#endif //CSWEEPER_V_1_1_4_CSWEEPER_H