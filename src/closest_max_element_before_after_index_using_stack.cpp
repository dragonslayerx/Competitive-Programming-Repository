/**
 * Description: Find the closest larger element before and after an index.
 * Usage: See below O(N)
 * Source: https://github.com/dragonslayerx
 */

 #include <iostream>
 #include <cstdio>
 #include <vector>
 #include <stack>

 using namespace std;

 int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    const int max = 100005;
    int after[max], before[max];
    stack<pair<int,int> > S, T;
    for (int i = 0; i < n; i++) {
        while (!S.empty() && (S.top().first <= a[i])) S.pop();
        if (S.empty()) {
            before[i] = -1;
        } else {
            before[i] = S.top().second;
        }
        S.push(make_pair(a[i], i));
    }

    for (int i = n-1; i >= 0; i--) {
        while (!T.empty() && (T.top().first <= a[i])) T.pop();
        if (T.empty()) {
            after[i] = n;
        } else {
            after[i] = T.top().second;
        }
        T.push(make_pair(a[i], i));
    }

    cout << "Before:" << endl;
    for (int i = 0; i < n; i++) {
        cout << before[i] << " ";
    }
    cout << endl;

    cout << "After:" << endl;
    for (int i = 0; i < n; i++) {
        cout << after[i] << " ";
    }
    cout << endl;

}
