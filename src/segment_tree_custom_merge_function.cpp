/**
 * Description: Segment Tree with custom merge function.
 * Usage: construct O(N), query O(lg(N)), update O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

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

    node(int sum, int maxs, int prefix, int suffix) {
        setNode(sum, maxs, prefix, suffix);
    }

    void setNode(int sum, int maxs, int prefix, int suffix){
        this->sum =sum;
        this->maxs=maxs;
        this->prefix=prefix;
        this->suffix=suffix;
    }
};

int a[MAX];
node st[4*MAX];

node merge(node left, node right){
    node t;
    t.prefix = max(left.prefix, left.sum+right.prefix);
    t.suffix = max(right.suffix, right.sum+left.suffix);
    t.sum = left.sum+right.sum;
    t.maxs = left.maxs;
    t.maxs = max(t.maxs, right.maxs);
    t.maxs = max(t.maxs, left.suffix+right.prefix);
    return t;
}

node construct(int n, int ll, int rl){
    if (ll == rl) {
        st[n].setNode(a[ll], a[ll], a[ll], a[ll]);
    } else {
        node left = construct(2*n+1, ll, (ll+rl)/2);
        node right = construct(2*n+2, (ll+rl)/2+1, rl);
        st[n] = merge(left, right);
    }
    return st[n];
}

node query(int n, int ll, int rl, int x, int y){
    int mid = (ll+rl)/2;
    if (x==ll &&  y==rl) return st[n];
    else if (y <= mid) return query(2*n+1, ll, mid, x, y);
    else if (x > mid) return query(2*n+2, mid+1, rl, x, y);
    else {
        node left = query(2*n+1, ll, (ll+rl)/2, x, mid);
        node right = query(2*n+2, (ll+rl)/2+1, rl, mid+1, y);
        return merge(left, right);
    }
}

node update(int n, int ll, int rl, int p, int val){
    if (p < ll || p > rl) return st[n];
    if (p == ll &&  p == rl) {
        st[n].setNode(val, val, val, val);
        return st[n];
    } else {
        int mid = (ll+rl)/2;
        node left = update(2*n+1, ll, (ll+rl)/2, p, val);
        node right = update(2*n+2, (ll+rl)/2+1, rl, p, val);
        st[n] = merge(left, right);
    }
    return st[n];
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a+i);
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
