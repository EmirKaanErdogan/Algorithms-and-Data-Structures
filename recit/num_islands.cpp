#include <iostream>
#include <vector>
using namespace std; 

void take_input(vector<vector<char> >&grid,int row,int columns){
    grid.resize(row);
    for(int i=0;i<row;i++){
        grid[i].resize(columns); 
    } 
    for(int i=0;i<row;i++){
        for(int j=0;j<columns;j++){
            cout<<"Row "<<i+1<<" Column "<<j+1<<": "<<endl ; 
            cin>>grid[i][j]; 
        }
    }
}
void print_grid(vector<vector<char> >grid){
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl; 
    }
}
void dfs(vector<vector<char> >&grid,int row,int col){
    int rows=grid.size();
    int columns=grid[0].size();
    if(row<0||row>=rows ||col<0|| col>=columns){
        return; 
    }
    if(grid[row][col]!='1'){
        return; 
    }
    grid[row][col]='V'; 
    dfs(grid,row-1,col); 
    dfs(grid,row+1,col);
    dfs(grid,row,col+1);
    dfs(grid,row,col-1);
}
int numIslands(vector<vector<char> >& grid) {
    int rows=grid.size();
    int columns=grid[0].size();
    int num_islands=0; 
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(grid[i][j]=='1'){
                dfs(grid,i,j);
                num_islands+=1;
            }
        }
    }
    return num_islands; 
}
int main(){

    vector <vector <char> > grid ;
    int rows;
    int columns; 
    cout<<"The number of rows: " ;
    cin>>rows;
    cout<<"The number of columns ";
    cin>>columns; 
    take_input(grid,rows,columns); 
    print_grid(grid); 
    cout<<"Number of Islands: "<<numIslands(grid); 
    return EXIT_SUCCESS; 
}
/*
Test Case: 

grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Answer:1 ;
*/
