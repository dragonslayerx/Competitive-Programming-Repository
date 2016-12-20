/**
 * Description: Dijkstra (Find shortest path from single source)
 * Usage: dijkstra O((V + E) lg(V)) 
 * Source: https://github.com/dragonslayerx 
 */

class Dijkstra {
        static const int MAX = 100050;
        static const int INF = 1e9;

        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        bool isvisited[MAX];

        public:

        void dijkstra(vector<vector<pair<int,int> > > &G, int v, int e, int s, int dist[])
        {
            for (int i = 0; i < v; i++) {
                dist[i] = INF;
                isvisited[i] = false;
            }
            dist[s] = 0;
            pq.push(make_pair(0, s));
            while (!pq.empty()){
                pair<int, int> tp = pq.top();
                pq.pop();
                int node = tp.second;
                int d = tp.first;
                if (isvisited[node]) continue;
                else {
                    isvisited[node] = true;
                    for (int i = 0; i < G[node].size(); i++) {
                        int v = G[node][i].first;
                        int w = G[node][i].second;
                        if (dist[v] > d + w) {
                            dist[v] = d + w;
                            pq.push(make_pair(dist[v], v));
                        } 
                    }
                }
            }
        }
};
