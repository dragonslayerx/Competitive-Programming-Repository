/**
 * Description : Connected Components (Find the connected components in graph) 
 * Usage: dfs O(V) 
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 100005;

bool isVisited[MAX];
vector<vector<int> > G;
vector<int> col;
vector<int> components[MAX];

int dfs(int u, int color){
    isvisited[u] = 1;
    col[u] = color;
    components[color].push_back(u);
    int members = 1;
    for (int i = 0; i < G[u].size(); i++) {
        if (!isvisited[G[u][i]]) {
            members += dfs(G[u][i], color);
        }
    }
    return members;
}

memset(isVisited, 0, sizeof(isVisited));
int size=0;
for (int i = 0; i < n; i++) {
    if (!isVisited[i]) {
        dfs(i, size);
        size++;
    }
}
