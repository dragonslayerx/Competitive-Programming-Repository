/**
 * Description : Bridges (Find bridges in a graph) 
 * Usage: See below O(V) 
 * Source: https://github.com/dragonslayerx 
 */

#include<iostream>
#include<vector>
#include<cstdio>
#include <cstring>
#include<list>
#include<set>
using namespace std;

#define INVALID_NUMBER -1
#define INVALID_EDGE -1

typedef vector<list<pair<int,int> > > graph;


vector<int> bridges;
vector<int> low;
vector<int> dfsNumbers;
graph G;

void calculateBridges(int currentNode, int &time, int parentEdge=INVALID_EDGE) {
    if(dfsNumbers[currentNode]==INVALID_NUMBER)
	{
	    dfsNumbers[currentNode]=low[currentNode]=(++time);
		for(list<pair<int,int> >::const_iterator i=G[currentNode].begin();i!=G[currentNode].end();i++)
		{
		    int currentEdge=i->second;
			if(currentEdge!=parentEdge){
				int destination = i->first;
				calculateBridges(destination, time, currentEdge);
				if(low[destination]>dfsNumbers[currentNode]) {
					bridges.push_back(currentEdge);
				}
				low[currentNode]=min(low[currentNode],low[destination]);
			}
		}
	}
}


bool isVisited[100005];
int dfs(vector<vector<int> > &G, int u){
    isVisited[u] = 1;
    int members = 1;
    for (int i = 0; i < G[u].size(); i++) {
        if (!isVisited[G[u][i]]) {
            members += dfs(G, G[u][i]);
        }
    }
    return members;
}

int main(){
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;

    	low.resize(n);
    	dfsNumbers.resize(n,INVALID_NUMBER);

    	vector<pair<int,int> > edges;
    	vector<vector<int> > Td(n);

	G.resize(n);
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		a--, b--;
		edges.push_back(make_pair(a, b));

		G[a].push_back(make_pair(b,i));
		G[b].push_back(make_pair(a,i));
	}

     	bridges.reserve(m);
	int initialTime = 0;
	for(int i=0;i<n;i++) {
		calculateBridges(i, initialTime);
	}
	for (int i : bridges) {
		cout << edges[i].first << " " << edges[i].second << endl;	
	}
}
