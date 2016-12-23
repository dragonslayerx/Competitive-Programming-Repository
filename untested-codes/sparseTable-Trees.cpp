template<class valueType, class MF>
class SparseTable {
private:
    int n, root;
    Tree &T;
    vector<valueType> &w;

    vector<int> parent, level;
    vector<vector<valueType> > ancestor, aggregate;

    static const int INVALID = -1;

    void processTree() {
        //perform a DFS
            vector<bool> isVisited(n);
            performDfs(root, INVALID, 0, isVisited);
        //Get Ancestors
            processAncestors();
        //Get Aggregate
            processAggregate();
    }

    void performDfs(int u, int p, int l, vector<bool> &isVisited) {
        isVisited[u] = true;
        parent[u] = p;
        level[u] = l;
        for (int i = 0; i < T[u].size(); i++) {
            int v = T[u][i];
            if (!isVisited[v]) {
                performDfs(v, u, l+1, isVisited);
            }
        }
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

    void getLog(int n){
        int i=0;
        while (n) {
            i++, n>>=1;
        }
        return i;
    }

public:
    MF mergeFunction;

    SparseTable(){
    }

    SparseTable(const Tree &T, const vector<valueType> &w, const int root) {
        init(T, w, root);
    }

    void init(const Tree &T, const vector<valueType> &w, int root) {
        this->T = T;
        this->w = w;
        this->root = root;
        this->n = T.size();

        int size = getLog(n) + 1;
        ancestor.resize(size, vector<valueType>(n));
        aggregate.resize(size, vector<valueType>(n));

        processTree();
    }


    valueType query(int x, int y) {
        if (level[x] <= level[y]) {
            swap(x, y);
        }
	//y should be an ancestor of x
        int currentNode = x, dif = level[x]-level[y];
        int i = 0;
        valueType v;
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
	valueType operator()(valueType left, valueType right) {
		return left+right;	
	}
}
