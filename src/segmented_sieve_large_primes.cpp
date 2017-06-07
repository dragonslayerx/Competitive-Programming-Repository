/**
 * Description: Get primes in range [ll, ul].
 * Usage: getPrimes. O(NlgN) where N = ul-ll+1
 * Source: https://github.com/dragonslayerx
 */

void getPrimes(int ll, int ul, set<int> &largePrimes) {
    vector<bool> isprm;
    isprm.resize(ul - ll + 1);
    for(int i = 0; i < ul - ll + 1; i++) {
        isprm[i] = 1;
    }
    for (int i = 2; i*i <= ul; i++) {
        if (isprime[i]) {
            int j;
            j = ll / i;
            for(; i * j <= ul; j++) {
                if (i * j >= ll && j > 1) {
                    isprm[i * j - ll] = 0;
                }
            }
        }
    }
    for (int i = ll; i <= ul; i++) {
        if (isprm[i - ll] && i > 1) {
            largePrimes.insert(i);
        }
    }
}
