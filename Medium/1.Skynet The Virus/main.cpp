/*******************************************************************

@Author: Javier Calvache (jcalvache@rocketmail.com)

The Goal
Your virus has caused a backdoor to open on the Skynet network enabling you to send new instructions in real time.

You decide to take action by stopping Skynet from communicating on its own internal network.

Skynet's network is divided into several smaller networks, in each sub-network is a Skynet agent tasked with transferring information by moving from node to node along links and accessing gateways leading to other sub-networks.

Your mission is to reprogram the virus so it will sever links in such a way that the Skynet Agent is unable to access another sub-network thus preventing information concerning the presence of our virus to reach Skynet's central hub.
  Rules
For each test you are given:

    A map of the network.
    The position of the exit gateways.
    The starting position of the Skynet agent.

>>> Nodes can only be connected to up to a single gateway. <<<

Each game turn:

    First off, you sever one of the given links in the network.
    Then the Skynet agent moves from one Node to another accessible Node.

Skynet agent
	
Gateway
 
Victory Conditions
The Skynet agent cannot reach an exit gateway
 
Lose Conditions
The Skynet agent has reached a gateway

*****************************************************************/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

bool agentGatewayConnection(set<pair<int,int>> links, int node, set<int> exitGateways){   
    set<pair<int,int>>::iterator itLinks = links.begin();     
    set<int>::iterator itExits = exitGateways.begin();
    pair<int,int> link;
    bool found = false;
    while(itLinks!=links.end() && !found){
        link.first=itLinks->first;
        link.second=itLinks->second;        

        if(exitGateways.find(link.second)!=exitGateways.end() && link.first == node){
            cout<<link.first<<" "<<link.second<<endl;
            found=true;            
        }
        else if (exitGateways.find(link.first)!=exitGateways.end() && link.second == node){
            cout<<link.first<<" "<<link.second<<endl;
            found=true;            
        } 
        else itLinks++;
    }
    return found;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    
    
    set<pair<int,int>> links;    
    set<int> exitGateways;
    for (int i = 0; i < L; i++) {
        pair<int, int> p;
        cin >> p.first >> p.second; cin.ignore();
        links.insert(p);
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        exitGateways.insert(EI);
    }    

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();

        if(!agentGatewayConnection(links, SI, exitGateways)){   
            set<pair<int,int>>::iterator itLinks = links.begin();     
            set<int>::iterator itExits = exitGateways.begin();
            
            bool found = false;
            while(itLinks!=links.end() && !found){
                if(itLinks->first == *itExits || itLinks->second == *itExits){
                    cout<<itLinks->first<<" "<<itLinks->second<<endl;
                    found = true;
                }
                else itLinks++;
            }                       
        }
    }
}