/**
 * Description: Range Min Query using Sparse Table
 * Usage: construct O(NlgN), query O(lg(N))
 * Source: https://github.com/dragonslayerx
 */
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX = 100005;
const int size = 25;

int rmq[size][MAX];

void construct(int a[], int n){
    for (int j = 0; j < n; j++) rmq[0][j] = a[j];
    for (int i = 1; i < size; i++) {
        int length = 1<<(i-1);
        for (int j = 0; j < n; j++) {
            if (j+length > n) rmq[i][j] = max(rmq[i-1][j], 0);
            else rmq[i][j] = max(rmq[i-1][j], rmq[i-1][j+length]);
        }
    }
}

/**
 * Usage: query O(lg(N))
 */

int query(int l, int r){
    int length = r-l+1, p = 0;
    while ((1 << p) <= length) p++;
    p--;
    return max(rmq[p][l], rmq[p][r-(1<<p)+1]);
}

int main() {
    int n;
    cin >> n;
    int a[MAX];
    for (int i = 0; i < n; i++) cin >> a[i];
    construct(a, n);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << query(l, r) << endl;
    }
}

/**
 * Usage: preprocess O(N), query O(1)
 * Note: Call preprocess function before using query function.

int frameSize[MAX];
int preprocess(){
    for(int i=0, pow2=1; pow2 < MAX;  pow2*=2, i++)
        frameSize[pow2]=i;
    for(int i=3;i<MAX;i++) {
        if(frameSize[i]==0) {
            frameSize[i]=frameSize[i-1];
        }
    }
}

inline int query(int rmq[][MAX], int l, int r){
    int p = frameSize[r-l+1];
    return min(rmq[p][l], rmq[p][r-(1<<p)+1]);
}
*/
