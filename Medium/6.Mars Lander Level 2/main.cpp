/******************************************************************************

@Author: Javier Calvache (jcalvache@rocketmail.com)

 The Goal
The goal for your program is to safely land the "Mars Lander" shuttle, the landing ship which contains the Opportunity rover. Mars Lander is guided by a program, and right now the failure rate for landing on the NASA simulator is unacceptable.

This puzzle is the second level of the "Mars Lander" trilogy. The controls are the same as the previous level but you must now control the angle in order to succeed.
  Rules

Built as a game, the simulator puts Mars Lander on a limited zone of Mars sky.
The zone is 7000m wide and 3000m high.

There is a unique area of flat ground on the surface of Mars, which is at least 1000 meters wide.
Every second, depending on the current flight parameters (location, speed, fuel ...), the program must provide the new desired tilt angle and thrust power of Mars Lander:
Angle goes from -90° to 90° . Thrust power goes from 0 to 4 .
 
The game simulates a free fall without atmosphere. Gravity on Mars is 3.711 m/s² . For a thrust power of X, a push force equivalent to X m/s² is generated and X liters of fuel are consumed. As such, a thrust power of 4 in an almost vertical position is needed to compensate for the gravity on Mars.

For a landing to be successful, the ship must:

    land on flat ground
    land in a vertical position (tilt angle = 0°)
    vertical speed must be limited ( = 40m/s in absolute value)
    horizontal speed must be limited ( = 20m/s in absolute value)

  Note
Tests and validators are only slightly different. A program that passes a given test will pass the corresponding validator without any problem.
  Game Input
The program must first read the initialization data from standard input. Then, within an infinite loop, the program must read the data from the standard input related to Mars Lander's current state and provide to the standard output the instructions to move Mars Lander.
Initialization input
Line 1: the number surfaceN of points used to draw the surface of Mars.
Next surfaceN lines: a couple of integers landX landY providing the coordinates of a ground point. By linking all the points together in a sequential fashion, you form the surface of Mars which is composed of several segments. For the first point, landX = 0 and for the last point, landX = 6999
Input for one game turn
A single line with 7 integers: X Y hSpeed vSpeed fuel rotate power

    X,Y are the coordinates of Mars Lander (in meters).
    hSpeed and vSpeed are the horizontal and vertical speed of Mars Lander (in m/s). These can be negative depending on the direction of Mars Lander.
    fuel is the remaining quantity of fuel in liters. When there is no more fuel, the power of thrusters falls to zero.
    rotate is the angle of rotation of Mars Lander expressed in degrees.
    power is the thrust power of the landing ship.

Output for one game turn
A single line with 2 integers: rotate power :

    rotate is the desired rotation angle for Mars Lander. Please note that for each turn the actual value of the angle is limited to the value of the previous turn +/- 15°.
    power is the desired thrust power. 0 = off. 4 = maximum power. Please note that for each turn the value of the actual power is limited to the value of the previous turn +/- 1.

Constraints
2 = surfaceN < 30
0 = X < 7000
0 = Y < 3000
-500 < hSpeed, vSpeed < 500
0 = fuel = 2000
-90 = rotate = 90
0 = power = 4
Response time per turn = 100ms


*********************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



struct Starship{
    int X;
    int Y;
    int hSpeed; // the horizontal speed (in m/s), can be negative.
    int vSpeed; // the vertical speed (in m/s), can be negative.
    int fuel; // the quantity of remaining fuel in liters.
    int rotate; // the rotation angle in degrees (-90 to 90).
    int power; // the thrust power (0 to 4).
    
    const int approachAngle = 10, constAngle = 22, normalAngle = 45, maxAngle = 75;
    const int maxVSpeed = 70, maxHSpeed = 80, minVSpeed = -35, minHSpeed = 20;
    
    int medP=0, changeP=0;
};

struct Terrain{
    int surfaceN; // the number of points used to draw the surface of Mars.
    pair<int,int> *land; //x,y surface coordinates
    pair<int,int> p; //X-axis points where the landing site begins and finishes.
    int medX=0; //X-axis midpoint between where the starship begins and the landing point
    int landingHeight; //Landing point's height
    const int wide = 7000, height = 3000;
};

//This method finds the first and last point (X-axis) of the landing site.
pair<int,int> flatGround(const pair<int,int> *land, int length){
    pair<int,int> p;
    bool firstP = false, secondP = false;
    
    for(int i=0;i<length-1 && !secondP;++i){
        if(land[i].second == land[i+1].second && !firstP){
            p.first = land[i].first;
            firstP = true;
        }
        else if(land[i].second != land[i+1].second && firstP){
            p.second = land[i].first;
            secondP = true;
        }
    }    
    return p;
}

//This method returns the height (Y-axis) of the landing place
int landingPointHeight(const Terrain &t){
    int i;
    for(i=0;i<t.surfaceN && t.land[i].first<t.p.first;++i);
    return t.land[i].second;
}

//This method returns true if there is an obstacle between the starship and the landing point
bool obstacle(const Starship &s, const Terrain &t){    
    pair<int,int> p = flatGround(t.land, t.surfaceN);
    int inc = (int)t.wide/t.surfaceN;//The zone is 7000m wide
    int x1 = s.X, y1 = s.Y;//The actual position of the starship
    int x2 = (p.first+p.second)/2, y2 = t.land[x2/inc].second; //Landing point
    int ini = x1/inc;
    int fin = x2/inc;
    bool obstacle = false;
  
    for(int i=x1/inc;i<x2/inc && !obstacle;++i){
        if(t.land[i].second>(((y2-y1)*((i*inc)-x1))/(x2-x1))+y1) obstacle=true;
    }
    
    return obstacle;
}

//Simple method, it goes in straight line to the landing point. Not valid for deep canyon or high ground.
pair<int,int> approach2(Starship &s, pair<int,int> p){
    if(s.changeP==0) s.changeP=(((p.first+p.second)/2)+s.X)/2;
    pair<int,int> res;  

    if(s.vSpeed<s.minVSpeed)res.second=4;
    else res.second=3;
    
    //Left  
    if(s.X<p.first){
        //Break if needed
        if(abs(s.hSpeed)>s.minHSpeed){
            res.first=s.normalAngle;
            res.second=4;
        }
        else res.first=-s.constAngle;
    }
    //Right
    else if(s.X>p.second){
        //Break if needed
        if(abs(s.hSpeed)>s.minHSpeed){
            res.first=-s.normalAngle;
            res.second=4;
        }
        else res.first=s.constAngle;
    }
    //Over the landing site
    else{
        //Brake if needed
        if(abs(s.hSpeed)>s.minHSpeed){
            if(s.hSpeed<0)  res.first=-s.normalAngle;
            else res.first=s.normalAngle;
            res.second=4;
        }
    }    
    
    return res;
}

//This method pilots the starship above the landing point and then it descends.
pair<int,int> softApproach(Starship &s, const Terrain &t){
    if(s.changeP==0) s.changeP=(((t.p.first+t.p.second)/2)+s.X)/2;
    pair<int,int> res;  

    if(s.vSpeed<s.minVSpeed)res.second=4;
    else res.second=3;
    
    //Left  
    if(s.X<t.p.first){
        //Break if needed
        if(abs(s.hSpeed)>s.minHSpeed) {
            res.first=s.constAngle;
            res.second=4;
        }
        else res.first=-s.constAngle;
    }
    //Right
    else if(s.X>t.p.second){
        //Break if needed
        if(abs(s.hSpeed)>s.minHSpeed){
            res.first=-s.constAngle;
            res.second=4;
        }
        //Climb if starship is below landing point
        else if(s.Y<t.landingHeight){
            res.first=0;
            if((s.vSpeed/2)<s.minVSpeed)res.second=3;            
            else res.second=4;
        }
        else res.first=s.constAngle;
    }
    //Over the landing site
    else{
        //Brake if needed
        if(abs(s.hSpeed)>s.minHSpeed){
            if(s.hSpeed<0)  res.first=-s.normalAngle;
            else res.first=s.normalAngle;
            res.second=4;
        }
        if(s.vSpeed>0) res.second--;
    }    
    
    return res;
}
        

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    Starship s;
    Terrain t;
    bool stabilized = false;
    cin >> t.surfaceN; cin.ignore();
    t.land = new pair<int,int>[t.surfaceN];
    for (int i = 0; i < t.surfaceN; i++) {        
        cin >> t.p.first >> t.p.second; cin.ignore();
        t.land[i]=t.p;
    }
    
    t.p = flatGround(t.land, t.surfaceN);
    
    int medX=0;    

    // game loop
    while (1) {
        cin >> s.X >> s.Y >> s.hSpeed >> s.vSpeed >> s.fuel >> s.rotate >> s.power; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;     
    
        //Calculate midpoint of landing site 
        if(t.medX==0) t.medX=(((t.p.first+t.p.second)/2)+s.X)/2;
        t.landingHeight = landingPointHeight(t);
        int x, y;   

        
        pair<int,int> res;
        if(obstacle(s, t) || (landingPointHeight(t)>(t.height/2))) res=softApproach(s,t);
        else res=approach2(s,t.p);
        cout<<res.first<<" "<<res.second<<endl;
    }
    delete t.land;
}