/**
 * Description: Finds Kth shortest path from s to t.
 * Usage : getCost O((V + E) lg(V) * k)
 * Source: https://github.com/dragonslayerx
 */
const int INF = 1e9;
int getCost(vector< vector< pair<int,int> > > &G, int s, int t, int k) {
    int n = G.size();
    int dist[MAX], count[MAX];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        count[i] = 0;
    }
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > Q;
	Q.push(make_pair(0, s));
	while (!Q.empty() && (count[t] < k)) {
		pair<int,int> node = Q.top();
		int u = node.second;
		int w = node.first;
		Q.pop();
		if ((dist[u] == INF) or (w > dist[u])) { // remove equal paths
			count[u]++;
			dist[u] = w;
		}
		if (count[u] <= k) {
		    for (int i = 0;  i < G[u].size(); i++) {
			int v = G[u][i].first;
			int w = G[u][i].second;
			Q.push(make_pair(dist[u] + w, v));
		    }
		}
	}
    return dist[t];
}
