/**
 * Description: Preorder and Postorder stamps (Finds the preorder and postorder stamps for vertices of tree. Useful for checking if vertex is in subtree) 
 * Usage: preprocess O(V) 
 * Source: https://github.com/dragonslayerx 
 */


int prestamp[MAX], poststamp[MAX];

int counter = 0;
void preprocess(int u, int p) {
    prestamp[u] = counter++;
    for (int v : T[u]) {
        if (v != p) {
            preprocess(v, p);
        }
    }
    poststamp[u] = counter++;
}

bool isInSubtree(int u, int v) {
    return ((prestamp[u] <= prestamp[v]) && (poststamp[u] >= poststamp[v]));
}
