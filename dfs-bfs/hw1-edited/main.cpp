

/*

    BLG336E Analysis of Algorithms
    Assigment -1- 
    <Emir Kaan Erdoğan>
    <150200706>  

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <unordered_set>
#include "kid.h"

using namespace std; 

void print_out_grid(vector <vector<int> > my_vector){
    for(int i=0;i<my_vector.size();i++){
        for(int j=0;j<my_vector[0].size();j++){
            cout<<my_vector[i][j]<<" "; 
        }
        cout<<endl ; 
    }
}
double get_distance(int x1,int y1,int x2,int y2){
    return (pow(double(x1-x2),2)+pow(double(y1-y2),2)); 
}
bool is_reachable(const Kid& kid1, const Kid& kid2){
    double distance = get_distance(kid1.get_xPosition(), kid1.get_yPosition(),
                                    kid2.get_xPosition(), kid2.get_yPosition());
    if(kid1.get_power() >= distance && kid2.get_power() >= distance){
        return true; 
    }
    return false; 
}

vector<vector<int> > create_grid(vector<Kid*> kids){
    vector <vector<int> > my_grid(kids.size(),vector<int>(kids.size()));
    //cout<<my_grid.size()<<","<<my_grid[0].size()<<endl ; 
    //print_out_grid(my_grid);
    for(int i=0;i<my_grid.size();i++){
        for(int j=0;j<my_grid[0].size();j++){
            if(i!=j){
                if(is_reachable(kids[i],kids[j])){
                    my_grid[i][j]=1;
                    my_grid[j][i]=1; 
                }
            }
        }
    }
    print_out_grid(my_grid);
    return my_grid; 
}

vector<Kid*> read_file(string file_name,vector<vector<int> >&my_grid,int* source_kid,int* target_kid){
    vector <Kid*> kids ; 
    int num_kids; 
    int num; 
    int row_counter=0 ;
    ifstream input_file(file_name);
    string line; 
    vector <vector<int> > row; 
    bool first_line=true; 
    bool first_col=true; 
    if(input_file.is_open()){
        while(getline(input_file,line)){
            stringstream ss(line); // create a stringstream from the line ; 
            string column; 
            int col_counter=0 ;
            while(ss>>num){
                //cout<<num<<" ";
                if(first_line){
                    if(first_col){
                        row.resize(num+1,vector<int>(3));
                        first_col=false; 
                    }  
                    row[0][col_counter]=num;
                }
                else{
                    row[row_counter][col_counter]=num; 
                }
                col_counter++; 
            }
            first_line=false;
            if(row_counter>0){
                kids.push_back(new Kid(row[row_counter][0],row[row_counter][1],row[row_counter][2]));
            }
            row_counter++;
            //cout<<endl; 
        }
    }
    else{
        cout<<"The file cannot be found"<<endl ;
        
    }
    input_file.close(); 
    /*
    for(int i=0;i<kids.size();i++){
        kids[i]->print_object();
    }
    */
    my_grid =create_grid(kids); 
    *source_kid=row[0][1];
    cout<<"Source Kid:"<<row[0][1]<<",Target Kid:"<<row[0][2]<<endl ;
    *target_kid= row[0][2];
     
    return kids; 
    
}
void print_parent_path(vector <int> parent_path,int src,int target){
    vector <int> path; 
    int current= target; 
    while(current!=src){
        path.push_back(current);
        current=parent_path[current] ;
    }
    cout<<endl ;
    cout<<path.size()<<" ";
    cout<<src;
    for(vector<int>::reverse_iterator i=path.rbegin(); i!=path.rend(); ++i){
    cout<<"->"<<*i;
    }
    cout<<endl ;
}
int min_passes(vector<vector<int> > grid, int src, int target) {
    /*
    To find the shortest path using BFS the following steps are implemented.
    1) a queue for kids and an unordered set to prevent ambigous search which is initially set to false 
    and a vector of distances that has the size of the grid and  
    2) while the queue is not empty iterate thorugh the unvisited nodes and mark them as visited
    and update the corresponding distance. The process should continue untill the distance of the target is achieved

    */
    queue<int> search_queue;
    unordered_set<int> visited;
    vector<int> dist(grid.size(), -1);
    vector<int> parent(grid.size(),-1); 
    // enqueue the source and set it as visited
    search_queue.push(src);
    visited.insert(src);
    // distance from source to itself is 0
    dist[src] = 0; 
    while (!search_queue.empty()) {
        // dequeue the node 
        int current_kid = search_queue.front();
        search_queue.pop();
        if (current_kid == target) { 
            print_parent_path(parent,src,target); 
            return dist[target];
        }
        // control the neighbours&& the kids that the current kid can pass to.
        for (int i = 0; i < grid[current_kid].size(); i++) {
            // the neighbouring kid should be reachable and has not been visited yet; 
            if (grid[current_kid][i] == 1 && visited.find(i) == visited.end()) {
                // mark the kid as visited and enqueue it
                visited.insert(i);
                search_queue.push(i);
                // update the distance for the neighbour  
                dist[i] = dist[current_kid] + 1; 
                parent[i]=current_kid ;
            }
        }
    }
    return -1; // target is not reachable from source
}
void print_out_cycle(vector<int> cycle){
    for(int i=0;i<cycle.size();i++){
        cout<<cycle[i]<<" "; 
    }
    cout<<endl ;
}

