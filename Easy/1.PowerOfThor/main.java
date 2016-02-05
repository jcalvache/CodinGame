/******************************************

  The Goal
Your program must allow Thor to reach the light of power.
  Rules
Thor moves on a map which is 40 wide by 18 high. Note that the coordinates (X and Y) start at the top left! This means the most top left cell has the coordinates "X=0,Y=0" and the most bottom right one has the coordinates "X=39,Y=17".

Once the program starts you are given:

    the variable lightX: the X position of the light of power that Thor must reach.
    the variable lightY: the Y position of the light of power that Thor must reach.
    the variable initialTX: the starting X position of Thor.
    the variable initialTY: the starting Y position of Thor.

At the end of the game turn, you must output the direction in which you want Thor to go among: 
*****************************************/
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
        int LX = in.nextInt(); // the X position of the light of power
        int LY = in.nextInt(); // the Y position of the light of power
        int TX = in.nextInt(); // Thor's starting X position
        int TY = in.nextInt(); // Thor's starting Y position
        
       
        // game loop
        while (true) {
            int E = in.nextInt(); // The level of Thor's remaining energy, representing the number of moves he can still make.
            //System.out.println("E");
            if(LX==TX && LY>TY){
                System.out.println("S");
                TY++;
            }
            else if(LX>TX && LY>TY){
                if((LX-LY)!=(TX-TY)){
                    System.out.println("E");
                    TX++;
                }
                else{
                    System.out.println("SE");
                    TX++;
                    TY++;
                }
            }
            else if(LX>TX && LY==TY){
                System.out.println("E");
                TX++;
            }
            else if(LX>TX && LY<TY){
                System.out.println("NE");
                TX++;
                TY--;
            }
            else if(LX==TX && LY<TY){
                System.out.println("N");
                TY--;
            }
            else if(LX<TX && LY<TY){
                System.out.println("NW");
                TX--;
                TY--;
            }
            else if(LX<TX && LY==TY){
                System.out.println("W");
                TX--;
            }
            else{ 
                System.out.println("SW");
                TX--;
                TY++;
            }
        }
    }
}