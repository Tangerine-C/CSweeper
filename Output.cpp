//
// Created by matth on 12/4/2023.
//
#include <iostream>
#include "Output.h"
#if _WIN32 || _WIN64 //WINDOWS SPECIFIC OUTPUTS
#include<windows.h>
HANDLE getHandle(){
    return GetStdHandle(STD_OUTPUT_HANDLE);
}
void update(int grid[][30],int hidden[][30], std::string shown[][31] ,int limit1, int limit2){
    for (int a = 0; a < limit1+1; a++) { //THIS CODE FINDS 1s in the hidden[][] and opens spaces in shown[][]
        for (int b = 0; b < limit2+1; b++) {
            if (hidden[a][b] == 1) {
                if(grid[a][b]==0){
                    shown[a+1][b+1]="0"; //shown[][] IS A CHAR DATA TYPE, IT NEEDS TO BE SPECIFIED AS A LITERAL NUMBER.
                }
                else if(grid[a][b]==1){
                    shown[a+1][b+1]="1";
                }
                else if(grid[a][b]==2){
                    shown[a+1][b+1]="2";
                }
                else if(grid[a][b]==3){ //The rest will most likely be very unlikely...
                    shown[a+1][b+1]="3";
                }
                else if(grid[a][b]==4){
                    shown[a+1][b+1]="4";
                }
                else if(grid[a][b]==5){
                    shown[a+1][b+1]="5";
                }
                else if(grid[a][b]==6){
                    shown[a+1][b+1]="6";
                }
                else if(grid[a][b]==7){
                    shown[a+1][b+1]="7";
                }
                else if(grid[a][b]==8){
                    shown[a+1][b+1]="8";
                }
                else if(grid[a][b]==99){ //Shouldn't be possible but doesn't hurt to be prepared.
                    shown[a+1][b+1]="M";
                }
            }
            else if(hidden[a][b]==2) {
                shown[a + 1][b + 1] = "!";
            }
        }
    }
}

void ResetColoring(){ //This just resets any console colors back to the original grey
    SetConsoleTextAttribute(getHandle(),7);
}


void colorCode(const std::string shown[][31],int a,int b){ //Sets specific values for each number ||NEED COMPATABILITY
    if(a!=0 && b!=0){ //Should stop the locators from being colored
        if(shown[a][b]=="0"){// 255
            SetConsoleTextAttribute(getHandle(),2);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="1"){
            SetConsoleTextAttribute(getHandle(),14);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="2"){
            SetConsoleTextAttribute(getHandle(),6);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="3"){
            SetConsoleTextAttribute(getHandle(),12);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="4"){
            SetConsoleTextAttribute(getHandle(),4);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="5"){
            SetConsoleTextAttribute(getHandle(),4);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="6"){
            SetConsoleTextAttribute(getHandle(),4);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="7"){
            SetConsoleTextAttribute(getHandle(),4);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="8"){
            SetConsoleTextAttribute(getHandle(),4);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="M"){
            SetConsoleTextAttribute(getHandle(),4);
            std::cout<<shown[a][b];
        }
        else if(shown[a][b]=="!"){
            SetConsoleTextAttribute(getHandle(),15);
            std::cout<<shown[a][b];
        }
    }
    else{
        SetConsoleTextAttribute(getHandle(),15);
        std::cout<<shown[a][b];
    }
    ResetColoring();
}



