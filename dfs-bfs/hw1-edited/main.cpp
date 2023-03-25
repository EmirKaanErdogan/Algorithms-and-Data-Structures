
/*
    BLG336E Analysis of Algorithms
    Assigment -1- 
    <Emir Kaan Erdoğan>
    <150200706>  
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 
#include "kid.h"
#include "read_csv.cpp"
using namespace std;


int main(){
    /*
        INSERT ALL YOUR CODE IN HERE!
        Program Compile Command: g++ -std=c++11 -Wall -Werror main.cpp -o main
        Program Run Command: ./main <input.txt>
        Expected input: /graphs/case{$n}/input_{$n}.txt
        Expected output: graph.txt bfs.txt dfs.txt
        Please, try to write clean and readable code. Remember to comment!!
    */
    // create the grid and the vector of pointers to Kid objects
    string file_name="input_1.txt";
    vector<vector<int> > my_grid; 
    int source_kid,target_kid;
    int* skidp=new int[1];
    skidp= &source_kid; 
    int* tkidp=new int[1];
    tkidp=&target_kid; 
    vector <Kid*> my_vector= read_file(file_name,my_grid,skidp,tkidp);
    cout<<"source kid: "<<*(skidp)<<", target kid: "<<*(tkidp)<<endl;
    cout<<"source kid: "<<source_kid<<", target kid: "<<target_kid<<endl;
    // deallocate memory and avoid dangling pointer ;
    delete [] skidp;
    skidp=nullptr; 
    delete [] tkidp;
    tkidp=nullptr; 
    
    exit(0);
}