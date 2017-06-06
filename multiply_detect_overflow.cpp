/**
 * Description: Multiply two 64-bit integers and checks if there is overflow. In later case INF is returned 
 * Usage: mul O(1)
 * Source: https://github.com/dragonslayerx 
 */

const long long INF = 1000000000000000005LL;
long long mul(long long a, long long b) {
	pair<long long, long long> s, t, result;
	t.first = a / 1000000000;
	t.second = a % 1000000000;

	s.first = b / 1000000000;
	s.second = b % 1000000000;

	long long r1, r2, r3, r4;

	r1 = t.first * s.first;
	r2 = t.first * s.second;
	r3 = t.second * s.first;
	r4 = t.second * s.second;

	if (r1 > 1) return INF;
	else if (r1 && (r2 || r3 || r4)) return INF;
	else if ((r2 + r3) > 1000000000) return INF;
	else if ((r2 + r3)*1000000000 + r4 > 1000000000000000000LL) return INF;
	else return r1*1000000000000000000LL + (r2 + r3)*1000000000 + r4;
}
