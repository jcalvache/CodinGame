/***********************************

	@Author: Javier Calvache (jcalvache@rocketmail.com)

  The Goal
Write the program that destroys the mountains before your starship collides with one of them.
  Rules
Your starship moves along the horizontal axis across 8 cells at an initial height of 10 kilometers. Each cell contains a mountain, some taller than others (from 0 to 9 kilometers).
The starship circles above all the mountains, going first from left to right, then from right to left, and so on and so forth. With each complete pass, the starship descends one kilometer as it is being drawn to the surface by an unknown force.

At the start of each game turn, you are given:

    the variable spaceX: the horizontal coordinate of your ship (0 to 7)
    the variable spaceY: the altitude at which your ship is advancing in kilometers (10 to 1)
    the height of each mountain from left to right (8 values mountainH)

By the end of the game turn, you must output one of the following commands:

    HOLD: your ship does not fire.
    FIRE: your ship shoots the mountain directly below it.

However, you may fire only once per pass. Firing on a mountain base will only destroy part of it and it will sink a random number of kilometers.
Once the turn is finished, your ship moves one cell forwards, descending by a kilometer if it completes a pass.
***********************************/
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
        
        int MH[]=new int [8];

        // game loop
        while (true) {
            int SX = in.nextInt();
            int SY = in.nextInt();
            in.nextLine();
            for (int i = 0; i < 8; i++) {
                MH[i] = in.nextInt(); // represents the height of one mountain, from 9 to 0. Mountain heights are provided from left to right.
                in.nextLine();
            }
            
            if(SX==major(MH)) System.out.println("FIRE");
            else System.out.println("HOLD");

            }
    }
    
    public static int major(int n[]){
       int major = 0;
       for(int i=1;i<8;++i){
           if(n[i]>n[major]) major=i;
       }
       return major;
    }
}