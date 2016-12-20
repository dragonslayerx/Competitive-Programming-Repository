/**
 * Description: Topological sorting
 * Usage: See below O(V + E)
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 10050;

bool isvisited[MAX];
vector<int> s;
vector<vector<int> > g;

void dfs(int u)
{
    isvisited[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!isvisited[v]) {
            dfs(v);
        }
    }
    s.push_back(u);
}

int main()
{
    int n, m;
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
        if (!isvisited[i]) dfs(i);
    }
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); i++) {
        cout << s[i]+1 << " ";
    }
    cout << endl;
}
