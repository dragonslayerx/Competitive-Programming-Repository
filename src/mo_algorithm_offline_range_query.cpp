/**
 * Description: Mo Algorithm (Support offline query processing)
 * Usage: See below (O(N sqrt(N))) 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAX = 100005

struct Query {
    int l, r;
    int idx;
    int answer;
    Query(int l, int r, int idx) {
        this->l = l;
        this->r = r;
        this->idx = idx;
    }
};

int S;
void initS(int n) { S = sqrt(n); }

bool compare(Query a, Query b) {
    if (a.l/S != b.l/S) {
        return a.l/S < b.l/S;
    } else {
        return a.r > b.r;
    }
}

//--Data-Strcuture
int Answer = 0;
inline void insert(int v) {
}

inline void erase(int v) {
}
//-------------

int answer[MAX];

int main() {
    int n, q;
    cin >> n >> q;
    initS(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > n) a[i] = n+1;
    }
    vector<Query> query;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        query.push_back(Query(l, r, i));
    }
    sort(query.begin(), query.end(), compare);
    int left = 0, right = -1;
    for (int i = 0; i < query.size(); i++) {
        int l = query[i].l;
        int r = query[i].r;
        if (right < r) {
            while (right < r) {
                right++; insert(a[right]);
            }
        } else {
            while (right > r) {
                erase(a[right]); right--;
            }
        }
        if (left < l) {
            while (left < l) {
                erase(a[left]); left++;
            }
        } else {
            while (left > l) {
                left--; insert(a[left]);
            }
        }
        answer[query[i].idx] = Answer;
    }

    for (int i = 0; i < q; i++) {
        cout << answer[i] << endl;
    }
}
