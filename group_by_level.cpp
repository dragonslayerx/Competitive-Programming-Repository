vector<int> nodes[MAX];
int groupByLevel(int u, int l){
    nodes[l].push_back(u);
    isvisited[u] = 1;
    int max_depth = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!isvisited[v]) {
            max_depth = max(max_depth, groupByLevel(v, l+1));
        }
    }
    return max_depth+1;
}