/**
 * Description: All pair shortest paths (Returns a matrix A where A[i][j] is the M-length shortest path from vertex i to vertex j)
 * Usage: getShortestPath O(N^3 log M)
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
using namespace std;

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
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = C[i][j];
		}
	}
}

void getShortestPath(int A[][MAX], int B[][MAX], const int n, int m) {
	if (m == 1)return;
	getShortestPath(A, B, n, m/2);
	multiply(A, A, n);
	if (m & 1) multiply(A, B, n);
}

int main() {
    int N;
    scanf("%d", &N);
    int Adj[MAX][MAX];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Adj[i][j]=INF;
        }
        Adj[i][i] = 0;
    }
    int countEdges;
    scanf("%d", &countEdges);
    for (int i = 0; i < countEdges; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        Adj[u][v] = Adj[v][u] = w;
    }

    int Dist[MAX][MAX];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Dist[i][j]=Adj[i][j];
        }
    }
    getShortestPath(Dist, Adj, N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%5d", Dist[i][j]);
        }
        printf("\n");
    }
}
