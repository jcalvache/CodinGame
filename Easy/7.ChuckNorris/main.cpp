/*********************************

  The Goal

Binary with 0 and 1 is good, but binary with only 0, or almost, is even better! Originally, this is a concept designed by Chuck Norris to send so called unary messages.

Write a program that takes an incoming message as input and displays as output the message encoded using Chuck Norris’ method.
  Rules

Here is the encoding principle:

    The input message consists of ASCII characters (7-bit)
    The encoded output message consists of blocks of 0
    A block is separated from another block by a space
    Two consecutive blocks are used to produce a series of same value bits (only 1 or 0 values):
    - First block: it is always 0 or 00. If it is 0, then the series contains 1, if not, it contains 0
    - Second block: the number of 0 in this block is the number of bits in the series

  Example

Let’s take a simple example with a message which consists of only one character: Capital C. C in binary is represented as 1000011, so with Chuck Norris’ technique this gives:

    0 0 (the first series consists of only a single 1)
    00 0000 (the second series consists of four 0)
    0 00 (the third consists of two 1)

So C is coded as: 0 0 00 0000 0 00

Second example, we want to encode the message CC (i.e. the 14 bits 10000111000011) :

    0 0 (one single 1)
    00 0000 (four 0)
    0 000 (three 1)
    00 0000 (four 0)
    0 00 (two 1)

So CC is coded as: 0 0 00 0000 0 000 00 0000 0 00

******************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string stringToBinary(string s);
string charToBinary(char c);
string reverseString(string s);
string chuckNorris(string s);


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout<<chuckNorris(stringToBinary(MESSAGE))<<endl;

}

string stringToBinary(string s){
    string binary = "";
    
    for(int i=0;i<s.length();++i){
        binary+=charToBinary(s[i]);
    }


    return binary;
}

string charToBinary(char c){
    int num = (int) c;
    string binary = "";
    
    for(int i=0;i<7;++i){
        binary += (c%2)+48;
        c /=2;
    }
    
    return reverseString(binary);
} 

string reverseString(string s){
    string aux = "";
    
    for(int i=s.length()-1;i>=0;--i) aux += s[i];
    
    return aux;
}

string chuckNorris(string s){
    string aux = "";
    
    if(s[0]=='0') aux+="00";
    else aux+='0';
    
    aux+=" 0";
    
    for(int i=1;i<s.length();++i){
        if(s[i]==s[i-1]) aux+='0';
        else{
            aux+=' ';
            if(s[i]=='0') aux+="00";
            else aux+="0";
            aux+=" 0";
        }
    }
    
    return aux;
}