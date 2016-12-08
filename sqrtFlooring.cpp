// Sum of n/1 + n/2 + ... + n/n

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
