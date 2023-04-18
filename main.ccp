#include <iostream>
#include <cstring>
#include <stack>
#include <random>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class stats{
public:
    int Scan = 0; //Used loosely to track the amount of repeats.
    int Turns = 0;
    int Opens = 0;
    int Marks = 0;
};

void view(string shown[][31],int limit1,int limit2,int diff){
    int a,b;
    for (a = 0; a < limit1+2; a++) {
        for (b = 0; b < limit2+2; b++) {
            if(diff==1||diff==2){
                if (a == 0 && b == 0) {
                    cout << "\nCurrent Grid:\n";
                }
                if (b == 0 && a < 10) {
                    cout << "| " <<shown[a][b]<< "";
                }
                else if( b == 0 && a>=10){
                    cout << "| " <<shown[a][b];
                }
                else {
                    if (shown[a][b] == "?"){
                        cout << "| _";
                    }
                    else{
                        cout << "| " << shown[a][b];
                    }

                }
                if (a != 0 && b >= 10) {
                    cout << " "; //Makes the ? align with the coord numbers
                }
                cout << " ";

                if (b == limit2+1) {
                    cout << "|\n";
                }
            }
            if(diff==3){ //POSSIBLE FIX FOR JANK
                if (a == 0 && b == 0) {
                    cout << "Current Grid:\n";
                }
                if (b == 0 && a < 10) {
                    cout << "|" <<shown[a][b]<< " ";
                }
                else if( b == 0 && a>=10){
                    cout << "|" <<shown[a][b];
                }
                else {
                    if (shown[a][b] == "?"){
                        if(b>9){
                            cout << "|__";
                        }
                        else{
                            cout << "|_";
                        }
                    }
                    else{
                        if(a!=0&&b>9){
                            cout << "| " << shown[a][b];
                        }
                        else{
                            cout << "|" << shown[a][b];
                        }
                    }

                }
                cout << "";

                if (b == limit2+1) {
                    cout << "|\n";
                }
            }
        }
    }
}
void lose(stats tracker) {
    string a;
    cout << "MINE TRIPPED! YOU LOSE!\nYour Stats:\nTotal Turns: "<<tracker.Turns<<"\nOpened Tiles: "<<tracker.Opens<<"\nMarked Tiles: "<<tracker.Marks;
    cout<<"\n\nIf you want to play again please rerun the code.\n\nPress Anything To Terminate Code.";
    cin.ignore();
    exit(0);
}
void win(stats tracker){
    string a;
    cout<<"MINES CLEARED! YOU WIN!\nIf you want to play again please rerun the code.\n\nPress Anything To Terminate Code.";
    cin.ignore();
    exit(0);

}

