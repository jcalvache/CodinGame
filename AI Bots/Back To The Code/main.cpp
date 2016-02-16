/******************************************************************
The Goal
The aim of this game is to own the largest number of cells in a grid.
  Rules
You have two ways to claim ownership of a cell:

    By moving onto a neutral cell (and being the only one on that cell).
    By surrounding a collection of neutral cells with your own cells.

The grid works as follows:

    The grid is composed of 35 columns and 20 rows.
    The coordinates of the top left cell are (0 0).
    You can move around on the grid by specifying a target cell (X Y). You will then move only one cell in the direction of that target, vertically if you are on the same column, horizontally otherwise.

Each round, all players are moving at the same time. For a two-player game, the match will last at most 350 rounds (300 for three, 250 for four). Note that the game may end sooner if the game ranking cannot change no matter what happens next.
 
Victory Conditions
The winner is decided depending on the number of cells owned at the end of the game.
  Expert Rules
For expert CodinGamers (don't bother with this until you've really tried the rest), you can go back in time:

    Instead of moving, you can decide to go back in time using the BACK command followed by a number of rounds. For example the output BACK 10 on round 30 will revert the game state back to what it was on round 20.
    All players are affected, their last movements and cell ownership are rolled back by the specified number of rounds.
    The number of rounds you attempt to go back in time cannot exceed 25 rounds.
    If you try to go back to before the beginning of the game, you will only go back to the first round.
    If multiple players want to go back in time on the same round, the number of rounds they want to go back are added up. In this case, it is possible to go back more than 25 rounds :)
    You can go back in time only once per game.

You will no longer be able to play if:

    You try to go back in time more than once.
    The number of rounds you want to go back in time exceeds 25 rounds.

	
	
	

---> Explanation

	When this game came across I didn't have plenty of time to analyze several behaviours, 
so I tried to figure out some easy-to-implement algorithm able to earn its daily bread.
 
	At first, I began with a "sweeping" algorithms. This one goes to 0 0 position and, from there, 
sweeps the gameboard row by row. Not good at all.

	At second, after seeing some other algorithms working, I realized how they were earning cells.
So I thought in algorithm capable of make some kind of mess, cruising with itself as much as possible.
This came up with a surprisingly good result, just below the half of the scoring.

	Then I realized that, sometimes, it went to some points far away among them. So I thought in
some way to "organize" them. I divided the grid in 4 spaces, just like a cartessian axe, going from
one to the next in a clockwise rotation. This one achieved 1314/2901 position, not bad for a 
made-in-5-minutes algorithm!

	At last chance, I tried to avoid collision, this was really ruining my score, but I didn't
came up with anything better...
	
	
	
*******************************************************************/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

struct Opponents{
    int opponentX; // X position of the opponent
    int opponentY; // Y position of the opponent
    int opponentBackInTimeLeft; // Remaining back in time of the opponent
};

using namespace std;

void sweeping();
void randomPosition();
void clockwise();
void quadrants();
void quadrantsAvoidCollision();

int opponentCount; // Opponent count
Opponents *opponents;
string line[20];
int gameRound;
int x; // Your x position
int y; // Your y position
int backInTimeLeft; // Remaining back in time

//**** sweeping
bool corner = false;
//**** randomPosition, quadrants, quadrantsAvoidCollision
int tempX=-1, tempY;
//**** quadrantsAvoidCollision
char dir;


int main()
{
    srand (time(NULL));
    
    cin >> opponentCount; cin.ignore();
    opponents = new Opponents[opponentCount];

    // game loop
    while (1) {
        
        cin >> gameRound; cin.ignore();

        cin >> x >> y >> backInTimeLeft; cin.ignore();
        for (int i = 0; i < opponentCount; i++) {
           cin >> opponents[i].opponentX >> opponents[i].opponentY >> opponents[i].opponentBackInTimeLeft; cin.ignore();
        }
        for (int i = 0; i < 20; i++) {
            // One line of the map ('.' = free, '0' = you, otherwise the id of the opponent)
            cin >> line[i]; cin.ignore();
        }
        //sweeping();
        //randomPosition();
        quadrants();
        //quadrantsAvoidCollision();
    }
    
    delete opponents;
}

void sweeping(){
    if(x==0 && y==0) corner=true;
    if(!corner)cout << "0 0" << endl;
    else{
        if(y==0){
            if(line[y+1][x]=='0')cout<<x+1<<" "<<y<<endl;
            else cout<<x<<" "<<y+1<<endl;
        }
        else if(y==20){
            if(line[y-1][x]!='0')cout<<x<<" "<<y-1<<endl;
            else cout<<x+1<<" "<<y<<endl;
        }
        else if(line[y+1][x]=='0')cout<<x<<" "<<y-1<<endl;
        else cout<<x<<" "<<y+1<<endl;
    }
}

void randomPosition(){
    if((x==tempX && y==tempY) || tempX==-1){
        tempX=rand()%35;
        tempY=rand()%20;
    }
    
    cout<<tempX<<" "<<tempY<<endl;

}

/*
1|2
---
4|3
*/
void clockwise(){
    if(x<(35/2)){
        // First quadrant, go to second
        if(y<(20/2)){
            tempX=((rand()%35)/2)+(35/2);
            tempY=((rand()%20)/2);
            dir='r';
        }
        //Fourth quadrant, go to first
        else{
            tempX=((rand()%35)/2);
            tempY=((rand()%20)/2);
            dir='u';
        }
    }
    else{
        //Second quadrant, go to third
        if(y<(20/2)){
            tempX=((rand()%35)/2)+(35/2);
            tempY=((rand()%20)/2)+(20/2);
            dir='d';
        }
        //Third quadrant, go to fourth
        else{
            tempX=((rand()%35)/2);
            tempY=((rand()%20)/2)+(20/2);
            dir='l';
        }
    }
}

void quadrants(){
    if(tempX==-1){
        tempX=(rand()%35)/2;
        tempY=(rand()%20)/2;
    }
    
    else if(x==tempX && y==tempY) clockwise();
    
    cout<<tempX<<" "<<tempY<<endl;
}

void quadrantsAvoidCollision(){
    if(tempX==-1){
        tempX=(rand()%35)/2;
        tempY=(rand()%20)/2;
        dir='r';
    }
    
    else if(x==tempX && y==tempY) clockwise();
    
    else{
        if((dir=='r' && (line[y][x+1]!='.' || line[y][x+1]!='0')) ||
           (dir=='l' && (line[y][x-1]!='.' || line[y][x+1]!='0'))) tempX=x;
        else if((dir=='u' && (line[y-1][x]!='.' || line[y-1][x]!='0')) ||
                (dir=='d' && (line[y+1][x]!='.' || line[y+1][x]!='0'))) tempY=y;
    }
    
    cout<<tempX<<" "<<tempY<<endl;
}