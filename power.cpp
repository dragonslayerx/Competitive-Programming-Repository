/**
 * Description: Calculates n^m (Binary exponentiation)
 * Usage: power O(lg(M)) 
 * Source: https://github.com/dragonslayerx 
 */

#define MOD 1000000007
long long power(long long n, long long m)
{
    if (m == 0) return 1;
    long long x = power(n, m / 2);
    if (!(m & 1)) return (x * x) % MOD;
    else return (((x * x) % MOD) * n) % MOD;
}

