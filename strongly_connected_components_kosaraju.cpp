/**
 * Description: Strictly Connected Component decomposition 
 * Usage: See below. O(V+E)
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef vector<vector<int> > graph;
class SCC {
    static const int MAX = 100005;

    void transpose(vector<vector<int> > &G, vector<vector<int> > &GT)
    {
        GT.resize(G.size());
        for (int i = 0; i < G.size(); i++) {
            for (int j = 0; j < G[i].size(); j++) {
                int v = G[i][j];
                GT[v].push_back(i);
            }
        }
    }

    public:
    //This fucntion can be used for toposort
    void decomposeSCC(graph &G, int u, bool isVisited[], vector<int> &sortedList)
    {
        isVisited[u] = true;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (isVisited[v] == false) {
                decomposeSCC(G, v, isVisited, sortedList);
            }
        }
        sortedList.push_back(u);
    }

    vector<vector<int> > decompose(graph &G)
    {
        vector<vector<int> > SCCList;
        bool isVisited[MAX] = {false};
        vector<int> sortedList;
        for (int i = 0; i < G.size(); i++) {
            if (!isVisited[i]) {
                decomposeSCC(G, i, isVisited, sortedList);
            }
        }
        reverse(sortedList.begin(), sortedList.end());
        vector<vector<int> > GT;
        transpose(G, GT);
        memset(isVisited, 0, sizeof(isVisited));
        for (int i = 0; i < sortedList.size(); i++) {
            int source = sortedList[i];
            if (!isVisited[source]) {
                vector<int> scc;
                decomposeSCC(GT, source, isVisited, scc);
                SCCList.push_back(scc);
            }
        }
        return SCCList;
    }
};

int main()
{
    SCC S;
    vector<vector<int> > G;
    int n, m;
    cin >> n >> m;
    G.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a].push_back(b);
    }
    vector<vector<int> > SCCList = S.decompose(G);
    for (int i = 0; i < SCCList.size(); i++) {
        for (int j = 0; j < SCCList[i].size(); j++) {
            cout << SCCList[i][j] << " ";
        }
        cout << endl;
    }
}
