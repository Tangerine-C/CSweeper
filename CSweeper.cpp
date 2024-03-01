//
// Created by matth on 12/1/2023.
//
//Checking operating system to avoid compile errors. Which should work.
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cstdlib>

//USER HEADERS
#include "Input.h"
#include "Output.h"
#include "debug.h"
#include "File Manager.h"
#include "CSweeper.h"

using namespace std;
string line{"_______________________________________________________________________________________________________\n"};
//// SORTING [IN ORDER OF USE] -------------------------------------------------------------------------------------------------------------


//// FUNCTIONS -----------------------------------------------------------------------------------------------------------------------------
void tutorial(stats tracker,int ReadTutorial,int DebugOpt) {
    if(ReadTutorial == 0){
        cout << "Minesweeper is a strategy game about sweeping mines. The way to find out where mines are on the field\n"
                "are based on the number that appears on the ground revealed by giving a starting point inputting x & y.\n"
                "You will then see a Board of empty boxes (tiles) with ascending numbers on the x and y axis to assist\n"
                "in finding a tile. After the starting tile is chosen you will see possibly a lot of 0s, some 1s and 2s\n"
                "and rarely 3s, these expose how many mines are around the number of which is the 8 tiles that surround\n"
                "the tile that the number is in. A single number does not help much, but multiple numbers help a lot!\n"
                "Observing where the overlap in the numbers is the key to finding where the mine are hiding in the hidden\n"
                "tiles. When you start you will be asked to select a mode. Mode 1 [OPEN] allows you to uncover tiles.\n"
                "Mode 2 [MARK] allows you to mark tiles for danger, making the [OPEN] mode not work on those tiles.\n"
                "You can reselect the mode after the initial selection by typing a negative number in the x value.\n"
                "Do note that if you try to change the mode using y, it will not work. You will be asked to input tile\n"
                "Coordinates until all tiles that are empty are revealed or a mine is hit. Revealing all empty tiles\n"
                "results in a win. Revealing a mine, results in a loss. You will be shown stats at the end of the game.\n"
                "Enter anything when you are ready to continue";
        cin.ignore();
    }
    Menu(tracker,DebugOpt);
}
void Menu(stats tracker,int DebugOpt){
    int diff=0,m=0,debug=0,h;
    if(DebugOpt == 0){
        cout<<endl<<line;
        cout<<"Would you like to active debug mode? (Use only to observe the inner workings of the game. Cheating is not fun.)"
              "\n(1) Yes\n(2) No";
        for(h=1;h>0;){
            cin>>debug;
            while(cin.fail()){
                cin.clear();
                cin.ignore();
                cout<<"Invalid character (non-integer). Please enter an integer.\n";
                cin>>debug;
            }
            switch(debug){
                case(1):h=0;break;
                case(2):h=0;break;
                default:cout<<"That was an invalid input. Please try again.";break;
            }
        }
    }
    cout<<endl<<line<<endl
        <<"Select your difficulty"<<endl;
#if _WIN32 || _WIN64 //WINDOWS
    SetConsoleTextAttribute(getHandle(),32);
    cout<<"(1) Easy\t [ 8 x  8]"<<endl;
    SetConsoleTextAttribute(getHandle(),224);
    cout<<"(2) Medium\t [16 x 16]"<<endl;
    SetConsoleTextAttribute(getHandle(),64);
    cout<<"(3) Hard\t [30 x 16]"<<endl;
    SetConsoleTextAttribute(getHandle(),7);
#else //NON WINDOWS
    cout<<"(1) Easy\t [ 8 x  8]"<<endl;
    cout<<"(2) Medium\t [16 x 16]"<<endl;
    cout<<"(3) Hard\t [30 x 16]"<<endl;
#endif
    int lock = 1;
    cout<<"Please type in the corresponding number for the difficulty you would like to play in."<<endl<<
        "We suggest that you start with easy if you are a beginner."<<endl;
    do{
        diff = 0;
        cin>>diff;
        switch(diff) {
            case 1:m = 10;
            case 2:m = 40;
            case 3:m = 99;
            default: m = 0;
        }
        if (diff<=3&&diff>=1){
            lock = 0;
            Begin(diff,m,tracker,debug);
        }else{
            cout<<"Invalid character (non-integer). Please enter an integer.\n";
            cin.clear();
            cin.ignore(); //Empties buffer and allows and characters to be flushed
        }
    }
    while(isdigit(diff)==false&&lock != 0);
}
void Begin(int diff,int numb,stats tracker,int debug) {
    int a = 0, b = 0, c, d, m, limit1, limit2, play = 1;

    string shown[17][31] = { //Size +1 to include the numbers outside the shown array (for ease of play).
            {" ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"},
            {"1", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"2", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"3", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"4", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"5", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"6", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"7", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"8", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"9", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"10", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"11", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"12", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"13", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"14", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"15", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},
            {"16", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?"},};
    int grid[16][30] = {};; //ARRAY THAT DESIGNATES EMPTY SPACE, MINES, AND PROXIMITY. GRID WILL CHANGE DEPENDING ON DIFF.
//EASY 8x8, 10 MINES / HARD 16x16, 40 MINES / EXPERT 30x16, 99 MINES. YOU DO NOT HAVE TO
//CHANGE THE SIZE OF THE GRID JUST THE FUNCTION THAT PRINTS IT. ALL NON INCLUDED ARRAY VALUES
//WILL BE ZERO AND UNDISPLAYED. IT WILL ALWAYS BE THE SIZE OF THE LARGEST BOARD
    for (;;) {
        if (diff == 1) {
            m = 10;
            limit1 = 7;
            limit2 = 7;
            break;
        } else if (diff == 2) {
            m = 40;
            limit1 = 15;
            limit2 = 15;
            break;
        } else if (diff == 3) {
            m = 99;
            limit1 = 15;
            limit2 = 29;
            break;
        } else {
            cout << "That is not a available option. Check spelling or options, and try again.\n";
        }
    }
//START TESTING
    cout<<endl<<line;
    cout << "Pick a starting point:\n";
    int x, y;
    for (;;) {
        cout << "x: ";
        cin >> x;
        while(cin.fail()){
            clean(x);
        }
        cout << "\ny: ";
        cin >> y;
        while(cin.fail()){
            clean(y);
        }
        grid[y - 1][x - 1] = -1;
        if (x > 8 && diff == 1) { //All these ifs check if the start is within range of given diff.
            cout << "\nx is out of range... Use x values 0 to 8\n";
        }
        else if (y > 8 && diff == 1) {
            cout << "\ny is out of range... Use y values 0 to 8\n";
        }
        else if (x > 16 && diff == 2) { //Both Hard and Expert use 16 columns.
            cout << "\nx is out of range... Use x values 0 to 16\n";
        }
        else if (y > 16 && (diff == 2 || diff == 3)) {
            cout << "\ny is out of range... Use y values 0 to 16\n";
        }
        else if (x > 30 && diff == 3){
            cout << "\nx is out of range... Use x values 0 to 30\n";
        }
        else{
            break; //tests if the values are integers.
        }
    }
    if(debug==1){
        reveal_game(grid,limit1,limit2);
    }
//// -------------------------------------------------------------------------------------------------------------------
//// GOOD CODE, HARD TO READ BUT WORKS FINE. LENGTH IS FINE FOR A GENERATOR. [LEN ~170 LINES]
//// -------------------------------------------------------------------------------------------------------------------
//THIS FOLLOWING CODE GENERATES THE MINE'S POSITIONS.
//RANDOM NUMBER GENERATOR
    random_device rd; //THIS SETS THE VARIABLE rd TO A "UNIFORMLY-DISTRIBUTED INTEGER RANDOM NUMBER GENERATOR (RNG)".
    mt19937 mt(rd()); //THIS IS THE SEED GENERATOR FOR THE RNG, OR KNOWN AS THE "MERSENNE TWISTER ALGORITHM".
    uniform_real_distribution<double> distROW(0, limit2 + 1); //THIS RESTRICTS THE NUMBER RANGE BETWEEN THESE VALUES.
    uniform_real_distribution<double> distCOLUMN(0, limit1 + 1);
    for (; m > 0; m--) { //CHANGE value of m to change the number of mines!
        int r1 = distCOLUMN(mt), r2 = distROW(mt);
        if (grid[r1][r2] != 99) {
            if (grid[r1 - 1][r2 - 1] != -1 && grid[r1 - 1][r2 - 0] != -1 && grid[r1 - 1][r2 - -1] != -1 &&
                grid[r1 - 0][r2 - 1] != -1 &&
                grid[r1 - 0][r2 - 0] != -1 && grid[r1 - 0][r2 - -1] != -1 && grid[r1 - -1][r2 - 1] != -1 &&
                grid[r1 - -1][r2 - 0] != -1 &&
                grid[r1 - -1][r2 - -1] != -1) { //THIS GIANT MESS CHECKS FOR THE -1s AROUND THE TESTED MINE LOCATION, IF THERE IS NO -1s
//IT WILL THEN MAKE IT A MINE LOCATION OR THE VALUE 99.
                grid[r1][r2] = 99;
//GIVING PROXIMITY... OR A +1 VALUE. ALL 8 TILES SURROUNDING THE TILE CONTAINING THE MINE WILL BE GIVEN A +1 VALUE, UNLESS
//IT IS AN EDGE. (TO PREVENT POSSIBLE ERRORS)
                if ((r1 != 0 && r2 != 0) && (r1 != limit1 && r2 != limit2) && (r1 != 0 && r2 != limit2) &&
                    (r1 != limit1 && r2 != 0)) { //NO EDGES ARE AFFECTED THEREFORE NO SPECIAL GENERATION OF NEARBY TILES REQUIRED.
                    for (int i = 1; i > -2; i--) {
                        for (int u = 1; u > -2; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }

                    }
                } else if (r1 == 0 && r2 == 0) { //TOP LEFT CORNER, ONLY THE TILES TO THE RIGHT, BOTTOM RIGHT, AND BOTTOM ARE GENERATED WITH
// +1 VALUE.
                    for (int i = 0; i > -2; i--) {
                        for (int u = 0; u > -2; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }

                    }
                } else if (r1 == 0 && r2 == limit2) { //TOP RIGHT CORNER, ONLY THE TILES TO THE LEFT, BOTTOM LEFT, AND BOTTOM ARE GENERATED
//WITH +1 VALUE.
                    for (int i = 0; i > -2; i--) {
                        for (int u = 1; u > -1; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }
                    }
                } else if (r1 == limit1 && r2 == 0) { //BOTTOM LEFT CORNER, ONLY THE TILES TO THE RIGHT, TOP RIGHT, AND TOP ARE GENERATED
//WITH +1 VALUE.
                    for (int i = 1; i > -1; i--) {
                        for (int u = 0; u > -2; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }
                    }
                } else if (r1 == limit1 && r2 == limit2) { // BOTTOM RIGHT CORNER, ONLY THE TILES TO THE LEFT, TOP LEFT, AND TOP ARE
// GENERATED WITH +1 VALUE
                    for (int i = 1; i > -1; i--) {
                        for (int u = 1; u > -1; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }
                    }
                } else if (r1 == 0) { //TOP EDGE, THE TOP TILES WILL BE GENERATED. REST ARE GENERATED NORMALLY.
                    for (int i = 0; i > -2; i--) { //DOES NOT INCLUDE THE ROW ABOVE, SINCE IT DOESN'T EXIST
                        for (int u = 1; u > -2; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }

                    }
                } else if (r1 == limit1) { //BOTTOM EDGE, THE BOTTOM TILES WILL NOT BE GENERATED. REST ARE GENERATED NORMALLY.
                    for (int i = 1; i > -1; i--) { //DOES NOT INCLUDE THE ROW BELOW, SINCE IT DOESN'T EXIST
                        for (int u = 1; u > -2; u--) {
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }

                    }
                } else if (r2 == 0) { //LEFT EDGE, THE LEFT VALUES WILL NOT BE GENERATED. REST ARE GENERATED NORMALLY.
                    for (int i = 1; i > -2; i--) {
                        for (int u = 0; u > -2; u--) { //DOES NOT INCLUDE THE COLUMN LEFT, SINCE IT DOESN'T EXIST
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }

                    }
                } else if (r2 == limit2) { // RIGHT EDGE, THE RIGHT VALUES WILL NOT BE GENERATED. REST ARE GENERATED NORMALLY.
                    for (int i = 1; i > -2; i--) {
                        for (int u = 1; u > -1; u--) { //DOES NOT INCLUDE THE COLUMN RIGHT, SINCE IT DOESN'T EXIST
                            if (i == 0 && u == 0) {
//IGNORES 99
                            } else {
                                if (grid[r1 - i][r2 - u] == 99) {
//IGNORES 99
                                } else {
                                    grid[r1 - i][r2 - u] += 1;
                                }

                            }
                        }

                    }
                }
            } else {
                m++;
            }
        } else {
            m++;
        }
    }
    cout << "\nInitialization Complete!\n\n";
//END OF INI CODE --------------------------------------------------------------------------------------------------
//[DEBUG ONLY] -----------------------------------------------------------------------------------------------------
    if(debug==1){
        values(grid,limit1,limit2);
    }
// [END OF DEBUG ONLY] ---------------------------------------------------------------------------------------------
    int hidden[16][30] = {};//ARRAY THAT WILL TELL SHOWN WHAT SPACE IS REVEALED OR. I.E. IF THE VALUE OF A GRID SPACE IS 0, IT IS HIDDEN FROM THE
// USERS VIEW. IF THE VALUE OF THE GRID SPACE IS 1 IT IS VISIBLE TO THE USER.
    hidden[y - 1][x - 1] = 1;
    int o=0;
//REVEAL CODE ------------------------------------------------------------------------------------------------------
/* - SCANS FOR ZEROS AND ATTEMPTS TO GENERATE A VISIBILITY AREA FOR THE PLAYER. LIMIT OF REFRESHES CAN BE ADJUSTED, JUST ASK.
* - FROM CURRENT TESTS SEEMS TO WORK. MORE TESTING IS NEEDED TO CONFIRM.
*/
//new scanning function:
    if(debug==1){
        cout<<endl<<line;
        cout<<"Total Scans:\n";
    }
    scan(grid,hidden,x-1,y-1,limit2,limit1,tracker,debug);
    cout<<"\n";
    if(debug==1){
        reveal(hidden,limit1,limit2);
    }



    for (a = 0; a < limit1 + 1; a++) { //Hides -1s, Changes them to 0s.
        for (b = 0; b < limit2 + 1; b++) {
            if (grid[a][b] == -1) {
                grid[a][b] = 0;
            }
        }
    }
    update(grid,hidden,shown,limit1,limit2);
    // NEW SECTION CHECKS ===============================
    int i = 1;
    string state;
    redo: //label
    state = input_state();
    cout<<"You are currently in "<<state<<" Mode.";
    if(i==1){ //Stops necessary messages from reappearing when changing modes.
        cout<<"You can change selection mode at anytime by typing a negative number for x.\nGood Luck.";
        i=0;
    }
    view(shown,limit1,limit2,diff);
    cout<<"\n\nWhat tile would you like to "<<state<<"?";
    int x1 = input_x(diff);
    int y1 = input_y(diff);
    while(x1<0 || y1<0){
        goto redo;
    }
    int multi=0, score=0;
    if(state=="[OPEN]"){
        if(hidden[y1][x1] == 0){
            hidden[y1][x1]=1;
            if(grid[y1][x1] != 99){
                score=1;
            }
        }
    }
    else if(state=="[MARK]"){
        if(hidden[y1][x1]==2){
            hidden[y1][x1]=0;
        }
        else if(hidden[y1][x1]==1){
            cout<<"Cannot mark a revealed tile.";
        }
        else{
            hidden[y1][x1]=2;
        }
    }
    if(hidden[y][x]==1&&grid[y][x]==0){
        scan(grid,hidden,x,y,limit2,limit1,tracker,0);//Auto open 0 connections
    }
    cout<<endl<<line;
    //UPDATES SHOWN
    update(grid,hidden,shown,limit1,limit2);
    if (grid[y1][x1] == 99 && hidden[y1][x1] == 1) { //LOSE CHECK
        view(shown, limit1, limit2, diff);
        tracker.NoMark = 0;
        tracker.NoRetry = 1;
        lose(tracker);
    }
    if(tracker.NoRetry!=1){
        resume(grid, hidden, shown, x1, y1, state, limit1, limit2, diff, tracker, multi,score);
    }

//FLEXIBLE SHOWN ARRAY GENERATOR -----------------------------------------------------------------------------------
    //playing(grid,hidden,shown,limit1,limit2,diff,tracker);
}

int scan(int grid[][30],int hidden[][30],int posx,int posy,int limit2,int limit1,stats tracker,int debug){
    tracker.Scan++;
    if(debug==1){
        cout<<"\r"<<tracker.Scan;
    }
//gets a current position, will check for all squares surrounding the given position. If any zeroes are found it will
//go through the same loop again at the new position
    for(int y = (posy - 1);y <= (posy+1);y++){//three rows, above and below
        for(int x = (posx - 1);x <= (posx+1);x++){//same as the above but for the collumns
            if(x >= 0 && x <= limit2 && y >= 0 && y<=limit1){//if the area you are scanning exists, it will continue
                if(x != posx || y != posy){//it will only continue if the space you are checking isnt the middle space
                    if(grid[y][x] == 0 && hidden[y][x] == 0){//if the position its at has no surrounding bombs, and the
//position hasn't already been scanned, then it will scan it
                        hidden[y][x] = 1;
                        scan(grid,hidden,x,y,limit2,limit1,tracker,debug);
                    }else{
                        if(grid[y][x]==99){
                            //NULL
                        }
                        else{
                            hidden[y][x] = 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
////END OF RECONSTRUCTION ------------------------------------------------------------------------------------------------------------------
//// MAKE THIS SECTION ONE RECURSIVE LOOP. MAKE IT LESS THAN 300 LINES! [MARCO]
/* OBJ take the "playing" loop and incorporate it into the "resume" recursive loop, and make only one recusive loop using
 * "resume" there is not much difference between them.
 * |!|THIS IS THE MAIN GAMEPLAY LOOP! IF IT IS NOT WORKING IT WILL BE OBVIOUS AND VOLITLE SO BE CAREFUL AND HAVE BACKUP CODE.|!|
 * DO NOT DELETE ANYTHING IN "resume" UNLESS IT REALLY SEEMS IRRELEVANT, ONLY ADD. Everything in playing can be removed at will but
 * remember that not everything in "playing" is in "resume" find what needs to be included in resume for it to have functionality.
 * If you have anymore questions please email me on canvas
*/
//// -------------------------------------------------------------------------------------------------------------------

void resume(int grid[][30],int hidden[][30],string shown[][31],int x, int y,string state,int limit1,int limit2,int diff,stats tracker,int multi,int score){ //CHECK IF THIS FUNCTION IS REALLY NECESSARY!
    int z,a,b,v,w=0,r=0,m=1,n,risk = 0,nmlb=0,end=0;
    if(tracker.NoRetry==0) {
        tracker.Turns++;
        cout<<endl<<line;
        if (state == "[OPEN]") {
            tracker.Opens++;
            if(score==1){
                if (multi >= 0 && multi < 2) { //MULTIPLIER SYSTEMS
                    tracker.ScoreOpen += 10;
                    tracker.MultiTotal += 1.0;
                } else if (multi >= 2 && multi < 4) {
                    tracker.ScoreOpen += 10 * 2;
                    tracker.MultiTotal += 2.0;
                } else if (multi >= 4 && multi < 6) {
                    tracker.ScoreOpen += 10 * 4;
                    tracker.MultiTotal += 4.0;
                } else if (multi >= 6 && multi < 8) {
                    tracker.ScoreOpen += 10 * 8;
                    tracker.MultiTotal += 8.0;
                } else if (multi >= 8) {
                    tracker.ScoreOpen += 10 * 16;
                    tracker.MultiTotal += 16.0;
                }
                score=0;
            }
            for (int t1 = (x - 1); t1 <= (x + 1); t1++) { // Special Open Condition: Risky Open.
                for (int t2 = (y - 1); t2 <= (y + 1); t2++) {
                    if (t1 == x && t2 == y) {
                        //IGNORE
                    } else {
                        if (hidden[t2][t1] == 0) {
                            risk++;
                        }
                    }
                }
            }
            if (risk == 8) {
                if (multi >= 0 && multi < 2) { //MULTIPLIER SYSTEMS
                    tracker.RiskyOpen += 50;
                } else if (multi >= 2 && multi < 4) {
                    tracker.RiskyOpen += 50 * 2;
                } else if (multi >= 4 && multi < 6) {
                    tracker.RiskyOpen += 50 * 4;
                } else if (multi >= 6 && multi < 8) {
                    tracker.RiskyOpen += 50 * 8;
                } else if (multi >= 8) {
                    tracker.RiskyOpen += 50 * 16;
                }
            }
            multi++;
            if (grid[y][x] == 8) { //Extremely Unlikely Find. Special Open Condition: Lucky Number.
                tracker.LuckyNumber += 5000;
            }
        } else if (state == "[MARK]") {
            tracker.Marks++;
            if (grid[y][x] == 99 && hidden[y][x] == 2) {
                tracker.Score += 100;
                tracker.ScoreMark += 100;
            } else if (grid[y][x] != 99 && hidden[y][x] == 2) { //Very hard to do so it is costly.
                tracker.Score -= 500;
                tracker.FalseMark -= 500;
            }
        }
        if (grid[y][x] == 99 && hidden[y][x] == 1) { //LOSE CHECK
            view(shown, limit1, limit2, diff);
            tracker.NoMark = 0;
            tracker.NoRetry = 1;
            end=1;
            lose(tracker);
        }
        for (a = 0; a < limit1 + 1; a++) { //REVEALED TILE TRACKER + Special Win Condition: No Mine Left Behind
            for (b = 0; b < limit2 + 1; b++) {
                if (grid[a][b] != 99 && hidden[a][b] == 1) {
                    w++;
                }
                if (grid[a][b] == 99 && hidden[a][b] == 2) {
                    nmlb++;
                }
            }
        }
        if (diff == 1) { //VARIABLE DIFFICULTY WIN CHECK : EASY
            if (w == 54) {
                if (nmlb == 10) {
                    tracker.NoMineLeftBehind = 1000;
                }
                tracker.Completion = 1000;
                view(shown, limit1, limit2, diff);
                tracker.NoRetry = 1;
                end=1;
                win(tracker); //REQUIRES ALL TILES TO BE OPENED, EXCLUDING MINES. (8x8 = 64; 64 - 10 = 54)
            }
        } else if (diff == 2) { // MEDIUM (Normally Hard)
            if (w == 216) {
                if (nmlb == 40) {
                    tracker.NoMineLeftBehind = 3500;
                }
                if (tracker.NoMark == 1) {
                    tracker.NoMark = 3500;
                }
                tracker.Completion = 3500;
                view(shown, limit1, limit2, diff);
                tracker.NoRetry = 1;
                end=1;
                win(tracker); //REQUIRES ALL TILES TO BE OPENED, EXCLUDING MINES. (16x16 = 256; 256 - 40 = 216)
            }
        } else if (diff == 3) { // HARD (Normally Expert)
            if (w == 381) {
                if (nmlb == 99) {
                    tracker.NoMineLeftBehind = 7000;
                }
                if (tracker.NoMark == 1) {
                    tracker.NoMark = 7000;
                }
                tracker.Completion = 7000;
                view(shown, limit1, limit2, diff);
                tracker.NoRetry = 1;
                end=1;
                win(tracker); //REQUIRES ALL TILES TO BE OPENED, EXCLUDING MINES. (30x16 = 480; 480 - 99 = 381)
            }
        }
        if(tracker.NoRetry==0){
            int f=1;
            redo: //label
            if(f==0){
                state = input_state();
                f=1;
            }
            cout<<"You are currently in "<<state<<" Mode.";
            view(shown,limit1,limit2,diff);
            cout<<"\n\nWhat tile would you like to "<<state<<"?";
            x = input_x(diff);
            y = input_y(diff);
            while(x<0 || y<0){
                f=0;
                goto redo;
            }
            if(state=="[OPEN]"){
                if(hidden[y][x] == 0){
                    hidden[y][x]=1;
                    if(grid[y][x] != 99){
                        score=1;
                    }
                }
            }
            else if(state=="[MARK]"){
                if(hidden[y][x]==2){
                    hidden[y][x]=0;
                }
                else if(hidden[y][x]==1){
                    cout<<"Cannot mark a revealed tile.";
                }
                else{
                    hidden[y][x]=2;
                }
            }
            if(hidden[y][x]==1&&grid[y][x]==0){
                scan(grid,hidden,x,y,limit2,limit1,tracker,0);//Auto open 0 connections
            }
            cout<<endl<<line;
            //UPDATES SHOWN !!! PLEASE CHANGE THIS TO A FUNCTION!
            update(grid,hidden,shown,limit1,limit2);
            if(end!=1){
                resume(grid, hidden, shown, x, y, state, limit1, limit2, diff, tracker, multi, score);
            }
        }
    }


}
//// TAKE THIS ONE BELOW AND COMBINE IT INTO THE ONE ABOVE AND JUST NAME IT "playing" FOR COMPATABILITY.

//// -------------------------------------------------------------------------------------------------------------------
//// END OF RECONSTRUCTION
//// -------------------------------------------------------------------------------------------------------------------
void win(stats tracker){
    string a,name;
    bool w=true;
    tracker.AvgMulti = tracker.MultiTotal / tracker.Turns;
    cout<<endl<<"_______________________________________________________________________________________________________\n";
    tracker.Score = tracker.ScoreOpen + tracker.ScoreMark + tracker.FalseMark + tracker.RiskyOpen + tracker.LuckyNumber + tracker.NoMark + tracker.NoMineLeftBehind + tracker.Completion;
    cout<<"MINES CLEARED! YOU WIN!\n";
    scoreboard(tracker);
    cout<<"\n\nPlease insert a Name\n";
    cin>>name;
    leaderboard(name,tracker.Score,w);
    display();
}
void lose(stats tracker) {
    string a,name;
    bool w=false;
    tracker.AvgMulti = tracker.MultiTotal / tracker.Turns;
    cout<<endl<<"_______________________________________________________________________________________________________\n";
    tracker.Score = tracker.ScoreOpen + tracker.ScoreMark + tracker.FalseMark + tracker.RiskyOpen + tracker.LuckyNumber + tracker.NoMark + tracker.NoMineLeftBehind + tracker.Completion;
    cout<<"MINE TRIPPED! YOU LOSE!\n";
    scoreboard(tracker);
    cout<<"\n\nPlease insert a Name\n";
    cin>>name;
    leaderboard(name,tracker.Score,w);
    display();
}
