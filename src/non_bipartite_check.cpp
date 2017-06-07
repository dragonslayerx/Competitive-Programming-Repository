/**
 * Description: Checks if a graph is non bipartite. Assigns color to each node in case it is.
 * Usage: dfs returns true if the graph in nonbipartite O(V + E)
 * Source: https://github.com/dragonslayerx
 */

#define MAX 100005
bool isVisited[MAX];
bool color[MAX];

long long countA, countB;

bool isNonBipartite(int u, bool colorU){
    color[u] = colorU;
    (color[u])? countA++: countB++;
    isVisited[u] = true;
    bool nonBipartite = false;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isVisited[v]) {
            nonBipartite |= dfs(v, !colorU);
        } else {
            if (color[v] == color[u]) {
                return true;
            }
        }
    }
    return nonBipartite;
}
