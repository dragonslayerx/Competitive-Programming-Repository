/**
 * Description: Persistent Segment trees (Version Query)
 * Usage: See below update O(lg(N)), query O(lg(N)), construct O(Nlg(N)) 
 * Source: https://github.com/dragonslayerx 
 */

struct Node {
    long long value;
    Node *left, *right;
    Node() {
        left=right=NULL;
    }
};

const int MAX = 100005; // # of updates
Node *root[MAX];
class PersistentST {

    const int n; //size of array
    int version; // current version
	int size;

    Node* createNewNode() {
        return new Node;
    }

    long long mergeFunction(Node *left, Node *right) {
        return left->value + right->value;
    }


    Node* construct(long long val[], int l, int r) {
        Node *x = createNewNode();;
        if (l == r) {
            x->value = (val==NULL)?0:val[l]; // NULL in case to be initialized with 0 initially
            return x;
        } else {
            int mid = (l+r)/2;
            x->left = construct(val, l, mid);
            x->right = construct(val, mid+1, r);
            x->value = mergeFunction(x->left, x->right);
            return x;
        }
    }

    Node* update(int l, int r, Node *prevVersionPtr, const int pos, const long long updatedVal) {
        Node *x = createNewNode();
        if (l == r) {
            x->value = prevVersionPtr->value + updatedVal;
        } else {
            int mid = (l+r)/2;
            if (pos <= mid) {
                x->left = update(l, mid, prevVersionPtr->left, pos, updatedVal);
                x->right = prevVersionPtr->right;
            } else {
                x->right = update(mid+1, r, prevVersionPtr->right, pos, updatedVal);
                x->left = prevVersionPtr->left;
            }
            x->value = mergeFunction(x->left, x->right);
        }
        return x;
    }

    long long query(Node *x, int l, int r, const int ql, const int qr) {
        if (r < ql || l > qr) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return x->value;
        } else {
            int mid = (l+r)/2;
            long long left = query(x->left, l, mid, ql, qr);
            long long right = query(x->right, mid+1, r, ql, qr);
            return left+right;
        }
    }

public:

    PersistentST(int n): n(n) {
        version = 0;
		size = 0;
    }

    void construct(long long val[]) {
        root[0]=construct(val, 0, n-1);
    }

    void update(int p, long long x) {
        root[version+1]=update(0, n-1, root[version], p, x);
        version++;
    }

    long long query(int queryVersion, int l, int r) {
        return query(root[queryVersion], 0, n-1, l, r);
    }

    Node *getVersion(int ver) {
        return root[ver];
    }
};

int main() {
    long long a[5] = {1, 2, 3, 4, 5};
    PersistentST S(5);
    S.construct(a);
    cout << S.query(0, 1, 2) << endl;
    S.update(1, 5);
    cout << S.query(1, 1, 2) << endl;
}
