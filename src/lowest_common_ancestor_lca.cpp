/**
 * Description: LCA (Finds the lowest common ancestor of two nodes in a tree)
 * Usage: LCA constructor O(Nlg(N)), query O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

template<typename value_type> class RMQ {
    vector<int> a;
    vector<vector<value_type> > rmq;

	int size;
    int log2(int x){
        int i = 0, n = 1;
        while (x >= n) {
            i++; n <<= 1;
        }
        i--;
        return i;
    }

public:
    RMQ() {}

    RMQ(vector<value_type> &a) : a(a) {
        size = log2(a.size()) + 1;
        rmq.resize(size, vector<value_type> (a.size()));
        construct(a);
    }

    void construct(vector<value_type> &array){
        for (int i = 0; i < array.size(); i++) rmq[0][i] = i;
        for (int k = 1; k < size; k++) {
            for (int i = 0; i < a.size(); i++) {
                int length = 1 << (k - 1);
                if (i + length >= a.size() || a.at(rmq[k - 1][i]) < a.at(rmq[k - 1][i + length])){
                    rmq[k][i] = rmq[k - 1][i];
                } else {
                    rmq[k][i] = rmq[k - 1][i + length];
                }
            }
        }
    }

    int query(int i, int j){
        int range = j - i + 1;
        int logr = log2(range);
        if (a[rmq[logr][i]] < a[rmq[logr][j - (1 << logr) + 1]])
            return rmq[logr][i];
        else
            return rmq[logr][j - (1 << logr) + 1];
    }
};

class LCA {
    typedef vector<vector<int> > tree;
    vector<int> E, H, L;
    RMQ<int> R;
    tree T;
    vector<bool> isvisited;

    void euler_tour(int node, int level){
        isvisited[node] = 1;
        E.push_back(node);
        L.push_back(level);
        for (vector<int>::iterator i = T[node].begin(); i != T[node].end(); i++) {
            if (!isvisited[*i]) {
                euler_tour(*i, level + 1);
                E.push_back(node);
                L.push_back(level);
            }
        }
    }

public:
    LCA(tree &T, int root): T(T){
        isvisited.resize(T.size());
        H.resize(T.size(), -1);
        euler_tour(root, 0);
        for (int i = 0; i < E.size(); i++) {
            if (H[E[i]] == -1)
                H[E[i]] = i;
        }
        R = RMQ<int>(L);
    }

    int lca(int a, int b){
        if (H[a] > H[b]) swap(a, b);
        int index = R.query(H[a], H[b]);
        return E[index];
    }
};
