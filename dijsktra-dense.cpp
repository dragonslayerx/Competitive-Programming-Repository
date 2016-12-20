/**
 * Description: Dijkstra (Find shortest path from single source in dense graph)
 * Usage: dijkstra O(V^2) 
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 1005
const int INF = 1e9
	
void dijkstra(int v, int source, int path_estimate[], int W[][MAX]) {
	bool isvisited[MAX];
	for (int i = 0; i < v; i++) {
        		isvisited[i] = false;
		path_estimate[i] = INF;
	}

	path_estimate[source] = 0;
	for (int i = 0; i < v; i++) {
		int mindist = INF, vertex;
		for (int j = 0; j < v; j++) {
			if (!isvisited[j] && mindist > path_estimate[j]) {
				mindist = path_estimate[j];
				vertex = j;
			}
		}
		isvisited[vertex] = true;
		for (int i = 0; i < v; i++) {
			if (!isvisited[i]) {
	      			if (path_estimate[i] > path_estimate[vertex] + W[vertex][i]) {
	          			path_estimate[i] = path_estimate[vertex] + W[vertex][i];
	      			}
			}
		}
	}
}
