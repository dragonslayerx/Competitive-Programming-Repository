/**
 * Description: Range Min Query using Sparse Table
 * Usage: construct O(NlgN), query O(lg(N)) / O(1)
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
using namespace std;

#define MAX 1000000
#define size 25
int rmq[size][MAX];
int a[MAX];

void construct(int n)
{
    for (int j = 0; j < n; j++)
        rmq[0][j] = a[j];
    for (int i = 1; i < size; i++) {
        int length = 1<<(i-1);
        for (int j = 0; j < n; j++) {
            if (j+length > n) rmq[i][j] = max(rmq[i-1][j], 0);
            else rmq[i][j] = max(rmq[i-1][j], rmq[i-1][j+length]);
        }
    }
}

int query(int l, int r)
{
    int length = r-l+1, p = 0;
    while ((1 << p) <= length) p++;
    p--;
    return max(rmq[p][l], rmq[p][r-(1<<p)+1]);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    construct(n);
}

// --------------- O(1) RMQ --------------------------

int rmq[SIZE][MAX];

void construct(int *a, int n)
{
    for (int j = 0; j < n; j++)
        rmq[0][j] = a[j];
    for (int i = 1; i < SIZE; i++) {
        int length = 1<<(i-1);
        for (int j = 0; j < n; j++) {
            if (j+length > n) rmq[i][j] = min(rmq[i-1][j], 0);
            else rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+length]);
        }
    }
}

int frameSize[MAX];
int preprocess()
{
    for(int i=0, pow2=1; pow2 < MAX;  pow2*=2, i++)
        frameSize[pow2]=i;
    for(int i=3;i<MAX;i++) {
        if(frameSize[i]==0) {
            frameSize[i]=frameSize[i-1];
        }
    }
}

inline int query(int rmq[][MAX], int l, int r)
{
    int p = frameSize[r-l+1];
    return min(rmq[p][l], rmq[p][r-(1<<p)+1]);
}
