/**
 * Description: Constructs path between two nodes in a full binary tree.
 * Usage: constructPath O(lg(N))
 * Source: https://github.com/dragonslayerx 
 */

vector<ll> constructPath(ll u, ll v) {
    vector<ll> pathA, pathB;
    while (u >= 1) {
        pathA.push_back(u);
        u >>= 1;
    }
    while (v >= 1) {
        pathB.push_back(v);
        v >>= 1;
    }
    reverse(pathA.begin(), pathA.end());
    reverse(pathB.begin(), pathB.end());
    vector<ll> path;
    int i = 0;
    for (; i+1 < pathA.size() && i+1 < pathB.size(); i++) if (pathA[i+1] != pathB[i+1]) break;
    for (int j = pathA.size()-1; j >= i; j--) {
        path.push_back(pathA[j]);
    }
    for (int j = i+1; j < pathB.size(); j++) {
        path.push_back(pathB[j]);
    }
    return path;
}