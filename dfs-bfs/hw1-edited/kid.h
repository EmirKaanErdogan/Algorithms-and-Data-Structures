


/*

    BLG336E Analysis of Algorithms
    Assigment -1- 
    <Emir Kaan Erdoğan>
    <150200706>  

*/

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h> 
using namespace std; 

class Kid{
    private:
        int x_position; 
        int y_position; 
        int power; 
    public:
        Kid(); // default constructor 
        Kid(int x_position,int y_position,int power); // constructor with parameters; 
        Kid(Kid*);// copy constructor 
        void print_object()const; 
        // Getters ; 
        int get_xPosition()const{
            return this->x_position; 
        }
        int get_yPosition()const{
            return this->y_position;
        }
        int get_power()const {
            return this->power; 
        }
        // Setters 
        void set_xPosition(int x_position){
            this->x_position=x_position; 
        }
        void set_yPosition(int y_position){
            this->y_position=y_position;
        }
        void set_power(int power){
            this->power=power; 
        }
};

#endif