/**
 * Description: Heavy Light Decomposition (Perform point updates and aggregate query over paths between two nodes in tree in case vertices are weighted)
 * Usage: update O(lg(N)), path_query O(lg^2(N)), See below for more details. 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

//----------Modifiable------
#define MAX 50050
//--------------------------
#define INVALID -1

bool isvisited[MAX];

int st_size[MAX]; // subtree_size
int p[MAX]; // parent of node
int lvl[MAX]; // level of node

vector<vector<int> > G;

int calc_size(int u, int level)
{
    isvisited[u] = 1;
    lvl[u] = level;

    st_size[u] = 1;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isvisited[v]) {
            p[v] = u;
            st_size[u] += calc_size(v, level+1);
        }
    }
    return st_size[u];
}

int node[MAX];
int chain_head[MAX], chain_link[MAX], chain[MAX];

//----------Modifiable------
int chain_id = 0, node_id = 1; // change this as per requiremnt bit donot support 0 base indexing
//--------------------------

int decompose(int u)
{
    isvisited[u] = 1;

    chain[u] = chain_id;
    node[u] = node_id++;
    if (chain_head[chain_id] == INVALID) {
        chain_head[chain_id] = u;
        chain_link[chain_id] = p[u];
    }

    int special_child = INVALID, max_subtree_size = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isvisited[v] && max_subtree_size < st_size[v]) {
            special_child = v;
            max_subtree_size = st_size[v];
        }
    }
    if (special_child != INVALID) decompose(special_child);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isvisited[v] && v != special_child) {
            chain_id++;
            decompose(v);
        }
    }
}

void hld_decompose(int root, int v)
{
    chain_id = 0, node_id = 1; // change this as per requiremnt bit donot support 0 base indexing
    memset(isvisited, 0, sizeof(isvisited));
    calc_size(root, 0);
    memset(isvisited, 0, sizeof(isvisited));
    for (int i = 0; i < v; i++) {
        chain_head[i] = INVALID;
        chain_link[i] = INVALID;
    }
    decompose(root);
}

int lca(int v1, int v2)
{
    int x = v1, y = v2;
    while (chain[x] != chain[y]){
        if (lvl[chain_head[chain[x]]] >= lvl[chain_head[chain[y]]])
            x = chain_link[chain[x]];
        else
            y = chain_link[chain[y]];
    }
    if (lvl[x] < lvl[y]) return x;
    else return y;
}

//---- BIT -----
long long _query(long long *bit, int indx){
    long long sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= indx & -indx;
    }
    return sum;
}

void update(long long *bit, int indx, long long val){
    while (indx < MAX) {
        bit[indx] += val;
        indx += indx & -indx;
    }
}

long long query(long long *bit, int x, int y){
    if (x > y) swap(x, y);
    return _query(bit, y) - _query(bit, x-1);
}
//--------------


//-----Modifiable---
long long path_query(long long *bit, int x, int y) // y is some ancestor of x in the actual tree
{
    long long aggregate = 0; // Set it as per the problem statement
    while (chain[x] != chain[y]){
        aggregate += query(bit, node[x], node[chain_head[chain[x]]]); // Set it as per the problem statement
        x = chain_link[chain[x]];
    }
    aggregate += query(bit, node[x], node[y]);
    return aggregate;
}

void node_update(long long *bit, int x, long long y) // pass the actual id of the nodes not the hashed ids
{
    update(bit, node[x], y);
}
//------------------


long long a[MAX], t[MAX], bit[MAX];

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++)
    {
        printf("Case %d:\n", t);
        int v;
        scanf("%d", &v);
        G.clear();
        G.resize(v);
        for (int i = 0; i < v; i++) {
            scanf("%lld", &a[i]);
        }
        memset(bit, 0, sizeof(bit));
        tree.process();
        for (int i = 1; i <= v-1; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }

        hld_decompose(0, v);

        for (int i = 0; i < v; i++) {
            update(bit, node[i], a[i]);
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int ch;
            scanf("%d", &ch);
            int x;
            scanf("%d", &x);
            if (!ch) {
                int y;
                scanf("%d", &y);
                long long sum = 0;
                int lca_xy = lca(x, y);
                sum += path_query(bit, x, lca_xy);
                sum += path_query(bit, y, lca_xy);
                sum -= a[lca_xy];
                printf("%lld\n", sum);
            } else {
                long long y;
                scanf("%lld", &y);
                node_update(bit, x, y - a[x]);
                a[x] = y;
            }
        }
    }
}