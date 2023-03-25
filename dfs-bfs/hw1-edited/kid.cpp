
/*
    BLG336E Analysis of Algorithms
    Assigment -2- 
    <Emir Kaan Erdoğan>
    <150200706>  
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "kid.h"

using namespace std ;


Kid::Kid(){
    cout<<"Welcome to Default Constructor ! "<<endl ; 
}
Kid::Kid(int x_positon,int y_position,int power){
    this->x_position=x_positon;
    this->y_position=y_position;
    this->power=power; 
}
Kid::Kid(Kid* copy_kid){
    this->x_position=copy_kid->x_position;
    this->y_position=copy_kid->y_position;
    this->power=copy_kid->power; 
}
void Kid::print_object()const{
    cout<<"X pos: "<<this->x_position<<", Y pos: "<<this->y_position<<" , Power: "<<this->power<<endl; 
}