/************************************

	@Author: Javier Calvache (jcalvache@rocketmail.com)
	
Have you ever asked yourself how it might be possible to simulate this display on a good old terminal? We have: with ASCII art!
  Rules

ASCII art allows you to represent forms by using characters. To be precise, in our case, these forms are words. For example, the word "MANHATTAN" could be displayed as follows in ASCII art:
 
# #  #  ### # #  #  ### ###  #  ###
### # # # # # # # #  #   #  # # # #
### ### # # ### ###  #   #  ### # #
# # # # # # # # # #  #   #  # # # #
# # # # # # # # # #  #   #  # # # #
 

​Your mission is to write a program that can display a line of text in ASCII art.

******************************************/

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
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    
    string T;
    getline(cin, T);
    
    string ROW[H];
    for (int i = 0; i < H; i++) getline(cin, ROW[i]);

    string sol[H];
    for(int i=0;i<H;++i)sol[i]="";
    

    for(int i=0;i<T.length();++i){
        for(int j=0;j<H;++j){
            if(T[i]>='a' && T[i]<='z') T[i]=toupper(T[i]);
            
            if(T[i]>='A' && T[i]<='Z') sol[j]+=ROW[j].substr((T[i]-'A')*L,L);
            else sol[j]+=ROW[j].substr(('Z'-'A'+1)*4,L);
            
        }
    }

    for(int i=0;i<H;++i) cout<<sol[i]<<endl;


}