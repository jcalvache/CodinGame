/******************************************************************

@author Javier Calvache (jcalvache@rocketmail.com)


The Goal
The game is played on a board of 9x9 square spaces. At the start of the game, each player starts on one side of the board.

The objective is to reach the other side of the board before the other players do.
  Rules
Players take turns moving their dragon:

    The first player (id = 0) always starts somewhere on the left edge of the board and must reach any cell on the right edge.
    The second player (id = 1) always starts somewhere on the right edge of the board and must reach any cell on the left edge.
    The third player (id = 2) always starts somewhere on the top edge of the board and must reach any cell on the bottom edge.


On each turn of the game, a player may do one of two things:

    Move to an adjacent cell in any direction ( LEFT, RIGHT, UP, DOWN).
    Place a wall somewhere on the board.

Wall placement:

    The player must indicate the cell on which he/she places a wall on its top left corner, as well as the wall orientation (horizontal or vertical).
    A wall is two cells long.
    Walls cannot cross. If a player tries to put a wall atop another wall, he/she loses the game. But it is still possible to put a vertical wall in between two horizontal walls (--|--).
    A wall may not be placed if it cuts off the only remaining path of any player to the side of the board it must reach. Walls may only be used to slow down an opponent's progress across the board.
    Each player may place a limited amount of walls: 10 each in a 2 player match and 6 each in a 3 player match.

In games with more than 2 players, players are ranked by the order of finish.

A player will lose if he/she attempts:

    An illegal wall placement: crossing an existing wall, sticking out the edge of the board, or cutting off a player's only path to his goal.
    An illegal move: moving outside the board or moving into a wall.

Players not having reached the opposite side of the board within 100 turns will tie for last place.
 
Victory Conditions
You win when you reach the opposite side of the board


---->Explanation
This is a quite simple algorithm, it just avoids collision and it goes as straight as possible to the opposite side. It is only valid for player 1 (from left to the right) and itmakes no use of walls.


******************************************************************************/

using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player
{
    static void Main(string[] args)
    {
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
        int w = int.Parse(inputs[0]); // width of the board
        int h = int.Parse(inputs[1]); // height of the board
        int playerCount = int.Parse(inputs[2]); // number of players (2 or 3)
        int myId = int.Parse(inputs[3]); // id of my player (0 = 1st player, 1 = 2nd player, ...)
        Point[] players = new Point[playerCount];
        string lastDir = "";
        

        // game loop
        while (true)
        {
            for (int i = 0; i < playerCount; i++)
            {
                inputs = Console.ReadLine().Split(' ');
                players[i].X = int.Parse(inputs[0]); // x-coordinate of the player
                players[i].Y = int.Parse(inputs[1]); // y-coordinate of the player
                int wallsLeft = int.Parse(inputs[2]); // number of walls available for the player
            }
            int wallCount = int.Parse(Console.ReadLine()); // number of walls on the board
            Point[] walls = new Point[wallCount];
            string[] wallOrientation = new string[wallCount];
            for (int i = 0; i < wallCount; i++)
            {
                inputs = Console.ReadLine().Split(' ');
                walls[i].X = int.Parse(inputs[0]); // x-coordinate of the wall
                walls[i].Y = int.Parse(inputs[1]); // y-coordinate of the wall
                wallOrientation[i] = inputs[2]; // wall orientation ('H' or 'V')
            }

            // Write an action using Console.WriteLine()
            // To debug: Console.Error.WriteLine("Debug messages...");


            // action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
            if(myId == 0){                
                if(crash(players[myId], walls, "RIGHT", wallOrientation)){
                    if(lastDir.Equals("UP")){
                        if(players[myId].Y > 0){
                            Console.WriteLine("UP");
                        }
                        else{
                            Console.WriteLine("DOWN");
                            lastDir = "DOWN";
                        }
                    }
                    else{
                        if(players[myId].Y < h-1){
                            Console.WriteLine("DOWN");
                        }
                        else{
                            Console.WriteLine("UP");
                            lastDir = "UP";
                        }
                    }
                }
                else{
                    Console.WriteLine("RIGHT");
                }
            }
            
        }
    }
    
    static bool crash(Point player, Point[] walls, string myDirection, string[] wallOrientation){
        bool crash = false;
        Point nextPosition = player;
        Point secondWallPos;
        string wrongOrientation = "";
        
        if(myDirection.Equals("UP")){
            nextPosition.Y--;
            wrongOrientation = "H";
        }
        else if(myDirection.Equals("DOWN")){
            nextPosition.Y++;
            wrongOrientation = "H";
        }
        else if(myDirection.Equals("LEFT")){
            nextPosition.X--;
            wrongOrientation = "V";
        }
        if(myDirection.Equals("RIGHT")){
            nextPosition.X++;
            wrongOrientation = "V";
        }
        
        for(int i=0;i<walls.Length && !crash;++i){
            secondWallPos = walls[i];
            if(wallOrientation[i].Equals("H")) secondWallPos.X++;
            else secondWallPos.Y++;
            
            if((nextPosition == walls[i] || nextPosition == secondWallPos) && wrongOrientation.Equals(wallOrientation[i])){
                crash = true;
                Console.Error.WriteLine("CRASH!!!");
            }
        }
        
        Console.Error.WriteLine(player);
        
        return crash;
    }
}

