

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
    cout<<"***********************************"<<endl ;
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
    cout<<my_grid.size()<<","<<my_grid[0].size()<<endl ; 
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
    for(int i=0;i<kids.size();i++){
        kids[i]->print_object();
    }
    my_grid =create_grid(kids); 
    *source_kid=row[0][1];
    cout<<row[0][1]<<","<<row[0][2]<<endl ;
    *target_kid= row[0][2];
     
    return kids; 
    
}
int min_passes(vector<vector<int> > grid,string* direction, int src, int target) {
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
/*
bool dfs(vector <vector<int> >&grid, unordered_set<int> &visited,vector<int>& cycle,int current,int parent){
    visited.insert(current); 
    for (int v = 0; v < grid.size(); v++) {
        if (grid[current][v] == 1) {
            if (visited.find(v) == visited.end()) {
                if (dfs(grid,visited,cycle,current,parent)) {
                    return true;
                }
            } else if (v != parent) {
                cycle.push_back(v);
                int curr = current;
                while (curr != v) {
                    cycle.push_back(curr);
                    curr = parent[curr];
                }
                cycle.push_back(v);
                return true;
            }
        }
    }
    return false;
}
*/
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
            } else if (parent[u] != v && v != src) {
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
}/*
bool exist_cycle(vector<vector<int> >grid,int source,vector<int>&path){
    cout<<"welcome!"<<endl ;
    unordered_set<int> visited; 
    int n=grid.size();
    int* parent= new int[1000];
    updated_dfs(grid,visited,path,source,parent);
}*/
void print_cycle(const vector<vector<int> >&grid,int source){
    vector <int>path; 
    unordered_set<int> visited; 
    vector <int> parent(grid.size(),-1);
    if(dfs(source,source,grid,path,visited,parent)){
        cout<<"Cycle Found ! "; 
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
int main(){
    string file_name="graphs/case3/input_3.txt";
    vector<vector<int> > my_grid; // adjacency matrix; 
    int* skidp=new int[1]; 
    int* tkidp=new int[1];
    string direction= ""; 
    string* directionp=&direction; 
    vector <Kid*> my_vector= read_file(file_name,my_grid,skidp,tkidp);
    cout<<"source kid: "<<*(skidp)<<", target kid: "<<*(tkidp)<<endl;
    int source_kid= *skidp; 
    int target_kid = *tkidp ;
    cout<<"source kid: "<<source_kid<<", target kid: "<<target_kid<<endl;
    // deallocate memory and avoid dangling pointer ;
    delete [] skidp;
    skidp=nullptr; 
    delete [] tkidp;
    tkidp=nullptr; 
    my_vector[source_kid]->print_object();
    my_vector[target_kid]->print_object(); 
    cout<<min_passes(my_grid,directionp,source_kid,target_kid)<<" "<<endl;
    //cout<<*directionp;
    print_cycle(my_grid,source_kid);
    return 0 ; 
}
