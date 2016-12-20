/**
 * Description: Mobeius Function.
 * Usage: initmobeius O(Nlg(N))  
 * Source: https://github.com/dragonslayerx 
 */

vector<int> mobeius;
vector<int> no_prime_factors;
#define INVALID INT_MAX
void initmobeius(int n){
    mobeius.resize(n + 1, INVALID);
    no_prime_factors.resize(n + 1);
    mobeius[1] = 0;
    mobeius[2] = 1, no_prime_factors[2] = 0;
    for (int i = 2; i <= n; i++) {
        if (mobeius[i]) {
            if (no_prime_factors[i] == 0) {
                mobeius[i] = 1;
                for (int j = 1; i * j <= n; j++)
                    no_prime_factors[i * j] += 1;
            }
            else if (no_prime_factors[i] == 1) {
                mobeius[i] = 0;
                for (int j = 1; i * j <= n; j++)
                    mobeius[i * j] = 0;
            }
            else if (no_prime_factors[i] & 1)
                mobeius[i] = 1;
            else
                mobeius[i] = -1;
        }
    }
}