void view(std::string shown[][31],int limit1,int limit2,int diff){
    int a,b;
    for (a = 0; a < limit1+2; a++) {
        for (b = 0; b < limit2+2; b++) {
            if(diff==1){
                if (a == 0 && b == 0) {
                    std::cout << "\nCurrent Grid:\n";
                }
                if (b == 0 && a < 10) {
                    std::cout << "| ";
                    colorCode(shown,a,b);
                    std::cout<< "";
                }
                else if( b == 0 && a>=10){
                    std::cout << "| ";
                    colorCode(shown,a,b);
                }
                else {
                    if (shown[a][b] == "?"){
                        std::cout << "| _";
                    }
                    else{
                        std::cout << "| ";
                        colorCode(shown,a,b);
                    }

                }
                if(a <= 9 && b == 0){
                    std::cout<< " ";
                }
                if (a != 0 && b >= 10) {
                    std::cout << " "; //Makes the ? align with the coord numbers
                }
                std::cout << " ";

                if (b == limit2+1) {
                    std::cout << "|\n";
                }
            }
            if(diff==3||diff==2){ //POSSIBLE FIX FOR JANK
                if (a == 0 && b == 0) {
                    std::cout << "Current Grid:\n";
                }
                if (b == 0 && a < 10) {
                    std::cout << "|";
                    colorCode(shown,a,b);
                    std::cout<< " ";
                }
                else if( b == 0 && a>=10){
                    std::cout << "|";
                    colorCode(shown,a,b);
                }
                else {
                    if (shown[a][b] == "?"){
                        if(b>9){
                            std::cout << "|__";
                        }
                        else{
                            std::cout << "|_";
                        }
                    }
                    else{
                        if(a!=0&&b>9){
                            std::cout << "| ";
                            colorCode(shown,a,b);
                        }
                        else{
                            std::cout << "|";
                            colorCode(shown,a,b);
                        }
                    }

                }
                std::cout << "";

                if (b == limit2+1) {
                    std::cout << "|\n";
                }
            }
        }
    }
}

void scoreboard(stats tracker){
    std::cout<<"Your Stats:\n";
    std::cout<<"Total Turns: "<<tracker.Turns;
    std::cout<<"\nOpened Tiles: "<<tracker.Opens;
    std::cout<<"\nMarked Tiles: "<<tracker.Marks; SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n\n\t    |Score|"; SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Opened Tiles: "; SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t+ "<<tracker.ScoreOpen; SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Marked Mines: "; SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t+ "<<tracker.ScoreMark; SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   False Marks: "; SetConsoleTextAttribute(getHandle(),4);
    std::cout<<"\t- "<<abs(tracker.FalseMark); SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Risky Tiles: ";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t+ "<<tracker.RiskyOpen;SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Lucky Number: ";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t+ "<<tracker.LuckyNumber;SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   No [MARK]: ";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t\t+ "<<tracker.NoMark;SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   NMLB: ";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t\t+ "<<tracker.NoMineLeftBehind;SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Win: ";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t\t+ "<<tracker.Completion;SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Total Score:";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t\t  "<<tracker.Score;SetConsoleTextAttribute(getHandle(),15);
    std::cout<<"\n   Average Multiplier:";SetConsoleTextAttribute(getHandle(),2);
    std::cout<<"\t x"<<tracker.AvgMulti; SetConsoleTextAttribute(getHandle(),7);//will be xnan if less than 1 turn is made

}
#else //COMPATABILITY OUTPUTS
void update(int grid[][30],int hidden[][30], std::string shown[][31] ,int limit1, int limit2){
    for (int a = 0; a < limit1+1; a++) { //THIS CODE FINDS 1s in the hidden[][] and opens spaces in shown[][]
        for (int b = 0; b < limit2+1; b++) {
            if (hidden[a][b] == 1) {
                if(grid[a][b]==0){
                    shown[a+1][b+1]="0"; //shown[][] IS A CHAR DATA TYPE, IT NEEDS TO BE SPECIFIED AS A LITERAL NUMBER.
                }
                else if(grid[a][b]==1){
                    shown[a+1][b+1]="1";
                }
                else if(grid[a][b]==2){
                    shown[a+1][b+1]="2";
                }
                else if(grid[a][b]==3){ //The rest will most likely be very unlikely...
                    shown[a+1][b+1]="3";
                }
                else if(grid[a][b]==4){
                    shown[a+1][b+1]="4";
                }
                else if(grid[a][b]==5){
                    shown[a+1][b+1]="5";
                }
                else if(grid[a][b]==6){
                    shown[a+1][b+1]="6";
                }
                else if(grid[a][b]==7){
                    shown[a+1][b+1]="7";
                }
                else if(grid[a][b]==8){
                    shown[a+1][b+1]="8";
                }
                else if(grid[a][b]==99){ //Shouldn't be possible but doesn't hurt to be prepared.
                    shown[a+1][b+1]="M";
                }
            }
            else if(hidden[a][b]==2) {
                shown[a + 1][b + 1] = "!";
            }
        }
    }
}

