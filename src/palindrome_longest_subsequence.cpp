/**
 * Description: Find longest length palindromic subsequence in s[i..j]
 * Usage: See below O(V^2)
 * Source: https://github.com/dragonslayerx
 */
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

void process(const string &s, int last[][30]) {
        int n = s.size();
        for (int j = 0; j < 26; j++) {
            if (j==s[0]-'a') {
                last[0][j] = 0;
            } else {
                last[0][j] = -1;
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                last[i][j] = last[i-1][j];
            }
            last[i][s[i]-'a'] = i;
        }

}

int last[1005][30];
int dp[1005][1005];

int main() {
    string s;
    cin >> s;
    int len = s.size();

    process(s, last);

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < len; i++) dp[i][i] = 1;
    for (int i = len-1; i >= 0; i--) {
        for (int j = i+1; j < len; j++) {
            dp[i][j] = 1;
            dp[i][j] = max(dp[i][j], dp[i+1][j]);
            if (last[j][s[i]-'a'] > i) {
                dp[i][j] = max(dp[i][j], 2 + dp[i+1][last[j][s[i]-'a']-1]);
            }
        }
    }

    cout << dp[0][len-1] << endl;
}
