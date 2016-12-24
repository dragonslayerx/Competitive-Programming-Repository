#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector< vector<int> > Tree;

template<class valueType, class MF>
class SparseTable {
private:
    int counter;

    int n, root;
    Tree &T;
    vector<valueType> &w;

    vector<int> parent, level;
    vector<int> prestamp, poststamp;
    vector<vector<valueType> > ancestor, aggregate;

    static const int INVALID = -1;

    bool isInSubtree(int u, int v) {
        return ((prestamp[u] <= prestamp[v]) && (poststamp[u] >= poststamp[v]));
    }

    void processTree() {
        //perform a DFS
            performDfs(root, INVALID, 0);
        //Get Ancestors
            processAncestors();
        //Get Aggregate
            processAggregate();
    }

    void performDfs(int u, int p, int l) {
        prestamp[u] = counter++;
        parent[u] = p;
        level[u] = l;
        for (int v : T[u]) {
            if (v != p) {
                performDfs(v, u, l+1);
            }
        }
        poststamp[u] = counter++;

    }

    void processAncestors() {
        for (int j = 0; j < n; j++) {
            ancestor[0][j] = parent[j];
        }
        for (int i = 1; i < ancestor.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (ancestor[i-1][j] != INVALID) {
                    ancestor[i][j] = ancestor[i-1][ancestor[i-1][j]];
                } else {
                    ancestor[i][j] = INVALID;
                }
            }
        }
    }

    void processAggregate() {
        for (int j = 0; j < n; j++) {
            aggregate[0][j] = w[j];
        }
        for (int i = 1; i < aggregate.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (ancestor[i-1][j] != INVALID) {
                    aggregate[i][j] =  mergeFunction(aggregate[i-1][j], aggregate[i-1][ancestor[i-1][j]]);
                } else {
                    aggregate[i][j] = INVALID;
                }
            }
        }
    }

    int getLog(int n){
        int i=0;
        while (n) {
            i++, n>>=1;
        }
        return i;
    }

public:
    MF mergeFunction;

    SparseTable(Tree &T, vector<valueType> &w, const int root) : T(T), w(w) {
        this->counter = 0;
        this->root = root;
        this->n = T.size();

        parent.resize(n);
        level.resize(n);
        prestamp.resize(n); poststamp.resize(n);

        int size = getLog(n)+5;
        ancestor.resize(size, vector<valueType>(n));
        aggregate.resize(size, vector<valueType>(n));

        processTree();
    }

    int getLCA(int u, int v) {
        if (isInSubtree(u, v)) return u;
        if (isInSubtree(v, u)) return v;
        int size = ancestor.size();
        for (int i = size-1; i >= 0; --i) {
            if (ancestor[i][u] == INVALID) continue;
            if (!isInSubtree(ancestor[i][u], v)) {
                u = ancestor[i][u];
            }
        }
        return ancestor[0][u];
    }

    valueType query(int x, int y) {
        if (level[x] <= level[y]) {
            swap(x, y);
        }
        //y should be an ancestor of x
        int currentNode = x, dif = level[x]-level[y]+1;
        int i = 0;
        valueType v = 0;
        while (dif) {
            if (dif & 1) {
                v = mergeFunction(v, aggregate[i][currentNode]);
                currentNode = ancestor[i][currentNode];
            }
            i++, dif>>=1;
        }
        return v;
    }

};

template <class valueType>
class MF {
    public:
	valueType operator()(valueType left, valueType right) {
		return left+right;
	}
};

int main() {
    int n;
    cin >> n;
    vector< vector<int> > T(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    SparseTable< int, MF<int> > S(T, w, 0);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int lcaUV = S.getLCA(u, v);
        int sumU = S.query(u, lcaUV);
        int sumV = S.query(v, lcaUV);
        cout << lcaUV << " " << sumU << " " << sumV << endl;
        cout << sumU + sumV - w[lcaUV] << endl;
    }
}
