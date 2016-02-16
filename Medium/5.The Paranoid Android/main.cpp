/*******************************************************************

@Author: Javier Calvache (jcalvache@rocketmail.com)

The Goal
You need to help Marvin and his clones (or is it the other way round?) reach the exit in order to help them escape the inside of the Infinite Improbability Drive.
  Rules
The drive has a rectangular shape of variable size. It is composed of several floors (0 = lower floor) and each floor has several possible positions that the clones can occupy (0 = leftmost position, width - 1 = rightmost position).

The goal is to save at least one clone in a limited amount of rounds.

The details:

    Clones appear from a unique generator at regular intervals, every three game turns. The generator is located on floor 0. Clones exit the generator heading towards the right.

    Clones move one position per turn in a straight line, moving in their current direction.

    A clone is destroyed by a laser if it is goes below position 0 or beyond position width - 1.

    Elevators are scattered throughout the drive and can be used to move from one floor to the one above. When a clone arrives on the location of an elevator, it moves up one floor. Moving up one floor takes one game turn. On the next turn, the clone continues to move in the direction it had before moving upward.

    On each game turn you can either block the leading clone - meaning the one that got out the earliest - or do nothing.

    Once a clone is blocked, you can no longer act on it. The next clone in line takes the role of "leading clone" and can be blocked at a later time.

    When a clone moves towards a blocked clone, it changes direction from left to right or right to left. It also changes direction when getting out of the generator directly on a blocked clone or when going up an elevator onto a blocked clone.

    If a clone is blocked in front of an elevator, the elevator can no longer be used.

    When a clone reaches the location of the exit, it is saved and disappears from the area.

Note: For the first simple question, there is at most one elevator per floor.

Victory Conditions
You win if at least one clone reaches the exit location in a limited amount of game rounds

***********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int elevatorPos(pair<int,int> *p, int length, int floor){
    int i;
    for(i=0;i<length && p[i].first!=floor;++i);
    
    return p[i].second;
}        

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    
    pair<int,int> elevators[nbElevators];
    for (int i = 0; i < nbElevators; i++) {
        cin >> elevators[i].first >> elevators[i].second; cin.ignore();
    }

    int i=0;
    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        if(cloneFloor == exitFloor){
            if(exitPos<clonePos){
                if(direction=="LEFT") cout<<"WAIT"<<endl;
                else cout<<"BLOCK"<<endl;
            }
            else{
                if(direction=="RIGHT") cout<<"WAIT"<<endl;
                else cout<<"BLOCK"<<endl;
            }
        }        
        else if(elevatorPos(elevators, nbElevators, cloneFloor) == clonePos) cout<<"WAIT"<<endl;
        else if(elevatorPos(elevators, nbElevators, cloneFloor) < clonePos){        
            if(direction=="LEFT") cout<<"WAIT"<<endl;
            else cout<<"BLOCK"<<endl; 
        }
        else{
            if(direction=="RIGHT") cout<<"WAIT"<<endl;
            else cout<<"BLOCK"<<endl; 
        }

        cerr<<direction<<"-"<<cloneFloor<<"-"<<elevatorPos(elevators, nbElevators, cloneFloor)<<"/"<<clonePos<<endl;
    }
}