/**
 * Description: BFS (Checks if graph is connected using BFS)
 * Usgae: isConnected O(V + E)
 * Source: https://github.com/dragonslayerx
 */

int isConnected(vector<vector<int> > &G, int src){
	bool isVisited[MAX] = {false};
	queue<int> Q;
	Q.push(src);
	while (Q.size()) {
		int u = Q.front();
		Q.pop();
		isVisited[u] = true;
		for (int v : G[u]) {
			if (!isVisited[v]) {
				Q.push(v);
			}
		}
	}
	for (int i = 0; i < G.size(); i++) {
        	if (isVisited[i] == false) {
            		return false;
        	}
	}
	return true;
}
