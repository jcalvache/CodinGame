/*******************************************

	@Author: Javier Calvache (jcalvache@rocketmail.com)
	
  The Goal
Casablanca’s hippodrome is organizing a new type of horse racing: duals. During a dual, only two horses will participate in the race. In order for the race to be interesting, it is necessary to try to select two horses with similar strength.

Write a program which, using a given number of strengths, identifies the two closest strengths and shows their difference with an integer (= 0).

*******************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int compare (const void * a, const void * b);


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; 
    cin.ignore();
    int horses[N];
    
    for (int i = 0; i < N; i++) {
        cin >> horses[i]; cin.ignore();
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    qsort(horses,N,sizeof(int),compare);

    
    int min = 1000, aux=0;/*
    for(int i=0; i<N-1; ++i){
        aux=horses[i+1]-horses[i];
        for(int j=i+1;j<N;j++){
            if(horses[j]-horses[i]>aux)break;
            else if(min == 0 || min>abs(horses[i]-horses[j])) min=abs(horses[i]-horses[j]);
        }
    }*/
        
    for(int i=0;i<N-1;++i) if(min>horses[i+1]-horses[i]) min=abs(horses[i+1]-horses[i]);
    
    
    cout << min << endl;
    
}

int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}