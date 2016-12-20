/**
 * Description: Segment Tree Range query Range update.  
 * Usage: construct O(N), update O(lg(N)), query O(lg(N)) 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 100100

struct node {
    long long val, lazy;
    bool flag;
    node()
    {
        val = lazy = 0;
        flag = false;
    }
};

node st[4*MAX];

long long query(int n, int ll, int rl, int ql, int qr)
{
    if (st[n].flag) {
        st[n].val += (rl-ll+1)*st[n].lazy;
        if (ll != rl) {
            st[(n<<1)+1].flag = true;
            st[(n<<1)+1].lazy += st[n].lazy;
            st[(n<<1)+2].flag = true;
            st[(n<<1)+2].lazy += st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }

    if (qr < ll || ql > rl) return 0;
    if (ll >= ql && rl <= qr) return st[n].val;
    else {
        long long left = query((n<<1)+1, ll, ((ll+rl)>>1), ql, qr);
        long long right = query((n<<1)+2, ((ll+rl)>>1) + 1, rl, ql, qr);
        return left + right;
    }
}

node update(int n, int ll, int rl, int ql, int qr, long long val)
{
    //cout << n << " " << ll << " " << rl << " " << ql << " " << qr << endl;
    if (st[n].flag) {
        st[n].val += (rl-ll+1)*st[n].lazy;
        if (ll != rl) {
            st[(n<<1)+1].flag = true;
            st[(n<<1)+1].lazy += st[n].lazy;
            st[(n<<1)+2].flag = true;
            st[(n<<1)+2].lazy += st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }

    if (qr < ll || ql > rl) return st[n];
    if (ll >= ql && rl <= qr) {
        st[n].val += (rl-ll+1)*val;
        if (ll != rl) {
            st[(n<<1)+1].flag = true;
            st[(n<<1)+1].lazy += val;
            st[(n<<1)+2].flag = true;
            st[(n<<1)+2].lazy += val;
        }
    } else {
        node left = update((n<<1)+1, ll, ((ll+rl)>>1), ql, qr, val);
        node right = update((n<<1)+2, ((ll+rl)>>1) + 1, rl, ql, qr, val);
        st[n].val = left.val + right.val;
    }
    return st[n];
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++) {
        memset(st, 0, sizeof(st));
        printf("Case %d:\n", t);
        int n, q;
        scanf("%d%d", &n, &q);
        while (q--) {
            int ch;
            scanf("%d", &ch);
            int x, y;
            scanf("%d%d", &x, &y);
            if (ch)
                printf("%lld\n", query(0, 0, n-1, x, y));
            else {
                long long val;
                scanf("%lld", &val);
                update(0, 0, n-1, x, y, val);
            }
            /*for (int i = 0; i < 4*n; i++) {
                cout << "(" << st[i].mod0 << " " << st[i].mod1 << " " << st[i].mod2 << " " << st[i].flag << " " << st[i].lazy << "), ";
            }*/
        }
   }
}
