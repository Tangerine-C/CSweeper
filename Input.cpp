//
// Created by matth on 12/4/2023.
//
#include <iostream>
#include <string>
#include "input.h"
int allowY = 0;
template <typename input>
input clean(input x){ //Compatible bufferClear and Retry function
    std::cin.clear();
    std::cin.ignore();
    std::cout<<"Invalid character (non-integer). Please enter an integer.";
    std::cin>>x;
    return x;
}


std::string input_state(){
    int v,z;
    std::string state;
    for(z=1;z>0;){
        std::cout<<"Please select a selection mode.\n(1) OPEN\n(2) MARK";
        std::cin>>v;
        while(std::cin.fail()){
            v = clean(v);
        }
        switch(v){
            case(1):state="[OPEN]";break;
            case(2):state="[MARK]";break;
            default:state="[NULL]";break;
        }
        if(state=="[NULL]"){
            std::cout<<"Invalid Selection, Try Again.";
        }
        else{
            z=0;
        }
    }
    return state;
}
int input_x(int diff){
    int z,x;
    for(z=1;z>0;){
        std::cout<<"\nX: ";std::cin>>x;
        while(std::cin.fail()){
            x = clean(x);
        }
        if(x<0){
            allowY=0; //Doesn't Allow Y to be chosen
            return -1;
        }
        else if(diff==1&&x>8){
            std::cout<<"Integer Out of Range [0 - 8]... Try Again.";
        }
        else if(diff==2&&x>16){
            std::cout<<"Integer Out of Range [0 - 16]... Try Again.";
        }
        else if(diff==3&&x>30){
            std::cout<<"Integer Out of Range [0 - 30]... Try Again.";
        }
        else{
            x--; //To match the tile on array
            z=0;
            allowY = 1;
        }
    }
    return x;
}

int input_y(int diff){
    int z,y;
    if(allowY==0){
        return 0;
    }
    else{
        for(z=1;z>0;){
            std::cout<<"\nY: ";std::cin>>y;
            while(std::cin.fail()){
                y = clean(y);
            }
            if(y<0){
                allowY = 0;
                return -1;
            }
            else if(diff==1&&y>8){
                std::cout<<"Integer Out of Range [0 - 8]... Try Again.";
            }
            else if((diff==2||diff==3)&&y>16){
                std::cout<<"Integer Out of Range [0 - 16]... Try Again.";
            }
            else{
                y--; //To match the tile on array
                z=0;
                allowY=0;
            }
        }
    }
    return 0;
}
