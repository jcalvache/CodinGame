/****************************************************

  The Goal
A finance company is carrying out a study on the worst stock investments and would like to acquire a program to do so. The program must be able to analyze a chronological series of stock values in order to show the largest loss that it is possible to make by buying a share at a given time t0 and by selling it at a later date t1. The loss will be expressed as the difference in value between t0 and t1. If there is no loss, the loss will be worth 0.

*****************************************************/

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
    int n;
    cin >> n; cin.ignore();
    string vs;
    getline(cin, vs);
    
    
    int v[n], ini=0, end=0, i=0;
    while(end<vs.length()){
        if(vs[end] == ' '){
            v[i] = stringToInt(vs.substr(ini,end-ini));
            ini=end+1;
            i++;
        }
        end++;
        if(end==vs.length()){
            v[i] = stringToInt(vs.substr(ini,end-ini));
        }
    }


    int min=0, max=0;
    
    for(int i=1;i<n;++i) if(v[i]<v[min]) min=i;

    if(min>0){
        for(int i=1;i<min;++i) if(v[i]>v[max]) max=i;
        
        cout << v[min]-v[max] << endl;
    }
    
    else cout << "0" << endl;
    
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