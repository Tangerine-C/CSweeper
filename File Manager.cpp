//
// Created by matth on 12/1/2023.
//
#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include "File Manager.h"
char file_name[ ] = "csr_leader.txt"; //Global file_name name
int attempt{0};
bool empty=false;
void leaderboard(std::string name,int score,bool w){
    //TEMPLATE Axxxx 0xxxxx xxx0 1 name[0-4] score[6-12] attempt[
    std::fstream file;
    file.open(file_name, std::fstream::in | std::fstream::out | std::fstream::app); //checking if it exists
    file.close();
    file.open(file_name,std::fstream::in); //will open to read file.
    std::array<std::string,1000>compare{}; //List of names
    std::string temp1,temp2;
    int x{0};
    do{ //this reads everything in the file
        getline(file,temp1);
        compare[x] = temp1;
        x++;
    }
    while(!file.eof()); //While itself will not work to read the entire file. It will read all but last line.
    attempt = x; //since an empty leaderboard will only contain 1 attempt
    int lC{0};
    file.close(); //Ending read.
    //END OF COMPARISON PHASE NOW APPENDING
    file.open(file_name, std::ios::app); //will open to APPEND file (adds to the end of file)
    int last{1}; //NEEDS TO BE ABLE TO GO UP
    std::string tempL;
    if(attempt<10){
        tempL = "   " + std::to_string(attempt);
    }
    else if(attempt<100){
        tempL = "  " + std::to_string(attempt);
    }
    else if (attempt<1000){
        tempL = " " + std::to_string(attempt);
    }
    while(name.length()>16){
        name.pop_back(); //if it somehow goes through it will remove letters until its under 16.
    }
    while(name.length()!=16){
        name += " "; //add spaces till it is length 26
    }
    std::string t = std::to_string(score);
    std::string emptyStr = "0";
    while(t.length()!=6){
        t.insert(0,emptyStr);// fills empty space with 0s
    }
    file << name << " " << t << " " << tempL << " " << w << '\n';
    file.close();
    file.open(file_name);
//    for(x=x+1;x>=0;x--){
//        std::cout<<compare[x]<<"\n";
//    }
    file.close(); //Ending
    // END OF ADDITION PHASE NOW COMPARING SCORES NOW SORTING SCORES
    file.seekg(0, std::ios::end);
    if (compare[0].empty()) {
        std::cout<<"There are no other scores in the leaderboard file.";
        empty=true;
    }
    else{
        int scores[1000]={}; //the array<int,1000> scores{} is not compatible with sort()
        std::string sort1,sort2,fin[1000]={};
        for(size_t u = 0;u!=attempt;u++){
            sort1 = compare[u];
            sort2={};
            for(size_t b = 17;b<=22;b++){
                sort2 += sort1[b];
            }
            scores[u] = std::stoi(sort2); //WILL KILL THE CODE
        }
        //int n = sizeof(scores) / sizeof(scores[0]);
        std::sort(scores,scores+(attempt-1),std::greater<>());
        for(int r=0;r<2;r++){
            for(size_t u = 0;u!=attempt-1;u++){
                sort1 = compare[u];
                sort2={};
                for(size_t b = 17;b<=22;b++){
                    sort2 += sort1[b];
                }
                for(size_t l=0;l!=attempt-1;l++){ //COMPARES ALL LINE AND DISTRIBUTES
                    sort1=std::to_string(scores[l]);
                    while(sort1.length()!=6){
                        sort1.insert(0,emptyStr);
                    }
                    if(sort2==sort1){
                        fin[l]=compare[u];
                    }
                }
            }
        }
        //std::cout<<"NOW TESTING\n";
        for(size_t a = 0;a<attempt-1;a++){
            //std::cout<<a+1<<" "<<fin[a]<<"\n";
        }
        file.open(file_name);
        for(size_t a = 0;a<attempt-1;a++){
            file << fin[a] << "\n";
        }

    }
}

void display(){
    std::fstream file;
    if(empty){} //Do Nothing
    else{
        std::cout<<"Username\t\tScore:\tAttempt:\n";
    }
    file.open(file_name,std::fstream::in);
    std::string temp;
    for(int x=1;x<(attempt);x++){
        getline(file,temp);
        std::cout<<x<<".";
        for(int y = 0;y<16;y++){
            std::cout<<temp[y];
        }
        std::cout<<"\t";
        for(int y = 16;y<22;y++){
            std::cout<<temp[y];
        }
        std::cout<<"\t";
        for(int y = 24;y<29;y++){
            std::cout<<temp[y];
        }
        std::cout<<"\n\n";
    }
    file.close();
}