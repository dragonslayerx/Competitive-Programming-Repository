#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MOD 1000000007

string tostring(long long x){
    string A;
    for (int i = 63; i >= 0; i--) {
        if (x & (1LL << i)) A.push_back('1');
        else A.push_back('0');
    }
    return A;
}

bool exist[105][5][5][5][5];
long long dp[105][5][5][5][5];

string A, B, C, D;

long long solve(int idx, bool b1, bool b2, bool b3, bool b4)
{
    if (idx == 64) {
        return 1;
    }
    if (!exist[idx][b1][b2][b3][b4]) {
        int max1 = 1;
        int max2 = 1;
        int max3 = 1;
        if (b1) max1 = A[idx] - '0';
        if (b2) max2 = B[idx] - '0';
        if (b3) max3 = C[idx] - '0';
        long long answer = 0;
        for (int i = 0; i <= max1; i++) {
            for (int j = 0; j <= max2; j++) {
                for (int k = 0; k <= max3; k++) {

                    int result_bit = (i ^ j) | k; // type your expression here

                    int nb1 = b1 && ((A[idx] - '0') == i);
                    int nb2 = b2 && ((B[idx] - '0') == j);
                    int nb3 = b3 && ((C[idx] - '0') == k);
                    int nb4 = (b4 && (result_bit == (D[idx] - '0')));

                    if (b4) {
                        if (result_bit <= D[idx] - '0') answer += solve(idx+1, nb1, nb2, nb3, nb4);
                    } else {
                        answer += solve(idx+1, nb1, nb2, nb3, nb4);
                    }

                    answer %= MOD;
                }
            }
        }
        exist[idx][b1][b2][b3][b4] = 1;
        dp[idx][b1][b2][b3][b4] = answer;
    }
    return dp[idx][b1][b2][b3][b4];
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(dp, 0, sizeof(dp));
        memset(exist, 0, sizeof(dp));

        long long a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        A = tostring(a); B = tostring(b); C = tostring(c); D = tostring(d);
        printf("%lld\n", solve(0, 1, 1, 1, 1));
    }
}
