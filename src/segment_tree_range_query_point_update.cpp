/**
 * Description: Segment Tree Range query Point update.
 * Usage: construct O(N), update O(lg(N)), query O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

#define MAX 100005

long long a[MAX];

int st[4*MAX];

int construct (int node, int ll, int rl){
    if (ll == rl) st[node] = a[ll];
    else {
        int left = construct(2*node+1, ll, (ll+rl)/2);
        int right = construct(2*node+2, (ll+rl)/2 + 1, rl);
        st[node] = left + right;
    }
    return st[node];
}

int query(int node, int ll, int rl, int ql, int qr){
    if (ll >= ql && rl <= qr) return st[node];
    else if (rl < ql || ll > qr) return 0;
    int left = query(2*node+1, ll, (ll+rl)/2, ql, qr);
    int right = query(2*node+2, (ll+rl)/2 + 1, rl, ql, qr);
    return left + right;
}

int update(int node, int ll, int rl, int q, int val){
    if (rl < q || ll > q) return st[node];
    if (q == ll && q == rl) st[node] = val;
    else {
        int left = update(2*node+1, ll, (ll+rl)/2, q, val);
        int right = update(2*node+2, (ll+rl)/2 + 1, rl, q, val);
        st[node] = left + right;
    }
    return st[node];
}


int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t=1; t<=tc; t++ ) {
        printf("Case %d:\n", t);
        memset(a, 0, sizeof(a));
        int n, q;
        scanf("%d%d", &n, &q);
        for (int i = 0; i < n; i++)
            scanf("%lld", &a[i]);
        construct(0, 0, n-1);
        while (q--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--, y--;
            printf("%d\n", query(0, 0, n-1, x, y));
        }
    }
}
