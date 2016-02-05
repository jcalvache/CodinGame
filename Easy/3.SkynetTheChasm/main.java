/***********************************

  The Goal
The goal for your program is to make a motorbike jump across a gap and land on a platform then stop.
  Rules

The platform is located on the otherside of a gap in the road above a chasm. The lengths of the road, gap and platform are measured in cells.
 

At the start of the program, you are given:

    The variable road: the length of the road before the gap.
    The variable gap: the length of the gap.
    The variable platform: the length of the platform.

At the start of each game turn, the motorbike gives you:

    The variable speed: its current speed.
    The variable coordX: its position on the road.

The motorbike's initial position is coordX = 0. It always moves in a straight line. At the end of each turn, it moves forward a number of spaces equal to its speed (speed). For example, if coordX = 1 and speed = 3, coordX will be 4 at the next turn. The bike can start with any speed, including being at a stop.
 

Before the end of the turn, you must output one of the following commands:

    SPEED: increases the speed of the motorbike by 1 (+1 to the speed variable).
    SLOW: decreases the speed of the motorbike by 1 (-1 to the speed variable).
    JUMP: makes the motorbike jump.
    WAIT: does nothing (the motorbike keeps the same speed).


**********************************/

import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int R = in.nextInt(); // the length of the road before the gap.
        in.nextLine();
        int G = in.nextInt(); // the length of the gap.
        in.nextLine();
        int L = in.nextInt(); // the length of the landing platform.
        in.nextLine();

        // game loop
        while (true) {
            int S = in.nextInt(); // the motorbike's speed.
            in.nextLine();
            int X = in.nextInt(); // the position on the road of the motorbike.
            in.nextLine();
            
            // Write an action using System.out.println()
            // To debug: System.err.println("Debug messages...");

            if((X+S)<R+1){
                if(S<G+1) System.out.println("SPEED");
                else if(S>G+1) System.out.println("SLOW");
                else System.out.println("WAIT");
            }
            else if(X<R) System.out.println("JUMP");
            else System.out.println("SLOW");
        }
    }
}