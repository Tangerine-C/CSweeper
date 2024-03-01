//
// Created by matth on 12/1/2023.
//
#include <iostream>
#include "debug.h"
void values(int grid[][30],int limit1,int limit2){
    std::cout<<std::endl<<"_______________________________________________________________________________________________________\n";
    for (int a = 0; a < limit1 + 1; a++) {
        for (int b = 0; b < limit2 + 1; b++) {
            if (a == 0 && b == 0) {
                std::cout << "Grid Values:\n";
            }
            std::cout << grid[a][b]; //It's tabbed to allow for uniformity.
            if (grid[a][b] < 99) {
                std::cout << " ";
            }
            std::cout << " ";
            if (b == limit2) {
                std::cout << "\n";
            }
        }
    } //DEBUG EXTENDED
    int test = 0;
    for (int a = 0; a < limit1 + 1; a++) { //[DEBUG ONLY] COMMENT OUT THIS FUNCTION FOR ACTUAL USE!
        for (int b = 0; b < limit2 + 1; b++) {
            if (grid[a][b] == 99) {
                test++;
            }
        }
    }
    std::cout << "Number of Mines: " << test << "\n\n"; //
}

//REVEAL CODE VISIBILITY------------------------------------------------------------------------------------------------
void reveal(int hidden[][30],int limit1,int limit2){
    for (int a = 0; a < limit1 + 1; a++) {
        for (int b = 0; b < limit2 + 1; b++) {
            if (a == 0 && b == 0) {
                std::cout << "Grid Visibility:\n"; //PRINTS THE GRID OF VISIBLE SPOTS, ANY 1s IN THE ARRAY ARE GOING TO BE VISIBLE IN THE GAME'S
//shown[][] ARRAY AND DISPLAYED GRID. THIS DEBUG IS TO CONFIRM THAT THE POINTS IN THE ARRAY (hidden[][]) MATCH THOSE IN THE
//GAME'S DISPLAYED ARRAY (shown[][])
            }
            std::cout << hidden[a][b]; //It's tabbed to allow for uniformity.
            std::cout << " ";
            if (b == limit2) {
                std::cout << "\n";
            }
        }
    }
    int test = 0; //THIS FOR LOOP CHECK THE ENTIRE ARRAY FOR ALL SPOTS THAT ARE VISIBLE TO THE USER.
    for (int a = 0; a < limit1 + 1; a++) {
        for (int b = 0; b < limit2 + 1; b++) {
            if (hidden[a][b] == 1) {
                test++;
            }
        }
    }
    std::cout << "Number of Starting Spots: " << test << "\n\n";
}
//REVEAL CODE GAME------------------------------------------------------------------------------------------------------
void reveal_game(int grid[][30],int limit1,int limit2){
    std::cout<<std::endl<<"_______________________________________________________________________________________________________\n";
    for (int a = 0; a < limit1 + 1; a++) { //[DEBUG ONLY] COMMENT OUT THIS FUNCTION FOR ACTUAL USE!
        for (int b = 0; b < limit2 + 1; b++) {
            if (a == 0 && b == 0) {
                std::cout << "Current Grid:\n";
            }
            std::cout << grid[a][b]; //It's tabbed to allow for uniformity.
            if (grid[a][b] < 99) {
                std::cout << " ";
            }
            std::cout << " ";
            if (b == limit2) {
                std::cout << "\n";
            }
        }
    }
}