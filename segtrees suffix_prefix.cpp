#include <iostream>
#include <cstdio>
using namespace std;

#define MAX 50100
#define INF -1000000000

struct node {
    int sum;
    int maxs, prefix, suffix;
    node(){
        sum = prefix = suffix = 0;
        maxs = INF;
    }
    node(int a, int b, int c, int d) {
        assign(a, b, c, d);
    }
    void assign(int a, int b, int c, int d)
    {
        sum = a, maxs = b, prefix = c, suffix = d;
    }
};

int a[MAX];
node st[4*MAX];

node merge(node left, node right)
{
    node t;
    t.prefix = max(left.prefix, left.sum+right.prefix);
    t.suffix = max(right.suffix, right.sum+left.suffix);
    t.sum = left.sum+right.sum;
    t.maxs = left.maxs;
    t.maxs = max(t.maxs, right.maxs);
    t.maxs = max(t.maxs, left.suffix+right.prefix);
    return t;
}

node construct(int n, int ll, int rl)
{
    if (ll == rl) {
        st[n].assign(a[ll], a[ll], a[ll], a[ll]);
    } else {
        node left = construct(2*n+1, ll, (ll+rl)/2);
        node right = construct(2*n+2, (ll+rl)/2+1, rl);
        st[n] = merge(left, right);
    }
    return st[n];
}

node query(int n, int ll, int rl, int x, int y)
{
    int mid = (ll+rl)/2;
    if (x == ll &&  y == rl) return st[n];
    else if (y <= mid) return query(2*n+1, ll, mid, x, y);
    else if (x > mid) return query(2*n+2, mid+1, rl, x, y);
    else {
        node left = query(2*n+1, ll, (ll+rl)/2, x, mid);
        node right = query(2*n+2, (ll+rl)/2+1, rl, mid+1, y);
        return merge(left, right);
    }
}

node update(int n, int ll, int rl, int x, int color)
{
    if (x < ll || x > rl) return st[n];
    if (x == ll &&  x == rl) {
        st[n].assign(//--Do everything Here--//);
        return st[n];
    } else {
        int mid = (ll+rl)/2;
        node left = update(2*n+1, ll, (ll+rl)/2, x, color);
        node right = update(2*n+2, (ll+rl)/2+1, rl, x, color);
        st[n] = merge(left, right);
    }
    return st[n];
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a+i);
    construct(0, 0, n-1);
    int q;
    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        printf("%d\n", query(0, 0, n-1, x, y).maxs);
    }
}
