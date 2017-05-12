/**
 * Description: Tree linearization (Find the aggregate queries over nodes of a subtree)
 * Usage: dfs O(N)
 * Source: https://github.com/dragonslayerx
 */

#define MAX 100500
bool isvisited[MAX];
int pos[MAX], child[MAX];
int size = 0;

vector<vector<int> > G;

int dfs(int u){
	isvisited[u] = 1;
	int count = 1;
	pos[u] = size++;
	for (vector<int>::iterator i = G[u].begin(); i != G[u].end(); i++) {
        if (!isvisited[*i]) {
            count += dfs(*i);
		}
	}
	child[pos[u]] = count;
	return count;
}
