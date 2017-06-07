/**
 * Description: Calculate the no of paths of paths of length L from u to v
 * Usage: pow O(N^3 log L)
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
using namespace std;

#define MAX 150
#define MOD 1000000007

void multiply(long long A[][MAX], long long B[][MAX], int n){
	long long C[MAX][MAX];
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[i][j] += (A[i][k] * B[k][j]) % MOD;
				C[i][j] %= MOD;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = C[i][j];
		}
	}
}

void pow(long long A[][MAX], long long B[][MAX], int n, int m){
	if (m == 1)return;
	pow(A, B, n, m/2);
	multiply(A, A, n);
	if (m & 1) multiply(A, B, n);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        long long d[MAX][MAX] = {}, W[MAX][MAX] = {};
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            W[a][b]++; W[b][a]++;
        }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i][j]=W[i][j];
		}
	}
        int q, L;
        scanf("%d%d", &q, &L);
        pow(d, W, n, L);
        while (q--) {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%lld\n", d[a][b]);
        }
    }
}

