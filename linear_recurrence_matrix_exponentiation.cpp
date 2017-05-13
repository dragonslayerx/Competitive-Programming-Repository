/**
 * Description: Matrix Exponentiation (Finds the Kth element of a linear recurrence using matrix exponentiation)
 * Usage: solve O(N^3 lg (K))
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

template <typename T, size_t N>
void multiply(T A[N][N], T B[N][N]) {
    T C[N][N]={};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N ;k++) {
                C[i][j] += (A[i][k]*B[k][j]) % MOD;
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = C[i][j];
        }
    }
}

template <typename T, size_t N>
void power(T A[N][N], T base[N][N], long long k) {
    if (k == 0) return; // assumes A is I initially
    else {
        power(A, base, k>>1);
        multiply<T, N>(A, A);
        if (k & 1) {
            multiply<T, N>(A, base);
        }
    }
}

template<typename T, size_t N>
void solve(T transition[N][N], T cur[N], ll k, T next[N]) {
    T r[N][N]={};
    for (int i = 0; i < N; i++) r[i][i]=1; // r is I

    power<T, N>(r, transition, k);

    for (int i = 0; i < N; i++) {
        next[i]=0;
        for (int j = 0; j < N; j++) {
            next[i] += (r[i][j]*cur[j]) % MOD;
            if (next[i] >= MOD) next[i] -= MOD;
        }
    }
}

int main() {
    long long A[2][2] = {{1, 1}, {1, 0}};
    long long cur[2] = {1, 0}, next[2];
    int k;
    cin >> k;
    solve(A, cur, k, next);
    cout << next[0] << endl;
}

