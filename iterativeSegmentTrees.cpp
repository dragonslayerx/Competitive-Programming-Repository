/**
 * Description: Fast iterative segment tree. 
 * Usgae: build O(N), query O(lg(N)), modify O(lg(N))
 * Note: The code is taken from http://codeforces.com/blog/entry/18051
 * Source: https://github.com/dragonslayerx 
 */

int n,m,q;
int arr[600][600];
int a,b,t[50000];

void build(){
    for(int i = n - 1; i > 0 ; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int v){
    for(t[p += n] = v; p > 1 ; p>>=1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r){
    int ans = 0;
    for(l += n, r+=n; l < r; l >>= 1, r >>= 1)
        ans = max(ans, max( ((l&1) ? t[l++] : 0), ((r&1) ? t[--r] : 0)));
    return ans;
}
