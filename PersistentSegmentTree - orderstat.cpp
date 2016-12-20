/**
 * Description: Persistent Segment trees (Order Statistics)
 * Usage: See below <O(Nlg(N)), O(lg(N))> 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

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

class OrderStat {
public:
    const int n;
    PersistentST S;

    OrderStat(long long a[], int n) : n(n), S(n) {
        S.construct(NULL);
        // Map all elements of a from 0..n-1 first
        for (int i = 0; i < n; i++) {
            S.update(a[i], +1);
        }
        /*for (int i = 0; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                cout << S.query(i, j, j) << " ";
            }
            cout << endl;
        }*/
    }

    int getOrderStat(int ql, int qr, int k) {
        assert(k <= qr-ql+1);
        int l = 0, r = n-1;
        Node *pL = S.getVersion(ql), *pR = S.getVersion(qr+1);
        while (l < r) {
            int mid = (l+r)/2;
            int count = (pR->left->value - pL->left->value);
            if (count >=  k) {
                pL=pL->left, pR=pR->left;
                r = mid;
            } else {
                k-=count;
                pL=pL->right, pR=pR->right;
                l = mid+1;
            }
        }
        return l;
    }
};

int main() {
    long long a[5] = {1, 1, 3, 2, 4};
    OrderStat O(a, 5);
    cout << O.getOrderStat(0, 4, 5) << endl;;
}
