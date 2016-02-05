/*********************************

  Rules
Write a program that prints the temperature closest to 0 among input data. If two numbers are equally close to zero, positive integer has to be considered closest to zero (for instance, if the temperatures are -5 and 5, then display 5).

**********************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int stringToInt(string s);

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // the number of temperatures to analyse
    cin >> N; cin.ignore();
    string TEMPS; // the N temperatures expressed as integers ranging from -273 to 5526
    getline(cin, TEMPS);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    int overZero = 0, belowZero = 0, begin = 0, end = 0, temp; 

    while(end < TEMPS.length() + 1){
        if(TEMPS[end] == ' ' || end == TEMPS.length()){
            temp = stringToInt(TEMPS.substr(begin,end-begin));
            if(temp>0 && (overZero == 0 || temp < overZero))overZero = temp;
            else if (temp<0 && (belowZero == 0 || temp > belowZero))belowZero = temp;
            begin=end+1;
        }
        end++;
    }
    
    if(overZero == 0) cout << belowZero << endl;
    else if (belowZero == 0) cout << overZero << endl;
    else if(overZero <= abs(belowZero)) cout << overZero << endl;
    else cout << belowZero << endl;
}

int stringToInt(string s){
    int result = 0, i = 0, digit;
    bool negative = false;
    
    if(s[i] == '-'){
        negative = true;
        i++;
    }
    
    while(i < s.length()){
        result*=10;
        result += s[i] - '0';
        i++;
    }
    
    if (negative == true) result *= -1;
    
    return result;
}