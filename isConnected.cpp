/**
 * Description: BFS (Checks if graph is connected using BFS)
 * Usgae: isConnected O(V + E) 
 * Source: https://github.com/dragonslayerx 
 */

int isConnected(vector<vector<int> > &G, int u){
	bool isVisited[MAX] = {false};
	queue<int> Q;
	Q.push(u);
	while (Q.size()) {
		int u = Q.front();
		isVisited[u] = true;
		Q.pop();
		for (vector<int>::iterator V = G[u].begin(); V != G[u].end(); V++) {
			if (!isVisited[*V]) {
				Q.push(*V);
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
