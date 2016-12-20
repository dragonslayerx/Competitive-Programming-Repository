/**
 * Description: Karatsuba Algorithm (Fast polynomial multiplication)
 * Usage: multiply O(N^1.583)
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
using namespace std;

#define MOD 99991

//m should be a power of 2
class Karatsuba {
    public:

    static void multiply(int *A, int *B, int *C, int lA, int rA, int lB, int rB){
        int m = rA-lA+1;
        if (m == 1) {
            C[0] = ((long long)A[lA]*B[lB]) % MOD;
            return;
        }

        int z0[m], z1[m], z2[m];

        int midA = (lA + rA) >> 1;
        int midB = (lB + rB) >> 1;

        multiply(A, B, z0, lA, midA, lB, midB);
        multiply(A, B, z1, midA+1, rA, midB+1, rB);

        int a[m], b[m];
        int shift = m>>1;
        int mid = m>>1;
        for (int i = lA, j = 0; i <= midA; i++, j++) {
            a[j] = A[i] + A[i+shift];
            if (a[j] >= MOD) a[j] -= MOD;
        }
        for (int i = lB, j = 0; i <= midB; i++, j++) {
            b[j] = B[i] + B[i+shift];
            if (b[j] >= MOD) b[j] -= MOD;
        }
        multiply(a, b, z2, 0, mid-1, 0, mid-1);

        for (int i = 0; i <= m-2; i++) {
            C[i] = z0[i];
            if (C[i] >= MOD) C[i] -= MOD;
        }
        C[m-1] = 0;

        shift = m;
        for (int i = 0; i <= m-2; i++) {
            C[i+shift] = z1[i];
            if (C[i+shift] >= MOD) C[i+shift] -= MOD;
        }

        shift = m>>1;
        for (int i = 0; i <= m-2; i++) {
            C[i+shift] += (z2[i] + (MOD-z1[i]) + (MOD-z0[i])) % MOD;
            if (C[i+shift] >= MOD) {
                C[i+shift] -= MOD;
            }
        }
    }
};

int main()
{
    int A[] = {1, 1, 1, 1};
    int B[] = {1, 1, 0, 0};
    int C[7] = {};
    Karatsuba::multiply(A, B, C, 0, 3, 0, 3);
    for (int i = 0; i < 7; i++) {
            cerr << C[i] << endl;;
    }
}
