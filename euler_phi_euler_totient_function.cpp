/**
 * Description: Euler Totient function  
 * Usage: See below
 * Note: The code is taken from http://www.geeksforgeeks.org/eulers-totient-function/
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<bool> isprime;
vector<int> primes;

void sieve(int n){
    isprime.resize(n, 1);
    for (int i = 2; i < n; i++) {
        if (isprime[i]) {
            for (int j = 2; i*j < n; j++) {
                isprime[i*j] = 0;
            }
        }
    }
    for (int i = 2; i < n; i++)
        if (isprime[i])primes.push_back(i);
}

int phi(const int n){
  if ( n < 2 )
    return 0;
  if (isprime[n] )
    return n-1;
  if ( n & 1 == 0 ) {
    int m = n >> 1;
    return !(m & 1) ? phi(m)<<1 : phi(m);
  }
  for ( std::vector<int>::iterator p = primes.begin(); p != primes.end() && *p <= n; ++p ){
    int m = *p;
    if ( n % m  ) continue;

    // phi is multiplicative
    int o = n/m;
    int d = __gcd(m, o);
    return d==1? phi(m)*phi(o) : phi(m)*phi(o)*d/phi(d);
  }
}

int main()
{
    sieve(1000005);
    vector<int> ephi(1000005);
    for (int i = 1; i <= 1000005; i++)
        ephi[i] = phi(i);

    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        if (m > n) {cout << 0 << endl; continue;}
        int k = n/m;
        long long answer = 0;
        for (int i = 1; i <= k; i++) {
            answer += ephi[i];
        }
        cout << answer + 1 << endl;
    }
}
