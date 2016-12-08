ll stSize[200005];
int lvl[200005];
int calcSize(vector<vector<int> > &T, int u, int parent, int level){
    stSize[u] = 1;
    lvl[u]=level;
    for (int i = 0; i < T[u].size(); i++) {
        int v = T[u][i];
        if (v != parent) {
            stSize[u] += calcSize(T, v, u, level+1);
        }
    }
    return stSize[u];
}