void resume(int grid[][30],int hidden[][30],string shown[][31],int x, int y,string state,int limit1,int limit2,int diff,stats tracker){ //CHECK IF THIS FUNCTION IS REALLY NECESSARY!
    int z,a,b,v,w=0,r=0,m=1,n;
    tracker.Turns++;
    if(state=="[OPEN]"){
        tracker.Opens++;
    }
    else if(state=="[MARK]"){
        tracker.Marks++;
    }
    if(grid[y][x]==99&&hidden[y][x]==1){ //LOSE CHECK
        lose(tracker);
    }
    for (a = 0; a < limit1 + 1; a++) {
        for (b = 0; b < limit2 + 1; b++) {
            if(grid[a][b]!=99&&hidden[a][b]==1){
                w++;
            }
        }
    }
    if(diff==1){
        if(w==54){
            win(tracker); //REQUIRES ALL TILES TO BE OPENED, EXCLUDING MINES. (8x8 = 64; 64 - 10 = 54)
        }
    }
    else if(diff==2){
        if(w==216){
            win(tracker); //REQUIRES ALL TILES TO BE OPENED, EXCLUDING MINES. (16x16 = 256; 256 - 40 = 216)
        }
    }
    else if(diff==3){
        if(w==381){
            win(tracker); //REQUIRES ALL TILES TO BE OPENED, EXCLUDING MINES. (30x16 = 480; 480 - 99 = 381)
        }
    }
    for(n=1;n>0;){
        if(r==1){
            for(z=1;z>0;){
                cout<<"Please select a selection mode.\n(1) OPEN\n(2) MARK";
                cin>>v;
                switch(v){
                    case(1):state="[OPEN]";r=0;m=1;break;
                    case(2):state="[MARK]";r=0;m=1;break;
                    default:state="[NULL]";break;
                }
                if(state=="[NULL]"){
                    cout<<"Invalid Selection, Try Again.";
                }
                else{
                    z=0;
                }
            }
        }
        cout<<"You are currently in "<<state<<" Mode.";
        view(shown,limit1,limit2,diff);
        cout<<"\n\nWhat tile would you like to "<<state<<"?";
        for(z=1;z>0;){
            cout<<"\nX: ";cin>>x;
            if(x<0){
                r=1;m=0;z=0;
            }
            else if(diff==1&&x>8){
                cout<<"Integer Out of Range [0 - 8]... Try Again.";
            }
            else if(diff==2&&x>16){
                cout<<"Integer Out of Range [0 - 16]... Try Again.";
            }
            else if(diff==3&&x>30){
                cout<<"Integer Out of Range [0 - 30]... Try Again.";
            }
            else{
                x--; //To match the tile on array
                z=0;
            }
        }
        if(m==1){
            for(z=1;z>0;){
                cout<<"\nY: ";cin>>y;
                if(diff==1&&y>8){
                    cout<<"Integer Out of Range [0 - 8]... Try Again.";
                }
                else if((diff==2||diff==3)&&y>16){
                    cout<<"Integer Out of Range [0 - 16]... Try Again.";
                }
                else{
                    y--; //To match the tile on array
                    z=0;
                    if(hidden[y][x]==2){
                        cout<<"You cannot open a marked tile.";
                    }
                    else{
                        n=0;
                    }
                }
            }
        }
    } //If a negative number is place into x it will send you back to the selection.
    if(state=="[OPEN]"){
        hidden[y][x]=1;
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
    //UPDATES SHOWN
    for (a = 0; a < limit1+1; a++) { //THIS CODE FINDS 1s in the hidden[][] and opens spaces in shown[][]
        for (b = 0; b < limit2+1; b++) {
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
            else if(hidden[a][b]==2){
                shown[a+1][b+1]="!";
            }
        }
    }
    resume(grid,hidden,shown,x,y,state,limit1,limit2,diff,tracker); // This is the looping version

}
void playing(int grid[][30],int hidden[][30],string shown[][31],int limit1,int limit2,int diff,stats tracker){ //This is the ini for the game
    int x,y,v,z,a,b,n=0,w=0,r=1,m=1,i=1;
    string state;


    for(n=1;n>0;){
        if(r==1){
            for(z=1;z>0;){
                cout<<"Please select a selection mode.\n(1) OPEN\n(2) MARK";
                cin>>v;
                switch(v){
                    case(1):state="[OPEN]";r=0;m=1;break;
                    case(2):state="[MARK]";r=0;m=1;break;
                    default:state="[NULL]";break;
                }
                if(state=="[NULL]"){
                    cout<<"Invalid Selection, Try Again.";
                }
                else{
                    z=0;
                }
            }
        }
        cout<<"You are currently in "<<state<<" Mode.";
        if(i==1){ //Stops necessary messages from reappearing when changing modes.
            cout<<"You can change selection mode at anytime by typing a negative number for x.\nGood Luck.";
            i=0;
        }
        view(shown,limit1,limit2,diff);
        cout<<"\n\nWhat tile would you like to "<<state<<"?";
        for(z=1;z>0;){
            cout<<"\nX: ";cin>>x;
            if(x<0){
                r=1;m=0;z=0;
            }
            else if(diff==1&&x>8){
                cout<<"Integer Out of Range [0 - 8]... Try Again.";
            }
            else if(diff==2&&x>16){
                cout<<"Integer Out of Range [0 - 16]... Try Again.";
            }
            else if(diff==3&&x>30){
                cout<<"Integer Out of Range [0 - 30]... Try Again.";
            }
            else{
                x--; //To match the tile on array
                z=0;
            }
        }
        if(m==1){
            for(z=1;z>0;){
                cout<<"\nY: ";cin>>y;
                if(diff==1&&y>8){
                    cout<<"Integer Out of Range [0 - 8]... Try Again.";
                }
                else if((diff==2||diff==3)&&y>16){
                    cout<<"Integer Out of Range [0 - 16]... Try Again.";
                }
                else{
                    y--; //To match the tile on array
                    z=0;n=0;
                }
            }
        }
    } //If a negative number is place into x it will send you back to the selection.
    if(state=="[OPEN]"){
        hidden[y][x]=1;
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
    //UPDATES SHOWN
    for (a = 0; a < limit1+1; a++) { //THIS CODE FINDS 1s in the hidden[][] and opens spaces in shown[][]
        for (b = 0; b < limit2+1; b++) {
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

    resume(grid,hidden,shown,x,y,state,limit1,limit2,diff,tracker); // This is the looping version
}


int scan2(int grid[][30],int hidden[][30],int posx,int posy,int limit2,int limit1,stats tracker,int debug){
    tracker.Scan++;
    if(debug==1){
        cout<<"\r"<<tracker.Scan;
    }
//gets a current position, will check for all squares surrounding the given position. If any zeroes are found it will
//go through the same loop again at the new position
    for(int y = (posy - 1);y <= (posy+1);y++){//three rows, above and below
        for(int x = (posx - 1);x <= (posx+1);x++){//same as the above but for the collumns
            if(x >= 0 && x < limit2+1&& y >= 0 && y<=limit1){//if the area you are scanning exists, it will continue
                if(x != posx || y != posy){//it will only continue if the space you are checking isnt the middle space
                    if(grid[y][x] == 0 && hidden[y][x] == 0){//if the position its at has no surrounding bombs, and the
//position hasn't already been scanned, then it will scan it
                        hidden[y][x] = 1;
                        scan2(grid,hidden,x,y,limit2,limit1,tracker,debug);
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

int scan(int grid[16][30],int hidden[16][30],int posx,int posy,int limit2,int limit1,stats tracker,int debug){
    tracker.Scan++;
//gets a current position, will check for all squares surrounding the given position. If any zeroes are found it will
//go through the same loop again at the new position
    for(int y = (posy - 2);y <= (posy);y++){//three rows, above and below
        for(int x = (posx - 2);x <= (posx);x++){//same as the above but for the collumns
            if(x >= 0 && x < limit2+1&& y >= 0 && y<=limit1){//if the area you are scanning exists, it will continue
                if(x != posx || y != posy){//it will only continue if the space you are checking isnt the middle space
                    if(grid[y][x] == 0 && hidden[y][x] == 0){//if the position its at has no surrounding bombs, and the
//position hasn't already been scanned, then it will scan it
                        hidden[y][x] = 1;
                        scan2(grid,hidden,x,y,limit2,limit1,tracker,debug);
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




int Begin(int diff,int numb,stats tracker,int debug) {
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
//REASONING FOR INI ^ Since we want to use character to allow for other markings like ■ to show a hidden spot.
// STRING TYPE DESIGNATION IS USED HERE DUE TO THE SIZE OF SPECIAL CHARACTERS USED. ASCII EXTENDED DOES NOT WORK...
    int grid[16][30] = {};; //ARRAY THAT DESIGNATES EMPTY SPACE, MINES, AND PROXIMITY. GRID WILL CHANGE DEPENDING ON DIFF.
//EASY 8x8, 10 MINES / HARD 16x16, 40 MINES / EXPERT 30x16, 99 MINES. YOU DO NOT HAVE TO
//CHANGE THE SIZE OF THE GRID JUST THE FUNCTION THAT PRINTS IT. ALL NON INCLUDED ARRAY VALUES
//WILL BE ZERO AND UNDISPLAYED. IT WILL ALWAYS BE THE SIZE OF THE LARGEST BOARD
    /*for (a = 0; a < 17; a++) { //CHANGED: CODE MADE TO FIT 16x30 Grid
        for (b = 0; b < 31; b++) {
            if (a == 0 && b == 0) {
                cout << "Current Grid:\n";
            }
            if (b == 0 && a < 10) {
                cout << " " << shown[a][b] << " ";
            } else {
                cout << " " << shown[a][b];
            }
            if (a != 0 && b >= 10) {
                cout << " "; //Makes the ? align with the coord numbers
            }
            cout << " ";
            if (b == 30) {
                cout << "\n";
            }
        }
    }*/
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
    cout << "Pick a starting point: (FORMAT: '[x,y]')\n";
    int x, y;
    for (;;) {
        cout << "x: ";
        cin >> x;
        cout << "\ny: ";
        cin >> y;
        grid[y - 1][x - 1] = -1;
        if (x > 8 && diff == 1) { //All these ifs check if the start is within range of given diff.
            cout << "\nx is out of range... Use x values 0 to 8";
        }
        if (y > 8 && diff == 1) {
            cout << "\ny is out of range... Use y values 0 to 8";
        }
        if (x > 16 && (diff == 1 || diff == 1)) { //Both Hard and Expert use 16 columns.
            cout << "\nx is out of range... Use x values 0 to 16";
        }
        if (y > 30 && diff == 1) {
            cout << "\ny is out of range... Use y values 0 to 30";
        }
        if (y > 30 && diff == 1) {
            cout << "\ny is out of range... Use y values 0 to 30";
        }
        break; //tests if the values are integers.
    }
    if(debug==1){
        for (a = 0; a < limit1 + 1; a++) { //[DEBUG ONLY] COMMENT OUT THIS FUNCTION FOR ACTUAL USE!
            for (b = 0; b < limit2 + 1; b++) {
                if (a == 0 && b == 0) {
                    cout << "Current Grid:\n";
                }
                cout << grid[a][b]; //It's tabbed to allow for uniformity.
                if (grid[a][b] < 99) {
                    cout << " ";
                }
                cout << " ";
                if (b == limit2) {
                    cout << "\n";
                }
            }
        } // [END OF DEBUG ONLY] IN FUNCTION DEBUG WILL BE UTILIZED FOR IN GAME USE... using DBUG
    }
//THIS FOLLOWING CODE GENERATES THE MINE'S POSITIONS.
//RANDOM NUMBER GENERATOR
    random_device rd; //THIS SETS THE VARIABLE rd TO A "UNIFORMLY-DISTRIBUTED INTEGER RANDOM NUMBER GENERATOR (RNG)".
    mt19937 mt(rd()); //THIS IS THE SEED GENERATOR FOR THE RNG, OR KNOWN AS THE "MERSENNE TWISTER ALGORITHM".
    uniform_real_distribution<double> distROW(0, limit2 + 1); //THIS RESTRICTS THE NUMBER RANGE BETWEEN THESE VALUES.
    uniform_real_distribution<double> distCOLUMN(0, limit1 + 1);
    for (m = m; m > 0; m--) { //CHANGE value of m to change the number of mines!
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
//[DEBUG ONLY] COMMENT OUT THIS FUNCTION FOR ACTUAL USE! -----------------------------------------------------------
    if(debug==1){
        for (a = 0; a < limit1 + 1; a++) {
            for (b = 0; b < limit2 + 1; b++) {
                if (a == 0 && b == 0) {
                    cout << "Grid Values:\n";
                }
                cout << grid[a][b]; //It's tabbed to allow for uniformity.
                if (grid[a][b] < 99) {
                    cout << " ";
                }
                cout << " ";
                if (b == limit2) {
                    cout << "\n";
                }
            }
        } //DEBUG EXTENDED
        int test = 0;
        for (a = 0; a < limit1 + 1; a++) { //[DEBUG ONLY] COMMENT OUT THIS FUNCTION FOR ACTUAL USE!
            for (b = 0; b < limit2 + 1; b++) {
                if (grid[a][b] == 99) {
                    test++;
                }
            }
        }
        cout << "Number of Mines: " << test << "\n\n"; //
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
        cout<<"Total Scans:\n";
    }
    scan(grid,hidden,x,y,limit2,limit1,tracker,debug);
    cout<<"\n";

/* OLD SCAN LOOP
for (int i = 1; i > -2; i--) {
for (int u = 1; u > -2; u--) {
if (i == 0 && u == 0) {
//IGNORES -1 (Start)
} else {
int i1, u1;
if (grid[(y - 1) - i][(x - 1) - u] == 0 &&
hidden[(y - 1) - i][(x - 1) - u] != 1) { //COMMENCES FIRST SCAN REFRESH (IF ZERO IS FOUND IN THE VALUES grid[][] AND 1
// IS FOUND IN THE hidden[][] ARRAY WHICH SIGNIFIES A VISIBLE TILE)
for (i1 = 1; i1 > -2; i1--) {
for (u1 = 1; u1 > -2; u1--) {
if (i1 == 0 && u1 == 0) {
//IGNORES -1 (Start)
} else {
int i2, u2;
if (grid[((y - 1) - i1) - i][((x - 1) - u1) - u] == 0 &&
hidden[((y - 1) - i1) - i][((x - 1) - u1) - u] != 1) { //COMMENCES FIRST SCAN REFRESH (IF ZERO IS FOUND
// IN THE VALUES grid[][] AND 1 IS FOUND IN THE hidden[][] ARRAY WHICH SIGNIFIES A VISIBLE TILE)
for (i2 = 1; i2 > -2; i2--) {
for (u2 = 1; u2 > -2; u2--) {
if (i == 0 && u == 0) { //SCANS PROXIMITY OF START POINT OF ZEROS.
//IGNORES -1 (Start)
} else {
if (hidden[(((y - 1) - i2) - i1) - i][(((x - 1) - u2) - u1) - u] == 0) {
hidden[(((y - 1) - i2) - i1) - i][(((x - 1) - u2) - u1) - u] = 1; //ANYTHING IN 8 TILE
// PROXIMITY WILL BE REVEALED.
}
}
}

}
}
if (hidden[((y - 1) - i1) - i][((x - 1) - u1) - u] == 0) {
hidden[((y - 1) - i1) - i][((x - 1) - u1) - u] = 1; //ANYTHING IN 8 TILE PROXIMITY WILL BE REVEALED.
}

}
}

}
}
if (hidden[(y - 1) - i][(x - 1) - u] == 0) {
hidden[(y - 1) - i][(x - 1) - u] = 1; //ANYTHING IN 8 TILE PROXIMITY WILL BE REVEALED.
}
}
}

}
*/
//Any 0 found will cause it to go into its first refresh, of which it will try to find a zero again.
// It's not perfect but it works. If it was perfect it may need to be adjusted so that smaller areas are made.
    if(debug==1){
        for (a = 0; a < limit1 + 1; a++) { //[DEBUG ONLY] COMMENT OUT THIS FUNCTION FOR ACTUAL USE! ------------------------
            for (b = 0; b < limit2 + 1; b++) {
                if (a == 0 && b == 0) {
                    cout << "Grid Visibility:\n"; //PRINTS THE GRID OF VISIBLE SPOTS, ANY 1s IN THE ARRAY ARE GOING TO BE VISIBLE IN THE GAME'S
//shown[][] ARRAY AND DISPLAYED GRID. THIS DEBUG IS TO CONFIRM THAT THE POINTS IN THE ARRAY (hidden[][]) MATCH THOSE IN THE
//GAME'S DISPLAYED ARRAY (shown[][])
                }
                cout << hidden[a][b]; //It's tabbed to allow for uniformity.
                cout << " ";
                if (b == limit2) {
                    cout << "\n";
                }
            }
        }
        int test = 0; //THIS FOR LOOP CHECK THE ENTIRE ARRAY FOR ALL SPOTS THAT ARE VISIBLE TO THE USER.
        for (a = 0; a < limit1 + 1; a++) {
            for (b = 0; b < limit2 + 1; b++) {
                if (hidden[a][b] == 1) {
                    test++;
                }
            }
        }
        cout << "Number of Starting Spots: " << test << "\n\n"; //[END OF DEBUG] ----------------------------------------------------
    }



    for (a = 0; a < limit1 + 1; a++) { //Hides -1s, Changes them to 0s.
        for (b = 0; b < limit2 + 1; b++) {
            if (grid[a][b] == -1) {
                grid[a][b] = 0;
            }
        }
    }
    for (a = 0; a < limit1+1; a++) { //THIS CODE FINDS 1s in the hidden[][] and opens spaces in shown[][]
        for (b = 0; b < limit2+1; b++) {
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
        }
    }
//FLEXIBLE SHOWN ARRAY GENERATOR -----------------------------------------------------------------------------------
    playing(grid,hidden,shown,limit1,limit2,diff,tracker);
//---------------------------------------------END OF CODE----------------------------------------------------------
}

void Menu(stats tracker){
    Menu:
    int diff,m,debug=0,h;
    cout<<endl<<"_______________________________________________________________________________________________________"<<endl
        <<"First, start by selecting the difficulty"<<endl<<"(1) Easy"<<endl<<"(2) Medium"<<endl<<"(3) Hard"<<endl
        <<"Please type in the corresponding number for the difficulty you would like to play in."<<endl<<
        "We suggest that you start with easy if you are a beginner."<<endl;
    cin>>diff;

    switch (diff) {
        case 1:m = 10;
        case 2:m = 40;
        case 3:m = 99;
    }
    if(debug==0){
        cout<<"Would you like to active debug mode? (Use only to observe the inner workings of the game. Cheating is not fun.)"
              "\n(1) Yes\n(2) No";
        for(h=1;h>0;){
            cin>>debug;
            switch(debug){
                case(1):h=0;break;
                case(2):h=0;break;
                default:cout<<"That was an invalid input. Please try again.";break;
            }
        }
    }
    if (diff<=3&&diff>=1){
        Begin(diff,m,tracker,debug);
    }else{
        cout<<"That was an invalid input. Please try again.";
        Menu(tracker);
    }
}

void tutorial(stats tracker) {
    char p;
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
    Menu(tracker);
}

int main(){
    stats tracker;
    char enter;
    cout<<"| Input Anything to Begin |"<<endl;
    cin.ignore();
    tutorial(tracker);
}
