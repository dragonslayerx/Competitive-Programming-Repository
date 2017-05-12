/**
 * Description: Find the diameter of the tree.
 * Usage: getDiameter O(V + E)
 * Source: https://github.com/dragonslayerx 
 */

typedef vector<vector<pair<int, int> > > tree;
void dfs(tree &g, int u, int d, bool isVisited[], int dt[]){
    isVisited[u] = 1;
    dt[u] = d;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        if (!isVisited[v]) {
            dfs(g, v, d + g[u][i].second, isVisited, dt);
        }
    }
}

const int MAX = 100005;
bool isVisited[MAX];
int dt[MAX];

int getDiameter(tree &g) {
	memset(dt, 0, sizeof(dt));
	memset(isVisited, 0, sizeof(isVisited));
	dfs(g, 0, 0, isVisited, dt);
	int max_dist = 0, max_pos = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (max_dist < dt[i]) {
            		max_dist = dt[i];
            		max_pos = i;
        	}
    	}
	memset(dt, 0, sizeof(dt));
    	memset(isVisited, 0, sizeof(isVisited));
	dfs(g, max_pos, 0, isVisited, dt);
	max_dist = 0;
    	for (int i = 0; i < n; i++) {
        	max_dist = max(max_dist, dt[i]);
    	}
	return max_dist;
}
