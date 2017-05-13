/**
 * Description: Preorder and Postorder stamps (Finds the preorder and postorder stamps for vertices of tree. Useful for checking if vertex is in subtree)
 * Usage: preprocess O(V)
 * Source: https://github.com/dragonslayerx
 */
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100005;

vector< vector<int> > T;

int prestamp[MAX], poststamp[MAX];
int counter = 0;
void preprocess(int u, int p) {
    prestamp[u] = counter++;
    for (int v : T[u]) {
        if (v != p) {
            preprocess(v, u);
        }
    }
    poststamp[u] = counter++;
}

bool isInSubtree(int u, int v) {
    return ((prestamp[u] <= prestamp[v]) && (poststamp[u] >= poststamp[v]));
}

int main() {
    int n;
    cin >> n;
    T.resize(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    int root;
    cin >> root;
    preprocess(root, root);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        // Check if v is in subtree of u
        cout << isInSubtree(u, v) << endl;
    }
}
