/*******************************************************************

@Author: Javier Calvache (jcalvache@rocketmail.com)

The Goal
You mission is to print a specific line of the Conway sequence.
  Rules

Warning! This sequence can make you ill. The reasoning is simple but unusual: Read a line aloud whilst looking at the line above and you will notice that each line (except the first) makes ??an inventory of the previous line.

1
1 1
2 1
1 2 1 1
1 1 1 2 2 1
3 1 2 2 1 1
...

- Line 3 shows 2 1 because the line 2 contains two 1, one after the other.
- Line 4 displays 1 2 1 1 because the line 3 contains one 2 followed by one 1.
- Line 5 displays 1 1 1 2 2 1 because the line 4 contains one 1 followed by one 2 followed by two 1.

This sequence refers to a technique used to encode ranges in order to compress identical values ??without losing any information. This type of method is used, amongst others, to compress images.

Your mission is to write a program that will display the line L of this series on the basis of an original number R (R equals 1 in our example).

**********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    vector<int> v[L];
    vector<int>::iterator it;
    int value, times=0;
    
    v[0].push_back(R);

    
    for(int i=1;i<L;++i){
        it = v[i-1].begin();
        value = *it;
        while(it != v[i-1].end()){
            if(*it == value) times++;
            else{
                v[i].push_back(times);
                times = 1;
                v[i].push_back(value);
                value = *it;
            }
            it++;
            if(it == v[i-1].end()){
                v[i].push_back(times);
                times = 0;
                v[i].push_back(value);
            }
        }
    }
    
    
    for(int i=0;i<L;++i){
        it = v[i].begin();
        while(it != v[i].end()){            
            it++;
        }       
    }
    
    
    
    it = v[L-1].begin();
    
    while(it != v[L-1].end()){
        cout << *it;
        it++;
        if(it != v[L-1].end()) cout << " ";
    }

}