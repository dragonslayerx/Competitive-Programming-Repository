/**
 * Description: Find the diameter of the tree.
 * Usage: getDiameter O(V + E)
 * Source: https://github.com/dragonslayerx
 */

 #include <iostream>
 #include <cstdio>
 #include <cstring>
 #include <vector>
 using namespace std;

typedef vector< vector<pair<int,int> > > tree;
void dfs(tree &g, int u, int parent, int d, int dt[]){
    dt[u] = d;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        if (v != parent) {
            dfs(g, v, u, d + g[u][i].second, dt);
        }
    }
}

const int MAX = 100005;
int getDiameter(tree &g) {
	int dt[MAX] = {};
	dfs(g, 0, 0, 0, dt);
	int max_dist = 0, max_pos = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (max_dist < dt[i]) {
            max_dist = dt[i];
            max_pos = i;
        }
    }
	memset(dt, 0, sizeof(dt));
	dfs(g, max_pos, max_pos, 0, dt);
	max_dist = 0;
	for (int i = 0; i < n; i++) max_dist = max(max_dist, dt[i]);
	return max_dist;
}

int main() {
    int n, m;
    cin >> n >> m;
    tree T;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int w;
        cin >> w;
        T[a].push_back({b, w});
        T[b].push_back({a, w});
    }
    cout << getDiameter(T) << endl;
}
