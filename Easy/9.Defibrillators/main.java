/********************************

	@Author: Javier Calvache (jcalvache@rocketmail.com)
	
  The Goal
The city of Montpellier has equipped its streets with defibrillators to help save victims of cardiac arrests. The data corresponding to the position of all defibrillators is available online.

Based on the data we provide in the tests, write a program that will allow users to find the defibrillator nearest to their location using their mobile phone.
  Rules
The input data you require for your program is provided in text format.
This data is comprised of lines, each of which represents a defibrillator. Each defibrillator is represented by the following fields:

    A number identifying the defibrillator
    Name
    Address
    Contact Phone number
    Longitude (degrees)
    Latitude (degrees)

These fields are separated by a semicolon (;).

Beware: the decimal numbers use the comma (,) as decimal separator. Remember to turn the comma (,) into dot (.) if necessary in order to use the data in your program.
 
DISTANCE
The distance d between two points A and B will be calculated using the following formula:
x=(longitudeB - longitudeA)*cos((latitudeA + latitudeB)/2)
y=latitudeB - latitudeA
d=sqrt(x^2 + y^2)*6371
Note: In this formula, the latitudes and longitudes are expressed in radians. 6371 corresponds to the radius of the earth in km.

The program will display the name of the defibrillator located the closest to the user’s position. This position is given as input to the program.

********************************/

import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        String uLon = in.next();
        uLon=semiColonByPoint(uLon);
        double uLON = Double.parseDouble(uLon);
        in.nextLine();
        String uLat = in.next();
        uLat=semiColonByPoint(uLat);
        double uLAT = Double.parseDouble(uLat);
        in.nextLine();
        int n = in.nextInt();
        in.nextLine();
        
        double x,y,d,min=0;
        int pos=0;
        String address = "";
        
        for (int i = 0; i < n; i++) {
            String s = in.nextLine();
            
            x=(Lon(s)-uLON)*Math.cos((Lat(s)+uLAT)/2.);
            y=(Lat(s)-uLAT);
            d=Math.sqrt((x*x)+(y*y))*6371;
            
            if(i==0){
                min=d;
                address = Address(s);
            }
                
            else if(d<min){
                min=d;
                pos=i;
                address = Address(s);
            }
        }

        System.out.println(address);
    }
    
    public static double Lon(String s){
        int ini=0, fin=0, semiColons = 0;
        
        for(ini = 0;ini < s.length() && semiColons < 4;++ini) if(s.charAt(ini) == ';') semiColons++;
        for(fin = ini;s.charAt(fin) != ';';++fin);
        
        return Double.parseDouble(semiColonByPoint(s.substring(ini,fin)));
    }
    
    public static double Lat(String s){
        int ini=0, semiColons = 0;
        
        for(ini = 0;ini < s.length() && semiColons < 5;++ini) if(s.charAt(ini) == ';') semiColons++;
        
        return Double.parseDouble(semiColonByPoint(s.substring(ini,s.length())));
    }
    
    public static String Address(String s){
        int ini=0, fin=0, semiColons = 0;
        
        for(ini = 0;ini < s.length() && semiColons < 1;++ini) if(s.charAt(ini) == ';') semiColons++;
        for(fin = ini;s.charAt(fin) != ';';++fin);
        
        return s.substring(ini,fin);
    }
    
    public static String semiColonByPoint(String s){
        int i;
        for(i=0;i<s.length() && s.charAt(i) != ',';++i);
        
        return s.substring(0,i) + "." + s.substring(i+1,s.length());
        
    }
}