/**
 * Description : DisjointSet (Makes a set of sets, merge sets, set membership, no. of sets, undo last operation)
 * Usage: find O(lg(N)), merge O(lg(N)), undo O(1), getComponents O(1)
 * Source: https://github.com/dragonslayerx 
 */

class DisjointSet {
    const static int MAX = 100005;
 
    int parent[MAX], rank[MAX];
    int components;
    vector<int> O;
public:
    DisjointSet(int n) {
        components=n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i]=1;
        }
    }
 
    int find(int u) {
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    }
 
    void merge(int a, int b) {
        int parentA = find(a), parentB = find(b);
        if (parentA == parentB) {
            O.push_back(-1);
        } else {
            if (rank[parentA] > rank[parentB]) {
                parent[parentB] = parentA;
                O.push_back(parentB);
            } else {
                parent[parentA] = parentB;
                O.push_back(parentA);
                if (rank[parentA]==rank[parentB]) {
                    rank[parentB]++;
                }
            }
            components--;
        }
    }
 
    int getComponents() {
        return components;
    }
 
    void undo() {
        assert(!O.empty());
        int delta = O.back();
        O.pop_back();
        if (delta!=-1) {
            parent[delta]=delta;
            components++;
        }
    }
};