bool dfs(int u, int src, const vector<vector<int> >& adjMatrix, vector<int>& path, unordered_set<int>& visited, vector<int>& parent) {
    visited.insert(u);
    for (int v = 0; v < adjMatrix.size(); v++) {
        if (adjMatrix[u][v] == 1) {
            if (v == src && adjMatrix[src][u] == 1) {
                path.push_back(u);
                path.push_back(v);
                return true;
            }
            if (visited.find(v) == visited.end()) {
                parent[v] = u;
                if (dfs(v, src, adjMatrix, path, visited, parent)) {
                    if (u == src) {
                        path.push_back(src);
                    } else {
                        path.push_back(u);
                    }
                    return true;
                }
            }
            else if (parent[u] != v && v != src) {
                // Cycle found
                int curr = u;
                while (curr != v) {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                path.push_back(v);
                path.push_back(u);
                return true;
            }
        }
    }

    return false;
}

void print_cycle_first(const vector<vector<int> >&grid,int source){
    vector <int>path; 
    unordered_set<int> visited; 
    vector <int> parent(grid.size(),-1);
     
    if(dfs(source,source,grid,path,visited,parent)){
        cout<<"Cycle Found ! "<<endl; 
        cout<<path.size()<<" "; 
        for(int i=path.size();i>=0;i--){
            cout<<path[i]<<"->"; 
        }
        cout<<endl;
    } 
    else{
        cout<<"No cycle Found ! "<<endl ; 
    }
}

bool is_cyclic(const vector<vector<int> >& adjMatrix, unordered_set<int>& visited, vector<int>& path, int parent, int current, int source) {
    visited.insert(current);
    for (int i = 0; i < adjMatrix.size(); i++) {
        if (adjMatrix[current][i] == 1) {
            if (visited.find(i) == visited.end()) {
                if (is_cyclic(adjMatrix, visited, path, current, i, source)) {
                    if (path.back() == source) { // cycle contains source node
                        return true;
                    }
                    return false;
                }
            }
            else if (i != parent) {
                path.push_back(i);
                path.push_back(current);
                if (path.back() == source) { // cycle contains source node
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

void print_cycle(const vector<vector<int> >& grid, int source) {
    vector<int> path;
    unordered_set<int> visited;
    int parent = -1;
    if (is_cyclic(grid, visited, path, parent, source, source)) {
        cout << "Cycle Found ! " << endl;
        cout << source << "->";
        for (int i = path.size() - 1; i >= 0; i--) {
            /*
            if (path[i] == source) {
                cout << source << endl;
                break;
            }
            */
            cout << path[i] << "->";
        }
    }
    else {
        cout << "-1" << endl;
        cout << "No cycle found ! " << endl;
    }
}


int main(int argc,char** argv){

    /*
        INSERT ALL YOUR CODE IN HERE!
        Program Compile Command: g++ -std=c++11 -Wall -Werror main.cpp -o main
        Program Run Command: ./main <input.txt>
        Expected input: /graphs/case{$n}/input_{$n}.txt
        Expected output: graph.txt bfs.txt dfs.txt
        Please, try to write clean and readable code. Remember to comment!!
    */
    string file_name=argv[1];
    vector<vector<int> > my_grid; // adjacency matrix; 
    int* skidp=new int[1]; 
    int* tkidp=new int[1];
    vector <Kid*> my_vector= read_file(file_name,my_grid,skidp,tkidp);
    int source_kid= *skidp; 
    int target_kid = *tkidp ;
    //cout<<"source kid: "<<source_kid<<", target kid: "<<target_kid<<endl;
    // deallocate memory and avoid dangling pointer ;
    delete [] skidp;
    skidp=nullptr; 
    delete [] tkidp;
    tkidp=nullptr; 
    my_vector[source_kid]->print_object();
    my_vector[target_kid]->print_object(); 
    int minimum_passes=min_passes(my_grid,source_kid,target_kid);
    cout<<"The minimum Passes: "<<minimum_passes<<endl;
    print_cycle(my_grid,source_kid);
    return 0 ; 
}