void view(std::string shown[][31],int limit1,int limit2,int diff){
    int a,b;
    for (a = 0; a < limit1+2; a++) {
        for (b = 0; b < limit2+2; b++) {
            if(diff==1){
                if (a == 0 && b == 0) {
                    std::cout << "\nCurrent Grid:\n";
                }
                if (b == 0 && a < 10) {
                    std::cout << "| ";
                    std::cout<<shown[a][b];
                    std::cout<< "";
                }
                else if( b == 0 && a>=10){
                    std::cout << "| ";
                    std::cout<<shown[a][b];
                }
                else {
                    if (shown[a][b] == "?"){
                        std::cout << "| _";
                    }
                    else{
                        std::cout << "| ";
                        std::cout<<shown[a][b];
                    }

                }
                if(a <= 9 && b == 0){
                    std::cout<< " ";
                }
                if (a != 0 && b >= 10) {
                    std::cout << " "; //Makes the ? align with the coord numbers
                }
                std::cout << " ";

                if (b == limit2+1) {
                    std::cout << "|\n";
                }
            }
            if(diff==3||diff==2){ //POSSIBLE FIX FOR JANK
                if (a == 0 && b == 0) {
                    std::cout << "Current Grid:\n";
                }
                if (b == 0 && a < 10) {
                    std::cout << "|";
                    std::cout<<shown[a][b];
                    std::cout<< " ";
                }
                else if( b == 0 && a>=10){
                    std::cout << "|";
                    std::cout<<shown[a][b];
                }
                else {
                    if (shown[a][b] == "?"){
                        if(b>9){
                            std::cout << "|__";
                        }
                        else{
                            std::cout << "|_";
                        }
                    }
                    else{
                        if(a!=0&&b>9){
                            std::cout << "| ";
                            std::cout<<shown[a][b];
                        }
                        else{
                            std::cout << "|";
                            std::cout<<shown[a][b];
                        }
                    }

                }
                std::cout << "";

                if (b == limit2+1) {
                    std::cout << "|\n";
                }
            }
        }
    }
}

void scoreboard(stats tracker){ //Non colored variant of the scoreboard.
    std::cout<<"Your Stats:\n";
    std::cout<<"Total Turns: "<<tracker.Turns;
    std::cout<<"\nOpened Tiles: "<<tracker.Opens;
    std::cout<<"\nMarked Tiles: "<<tracker.Marks;
    std::cout<<"\n\n\t    |Score|";
    std::cout<<"\n   Opened Tiles: ";
    std::cout<<"\t+ "<<tracker.ScoreOpen;
    std::cout<<"\n   Marked Mines: ";
    std::cout<<"\t+ "<<tracker.ScoreMark;
    std::cout<<"\n   False Marks: ";
    std::cout<<"\t- "<<abs(tracker.FalseMark);
    std::cout<<"\n   Risky Tiles: ";
    std::cout<<"\t+ "<<tracker.RiskyOpen;
    std::cout<<"\n   Lucky Number: ";
    std::cout<<"\t+ "<<tracker.LuckyNumber;
    std::cout<<"\n   No [MARK]: ";
    std::cout<<"\t\t+ "<<tracker.NoMark;
    std::cout<<"\n   NMLB: ";
    std::cout<<"\t\t+ "<<tracker.NoMineLeftBehind;
    std::cout<<"\n   Win: ";
    std::cout<<"\t\t+ "<<tracker.Completion;
    std::cout<<"\n   Total Score:";
    std::cout<<"\t\t  "<<tracker.Score;
    std::cout<<"\n   Average Multiplier:";
    std::cout<<"\t x"<<tracker.AvgMulti;//will be xnan if less than 1 turn is made

}
#endif