/**
 * Description: Floyd Warshall (Find the all pair shortest path distances)
 * Usage: See below O(N^3) 
 * Source: https://github.com/dragonslayerx 
 */

for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != INF and dist[k][j] != INF) {
					if (dist[i][j] > dist[i][k] + dist[k][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	}
