/**
 * Description: All pair shortest paths (Returns a matrix A where A[i][j] is the M-length shortest path from vertex i to vertex j)
 * Usage: getShortestPath O(N^3 log M) : Pass adjacency matrix as A and B into the function
 * Source: https://github.com/dragonslayerx
 */

// Set the w(u, v) = INF if no edge exists between u and v.

const int MAX = 100;
const int INF = 1e9;

void multiply(int A[][MAX], int B[][MAX], int n) {
	int C[MAX][MAX];
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] =INF;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (A[i][k] != INF && B[k][j] != INF) {
					C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
				}
			}
	`	}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = C[i][j];
		}
	}
}

void getShotestPath(int A[][MAX], int B[][MAX], const int n, int m) {
	if (m == 1)return;
	getShotestPath(A, B, n, m/2);
	multiply(A, A, n);
	if (m & 1) multiply(A, B, n);
}
