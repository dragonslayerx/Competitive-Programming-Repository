/**
 * Descrption: BellmanFord (Finds the shortest path from source s to all vertices v. Detects a negative weight cycle if present.)
 * Usage: See below O(V E)
 * Source: https://github.com/dragonslayerx
 */

struct edges {
    int u;
    int v;
    long long w;
    edges(int u, int v, long long w): u(u), v(v), w(w) {}
};

int main(){
	int n, m;
	scanf("%d %d", &n, &m);

	vector<edges> edge;

	for (int i = 0; i < m; i++) {
		int a, b;
		long long w;
		scanf("%d%d%lld", &a, &b, &w);
		edge.push_back(edges(a, b, w));
	}

	int parent[MAX];
	long long dist[MAX];
	for (int i = 0; i < n; i++) {
		parent[i] = 0;
		dist[i] = INF;
	}
	
	dist[0] = 0;
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < edge.size(); j++) {
			int u = edge[j].u;
			int v = edge[j].v;
			long long w = edge[j].w;
			if (dist[u] != INF) {
				if (dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					parent[v] = u;
				}
			}
		}
	}

	bool negCycleExists = false;
	for (int j = 0; j < edge.size(); j++) {
		int u = edge[j].u;
		int v = edge[j].v;
		long long w = edge[j].w;
		if (dist[v] > (dist[u] + w)) {
			negCycleExists = true;
			break;
		}
	}
	
	for (int i = 0; i < n; i++) {
		cout << i << " " << dist[i] << endl;
	}
}
