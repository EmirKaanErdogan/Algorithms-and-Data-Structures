


/*
    BLG335E Analysis of Algorithms
    Assigment -1- 
    <Emir Kaan Erdoğan>
    <150200706>  
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std ;

int write_graph(const vector <vector<int> >&adj_matrix){
    ofstream outfile("graph.txt");
    if(!outfile.is_open()){
        cout<<"File cannot be opened !"<<endl ;
        return EXIT_FAILURE; 
    }
    outfile<< "Adjacency Matrix:"<<endl; 
    cout<<"Adjacency Matrix"<<endl ; 
    for(int i=0;i<adj_matrix.size();i++){
        for(int j=0;j<adj_matrix[0].size();j++){
            outfile<<adj_matrix[i][j]<<" ";
            cout<<adj_matrix[i][j]<<" "; 
        }
        outfile<<endl ;
        cout<<endl; 
    }
    outfile.close();
    return EXIT_SUCCESS;
}
int write_bfs(vector<int>&path,int source){
    ofstream outfile("bfs.txt");
    if(!outfile.is_open()){
        cout<<"File cannot be opened !"<<endl ;
        return EXIT_FAILURE; 
    }
    outfile<<path.size()<<" ";
    outfile<<source;
    for(vector<int>::reverse_iterator i=path.rbegin(); i!=path.rend(); ++i){
        outfile<<"->"<<*i;
    }
    
    outfile.close();

    return EXIT_SUCCESS;
}
int write_cycle(vector<int>&path,int source,bool is_cyclic){
    ofstream outfile("dfs.txt"); 
    if(!outfile.is_open()){
        cout<<"File cannot be opened !"<<endl ;
        return EXIT_FAILURE;
    }
    if(!is_cyclic){
        outfile<<"-1"; 
        outfile.close();
        return EXIT_SUCCESS;
    }
    outfile<<path.size()<<" ";
    for(int i=0;i<path.size();i++){
        outfile<<path[i]<<"->";
    }
    outfile<<source;
    outfile.close();
    return EXIT_SUCCESS;
}