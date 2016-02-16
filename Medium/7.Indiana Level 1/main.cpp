/*******************************************************************

@Author: Javier Calvache (jcalvache@rocketmail.com)

The Goal
Your objective is to write a program capable of predicting the route Indy will take on his way down a tunnel. Indy is not in danger of getting trapped in this first mission.
  Rules
The tunnel consists of a patchwork of square rooms of different types.The rooms can be accessed and activated by computer using an ancient RS232 serial port (because Mayans aren't very technologically advanced, as is to be expected...).

There is a total of 14 room types (6 base shapes extended to 14 through rotations).

Upon entering a room, depending on the type of the room and Indy's entrance point (TOP,LEFT, or RIGHT) he will either exit the room through a specific exit point, suffer a lethal collision or lose momentum and get stuck:

Type 0 	This room type is not part of the tunnel per se as Indy cannot move across it.

Type 1 	The green arrows indicate Indy's possible paths through the room.

Type 2 	
Type 3 	The room of type 3 is similar to the room of type 2 but rotated.

Type 4 	
Type 5 	A red arrow indicate a path that Indy cannot use to move across the room.

Type 6 	
Type 7 	
Type 8 	
Type 9

Type 10 	
Type 11 	
Type 12 	
Type 13

Indy is perpetually drawn downwards: he cannot leave a room through the top.

At the start of the game, you are given the map of the tunnel in the form of a rectangular grid of rooms. Each room is represented by its type.

For this first mission, you will familiarize yourself with the tunnel system, the rooms have all been arranged in such a way that Indy will have a safe continuous route between his starting point (top of the temple) and the exit area (bottom of the temple).

Each game turn:

    You receive Indy's current position
    Then you specify what Indy's position will be next turn.
    Indy will then move from the current room to the next according to the shape of the current room.

 
Victory Conditions
Indy reaches the exit
 
Lose Conditions
You assert an incorrect position for Indy

*************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void fillMatrix(int **m, const int W, const string s, const int row){
    int index=0, beg=0;

    for(int i=0;i<s.length();++i){
        if(s[i]==' ' || i==s.length()-1){
            m[row][index] = stoi(s.substr(beg,i));
            beg=i;
            index++;
        }
    }  
}

void printMatrix(int **m, const int W, const int H){
    for(int i=0;i<H;++i){
        for(int j=0;j<W;j++)
            cerr<<m[i][j]<<" ";
        cerr<<endl;
    }
}

void init(list<pair<int,pair<char,char>>> &l){
    pair<int,pair<char,char>> p;
    p.first=1;
    p.second.first='L';
    p.second.second='D';    
    l.push_back(p);
    p.second.first='T';
    l.push_back(p);
    p.second.first='R';
    l.push_back(p);
    
    p.first=2;
    p.second.first='L';
    p.second.second='R';
    l.push_back(p);
    p.second.first='R';
    p.second.second='L';
    l.push_back(p);
    
    p.first=3;
    p.second.first='T';
    p.second.second='D';
    l.push_back(p);
    
    p.first=4;
    p.second.second='L';
    l.push_back(p);
    p.second.first='R';
    p.second.second='D';
    l.push_back(p);
    
    p.first=5;
    p.second.first='L';
    p.second.second='D';
    l.push_back(p);
    p.second.first='T';
    p.second.second='R';
    l.push_back(p);
    
    p.first=6;
    p.second.first='L';
    p.second.second='R';
    l.push_back(p);
    p.second.first='R';
    p.second.second='L';
    l.push_back(p);
    
    p.first=7;
    p.second.first='T';
    p.second.second='D';
    l.push_back(p);
    p.second.first='R';
    l.push_back(p);
    
    p.first=8;
    l.push_back(p);
    p.second.first='L';
    l.push_back(p);
    
    p.first=9;
    p.second.first='L';
    l.push_back(p);
    p.second.first='T';
    l.push_back(p);
    
    p.first=10;
    p.second.first='T';
    p.second.second='L';
    l.push_back(p);
    
    p.first=11;
    p.second.second='R';
    l.push_back(p);
    
    p.first=12;
    p.second.first='R';
    p.second.second='D';
    l.push_back(p);
    
    p.first=13;
    p.second.first='L';
    l.push_back(p);
}

void printList(list<pair<int,pair<char,char>>> l){
    list<pair<int,pair<char,char>>>::iterator it = l.begin();
    
    while(it!=l.end()){
        cerr<<it->first<<"-"<<it->second.first<<" "<<it->second.second<<endl;
        it++;
    }
    
}   


char nextMove(pair<int,int> pos, string move, int **m, list<pair<int,pair<char,char>>> l){
    int roomType = m[pos.second][pos.first];
    
    list<pair<int,pair<char,char>>>::iterator it=l.begin();
    bool found=false;
    char dir;
    while(it!=l.end() && !found){
        if(it->first==roomType && it->second.first==move[0]) found=true;
        else it++;
    }
    
    return it->second.second;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();

    int **m=new int*[H];
    for(int i=0;i<H;++i) m[i]=new int[W];
    
    for (int i = 0; i < H; i++) {
        string LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        getline(cin, LINE);
        fillMatrix(m,W,LINE,i);
    }
    
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();
    
    list<pair<int,pair<char,char>>> rooms;
    init(rooms);


    // game loop
    while (1) {
        pair<int,int> pos;
        string move;
        cin >> pos.first >> pos.second >> move; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        char next = nextMove(pos, move, m, rooms);
        
        if(next=='R') cout<<pos.first+1<<" "<<pos.second<<endl;
        else if(next=='L') cout<<pos.first-1<<" "<<pos.second<<endl;
        else cout<<pos.first<<" "<<pos.second+1<<endl;
    }
    
    for(int i=0;i<W;++i) delete[] m[i];
    delete[] m; 
}