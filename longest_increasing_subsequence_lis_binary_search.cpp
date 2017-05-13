/**
 * Description: Longest Increasing Subsequence
 * Usage: LIS O(N lg(N))
 * Source: https://github.com/dragonslayerx
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int LIS(const vector<int> &a){
    vector<int> lis;
    lis.push_back(a[0]);
    for (int i = 1; i < a.size(); i++) {
        vector<int>::iterator pos = upper_bound(lis.begin(), lis.end(), a[i]);
        if (pos == lis.end()) {
            lis.push_back(a[i]);
        } else {
            int idx = pos - lis.begin();
            lis[idx] = a[i];
        }
    }
    return lis.size();
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << LIS(a) << endl;
}
