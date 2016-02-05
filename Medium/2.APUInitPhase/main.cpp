/***************************************************

  The Goal
The game is played on a rectangular grid with a given size. Some cells contain power nodes. The rest of the cells are empty.

The goal is to find, when they exist, the horizontal and vertical neighbors of each node.
  Rules
To do this, you must find each (x1,y1) coordinates containing a node, and display the (x2,y2) coordinates of the next node to the right, and the (x3,y3) coordinates of the next node to the bottom within the grid.

If a neighbor does not exist, you must output the coordinates -1 -1 instead of (x2,y2) and/or (x3,y3).

You lose if:

    You give an incorrect neighbor for a node.
    You give the neighbors for an empty cell.
    You compute the same node twice.
    You forget to compute the neighbors of a node.


************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    string line[height];
    
    for (int i = 0; i < height; i++) {
        getline(cin, line[i]);
    }
    
    ostringstream oss;
    bool found = false;
    
    for(int i=0;i<height;++i){
        for(int j=0;j<width;j++){
            if(line[i][j]=='0'){
                //Actual node coordinates
                oss << j << " " << i << " ";
                
                //Check nodes to the right
                for(int k=j+1;k<width && !found;k++){
                    if(line[i][k] == '0'){
                        oss<<k<<" "<<i<<" ";
                        found=true;
                    }
                }
                if(!found)oss<<"-1 -1 ";
                found=false;
                
                //Check nodes to the bottom
                for(int k=i+1;k<height && !found;k++){
                    if(line[k][j] == '0'){
                        oss<<j<<" "<<k;
                        found=true;
                    }
                }
                if(!found)oss<<"-1 -1";
                found=false;
                
                if(i<height-1 && j<width-1) oss<<" ";
                
                cout << oss.str() << endl;
                oss.str("");
            }
        }//j
    }//i
   
}