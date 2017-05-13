/**
 * Description: Cycle Detection (Detects a cycle in a directed or undirected graph.)
 * Usage: O(V)
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 100005;

enum Color {
	gray, white, black
};

typedef vector< vector<int> > Graph;
bool detectCycle(Graph &G, bool isUndirected)
{
    Color isVisited[MAX] = {white};
    int parent[MAX];
    stack<int> S;
    for (int i = 0;  i < G.size(); i++) {
        if (isVisited[i] == black) continue;
        S.push(i);
        while (!S.empty()) {
            int u = S.top();
            S.pop();
            if (isVisited[u] == gray) {
                isVisited[u] = black;
            } else {
                S.push(u);
                isVisited[u] = gray;
                for (int i = 0; i < G[u].size(); i++) {
                    int v = G[u][i];
                    if (isVisited[v] == white) {
                        parent[v] = u;
                        S.push(v);
                    } else if (isVisited[v] == gray and (!isUndirected or v != parent[u])) {
                        return true;
                    }
                }
            }
        }
    }
}

int main() {
    int v, e;
    cin >> v >> e;
    Graph G(v);
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a].push_back(b);
    }
    cout << detectCycle(G, false) << endl;
}
