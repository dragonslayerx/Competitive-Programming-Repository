/**
 * Description: Sum of n/1 + n/2 + n/3 + ... + n/n  
 * Usage: See below. O(sqrt(n))
 * Note: This method can be extended to any function that takes only O(sqrt(n)) distinct values.
 * Source: https://github.com/dragonslayerx 
 */

long long n;
scanf("%lld", &n);
long long answer = 0;
int i;
for (i = 1; (long long)i*i <= n; i++) {
    answer += n/i;
    answer %= MOD;
}
i--;
for (int j = 1; n/(j+1) >= i; j++) {
    answer += (((n/j - n/(j+1)) % MOD) * j) % MOD;
    answer %= MOD;
}
printf("%lld\n", answer);
