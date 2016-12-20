/**
 * Description: Edmonds Karp (Find maximum flow in a network) 
 * Source: https://github.com/dragonslayerx 
 */

class Max_Flow {
	#define MAX 500
	#define INF 1000000000
	private:
		vector<int> d, P;
		int construct_augmenting_path(vector<vector<int> > &G, int w[][MAX], int n, int src, int sink)
		{
			P.clear(); d.clear();
			d.resize(n); P.resize(n);
			vector<bool> isvisited(n);
			queue<pair<int,int> > Q;
			Q.push(make_pair(src, 0));
			isvisited[src] = 1;
			d[src] = 0;
			while (!Q.empty()) {
				pair<int, int> vertex = Q.front();
				Q.pop();
				int u = vertex.first;
				int dist = vertex.second;
				for (int i = 0; i < G[u].size(); i++) {
					int v = G[u][i];
					if (!isvisited[v] && w[u][v] > 0) {
						isvisited[v] = 1;
						Q.push(make_pair(v, dist + 1));
						d[v] = dist + 1;
						P[v] = u;
					}
				}
			}

			int d_sink = INT_MAX;
			int v = sink;
			while (v != src)  {
				d_sink = min(d_sink, w[P[v]][v]);
				v = P[v];
			}
			return d_sink;
		 }

	public:
		int flow;
		int f[MAX][MAX];
		Max_Flow()
		{
			flow = 0;
			for (int i = 0; i < MAX; i++)
				for (int j = 0; j < MAX; j++)
					f[i][j] = 0;
		}
		//G is a Flow-Network
		int ford_fulkerson(vector<vector<int> > &G, int c[][MAX], int v, int src, int sink)
		{
			int w[MAX][MAX];
			for (int i = 0; i < v; i++)
				for (int j = 0; j < v; j++)
					w[i][j] = c[i][j];

			int augment_flow;
			//construct_augmenting_path finds residual capacity
			while ((augment_flow = construct_augmenting_path(G, c, v, src, sink))) {
				 flow += augment_flow;
				 int v = sink;
				 while (v != src) {
				 	//Construct Residual Graph
					c[v][P[v]] += augment_flow;
					c[P[v]][v] -= augment_flow;
					//Augment Flow along the Augmenting Path
				 	if (w[P[v]][v] > 0)
						f[P[v]][v] += augment_flow;
					else
						f[v][P[v]] -= augment_flow;
					v = P[v];
				 }
			}
			return flow;
		}

};

int main()
{
	vector<vector<int > > G;
	int c[MAX][MAX] = {};
	int v, e;
	cin >> v >> e;
	G.resize(v);
	int src, sink;
	cin >> src >> sink;
	for (int i = 0; i < e; i++) {
		int x, y, capacity;
		scanf("%d%d%d", &x, &y, &capacity);
		
		G[x].push_back(y);
		G[y].push_back(x);
		c[x][y] = capacity;
		c[y][x] = 0;
		
	}
	Max_Flow F;
	cout << F.ford_fulkerson(G, c, v, src, sink) << endl;
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++)
			cout << F.f[i][j] << " ";
		cout << endl;
	}
}
