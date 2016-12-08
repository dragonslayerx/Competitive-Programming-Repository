long long Lucas_nCr(long long n, long long m){
    long long m0 = m % MOD;
    long long m1 = m / MOD;
    long long n0 = n % MOD;
    long long n1 = n / MOD;

    long long answer = 1;
    if (n0 >= m0) {
        answer *= C(n0, m0);
        answer %= MOD;
    } else {
        answer = 0;
    }
    if (n1 >= m1) {
        answer *= C(n1, m1);
        answer %= MOD;
    } else {
        answer = 0;
    }

    return answer;
}