#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 1000000000+7;
const int INF = 1000000000+5;

/**
 * Description: BIT RURQ (Support range queries and range updates of 1-D array)
 * Usage: query O(lg(N)), update O(lg(N))
 * Source: https://github.com/dragonslayerx
 * Note: Use 1-based indexing
 */

// Remember to use 1 based indexing
class BIT {
    static const int MAX = 100005;
    public:
    static long long query(long long *bit, int indx)
    {
        long long sum = 0;
        while (indx) {
            sum += bit[indx];
            indx -= (indx & -indx);
        }
        return sum;
    }

    static void update(long long *bit, int indx, long long x)
    {
        while (indx < MAX) {
            bit[indx] += x;
            indx += (indx & -indx);
        }
    }
};

class BitRPRQ {
    static const int MAX = 100005;
    long long B1[MAX];
    long long B2[MAX];

    public:
    BitRPRQ() {
    	memset(B1, 0, sizeof(B1));
        memset(B2, 0, sizeof(B2));
    }

    long long Rquery(int p){
        long long tempB1 = BIT::query(B1, p);
        long long tempB2 = BIT::query(B2, p);
        long long sum = tempB1 * p + tempB2;
        return sum;
    }

    long long Rupdate(int l, int r, long long v){
        BIT::update(B1, l, v);
        BIT::update(B1, r+1, -v);
        BIT::update(B2, l, -((l-1)*v));
        BIT::update(B2, r+1, r*v);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, q;
        scanf("%d%d", &n, &q);
        BitRPRQ B;
        while (q--) {
            int choice;
            scanf("%d", &choice);
            int p, q;
            long long v;
            scanf("%d%d", &p, &q);
            if (choice==0) {
                long long v;
                scanf("%lld", &v);
                B.Rupdate(p, q, v);
            } else {
                long long Answer = B.Rquery(q)-B.Rquery(p-1);
                printf("%lld\n", Answer);
            }
        }
    }
}
