/**
 * Description: Rabin-Karp Hashing
 * Usage: findSubstring O(N)
 * Note: Its not useful as adversary can generate cases like (T="aaaaaaaaaaa", P="aaa").
 * Source: https://github.com/dragonslayerx
 */

 #include <iostream>
 #include <cstdio>
 using namespace std;


long long pow(long long a, long long b, long long MOD){
	if (b == 0) return 1;
	long long p = pow(a, b/2, MOD);
	p = (p * p) % MOD;
	if (b & 1)  {
		return (p * a) % MOD;
	} else {
		return p % MOD;
	}
}

typedef long long int64;
int findSubtring(string T, string P, int d, int MOD){
	int n =T.size(), m = P.size();
	int64 p = 0, t = 0;
	int64 h = pow(d, m - 1, MOD);
	for (int i = 0; i < m; i++) {
		p *= d, p += (P[i] - 'a'), p %= MOD;
		t *= d, t += (T[i] - 'a'), t %= MOD;
	}
	for (int i = 0; i < n - m + 1; i++){
		//cerr << t << " " << p << endl;
		if (p == t)  {
			if (T.substr(i, m) == P) {
				return i;
			}
		}
		if (i < n - m) {
			t = (((d * (t + MOD - ((T[i] - 'a') * h) % MOD) % MOD) % MOD) + (T[i + m] - 'a')) % MOD;
		}
	}
	return -1;
}


int main(){
	cout << findSubtring("swapnil", "n", 26, 1000000007) << endl;
}
