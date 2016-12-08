#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<vector<int> > graph;

class DFS {
        int counter;
        vector<int> prestamp;
        vector<int> lowest_rechable;
        vector<int> isvisited;
        vector<int> parent;
    public:
        vector<int> points;
        vector<pair<int, int> > bridges;

        DFS(graph &G, int source)
        {
            int v = G.size();
            prestamp.resize(v);
            lowest_rechable.resize(v);
            isvisited.resize(v);
            parent.resize(v);
            parent[source] = source, counter = 0;

            dfs(G, source);
            //
                for (int i = 0; i < v; i++) {
                    bool flag = 0;
                    for (int j = 0; j < G[i].size(); j++)
                    if (lowest_rechable[G[i][j]] >= prestamp[i])
                        flag = 1;
                    int count = 0;
                    if (i == source) {
                        for (int i = 0; i < v; i++)
                        if (i != source && parent[i] == source)
                            count++;
                        if (count < 2)
                            flag = 0;
                    }
                    if (flag)
                        points.push_back(i);
                }
                for (int i = 0; i < v; i++) {
                    bool flag = 0;
                    for (int j = 0; j < G[i].size(); j++)
                        if (lowest_rechable[G[i][j]] > prestamp[i])
                            bridges.push_back(make_pair(i, G[i][j]));
                }
            //
        }
        int dfs(graph &G, int u)
        {
            prestamp[u] = counter;
            lowest_rechable[u] = counter;
            isvisited[u] = 1;
            counter++;
            for (int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                if (isvisited[v] == 0) {
                    parent[v] = u;
                    lowest_rechable[u] = min(lowest_rechable[u], dfs(G, v));
                } else if (isvisited[v] == 1 && v != parent[u])
                    lowest_rechable[u] = min(lowest_rechable[u], prestamp[v]);
            }
            counter++;
            isvisited[u] = 2;
            return lowest_rechable[u];
        }
};

int main()
{
    int v, e;
    cin >> v >> e;
    graph G(v);
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int source = 2;
    DFS D(G, source);
    for (int  i = 0; i < D.bridges.size(); i++)
        cout << D.bridges[i].first << " " << D.bridges[i].second << endl;
    for (int  i = 0; i < D.points.size(); i++)
        cout << D.points[i] << endl;

}
