/**
 * Description: Dp, Digit-DP, Binary Exponentiation DP templates.
 * Source: https://github.com/dragonslayerx 
 */

long long dp[][];
bool exist[][];

long long solve(){
	if () {
		return;
	}
	if(!exist[][]){
		long long answer = 0;
		
		dp[][] = answer;
		exist[][] = true;
	}
	return dp[][];	
}

/**
 * Description: Digit DP
 */

template<typename T> string toString(T value){
	string s;
	while (value) {
		s.push_back(value % 10 + '0');
		value /= 10;
	}
	s.push_back('0');
	reverse(s.begin(), s.end());
	return s;
}

bool exist[][][];
long long dp[][][];

long long solve(const string &s, int digit, bool bound, ){
	if (digit == s.size()) {
		return;
	}
	if (!exist[digit][bound][]) {
		int maxDigit = (bound)? s[digit]-'0': 9;
		long long answer = 0;
		for (int i = 0; i <= maxDigit; i++) {
			int newBound = (bound && ((s[digit] - '0') == i));
			answer += solve(s, digit+1, newBound, );
		}
		dp[digit][bound][]= answer;
		exist[digit][bound][] = true;
	}
	return dp[digit][bound][];
}

/**
 * Description: Binary exponentiation DP (Non standard)
 * Note: Most of the same target problems can be solved through matrix exponentiation. 
 * It helped me once doing a Div2-E (http://codeforces.com/problemset/problem/621/E) 
 */

    long long dp[105][105] = {};

    const int maxl = 40;
    for (int i = 1; i <= maxl; i++) {
        for (int j1 = 0; j1 < x; j1++) {
            for (int j2 = 0; j2 < x; j2++) {
                ll l = 1LL<<(i-1);
                int newmod = (j1 * power(10, l, x) + j2) % x;
                dp[i][newmod] += (dp[i-1][j1] * dp[i-1][j2]) % MOD;
                dp[i][newmod] %= MOD;
            }
        }
    }

    long long ways[2][105] = {};
    bool flag = true;
    int current = 0, prev = 1;
    for (int i = 0; i <= maxl; i++) {
        if (b & (1LL<<i)) {
            memset(ways[current], 0, sizeof(ways[current]));
            if (flag) {
                for (int j = 0; j < x; j++) {
                    ways[current][j] = dp[i][j];
                }
                flag = false;
            } else {
                for (int j1 = 0; j1 < x; j1++) {
                    for (int j2 = 0; j2 < x; j2++) {
                        ll l = 1LL<<i;
                        int newmod = (j1 * power(10, l, x) + j2) % x;
                        ways[current][newmod] += (ways[prev][j1] * dp[i][j2]) % MOD;
                        ways[current][newmod] %= MOD;
                    }
                }
            }
            swap(current, prev);
        }
    }

/**
 * Description: Bitwise combinatorial DP
 * Note: Target problems include no of pairs (x, y) 
	such that x <= A, y <= B, (x op y)  <= C, where op is a bitwise operator. 
 */

string toBinaryString(long long x){
    string A;
    for (int i = 63; i >= 0; i--) {
        if (x & (1LL << i)) A.push_back('1');
        else A.push_back('0');
    }
    return A;
}

string A, B, C;
bool exist[105][2][2][2];
long long dp[105][2][2][2];

long long solve(int idx, bool b1, bool b2, bool b3){
    if (idx == 64) {
        return 1;
    }
    if (!exist[idx][b1][b2][b3]) {
        int max1 = 1, max2 = 1;
        if (b1) max1 = A[idx] - '0';
        if (b2) max2 = B[idx] - '0';
        long long answer = 0;
        for (int i = 0; i <= max1; i++) {
            for (int j = 0; j <= max2; j++) {
                    int result_bit = (i ^ j); // Expression here
                    int nb1 = b1 && ((A[idx] - '0') == i);
                    int nb2 = b2 && ((B[idx] - '0') == j);
                    int nb3 = (b3 && (result_bit == (D[idx] - '0')));
                    if (b3) {
                        if (result_bit <= D[idx] - '0') answer += solve(idx+1, nb1, nb2, nb3);
                    } else {
                        answer += solve(idx+1, nb1, nb2, nb3);
                    }
                    if (answer >= MOD) answer -= MOD;
                }
            }
        }
        exist[idx][b1][b2][b3] = true;
        dp[idx][b1][b2][b3] = answer;
    }
    return dp[idx][b1][b2][b3];
}

int main(){
	long long a, b, c;
	scanf("%lld%lld%lld", &a, &b, &c);
	A = toBinaryString(a); B = toBinaryString(b); C = toBinaryString(c);
	printf("%lld\n", solve(0, true, true, true, true));
}
