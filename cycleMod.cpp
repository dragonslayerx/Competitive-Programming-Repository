/**
 * Description: Calculate aggregate of k terms in a cyclic function 
 * Note: cycle length must be small. 
	 getNext and getCyclicFuncfion must be overridden accordingly. 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

int getNext(int x) {
    return x + x%100;
}

int getCf(int x) {
    return x%100;
}

long long getSum(long long n, long long k) {
    const int INF = 1e9;
    long long cycleLength = INF, cycleStart = -1;
    map<int,int> modSoFar;
    modSoFar[getCf(n)] = 0; //initial value of cyclic-function
    {
        long long x = n;
        for (int i = 1; i <= k; i++) {
            x = getNext(x); //modify function here
            int mod = getCf(x); //modify cyclic-function here
            if (modSoFar.count(mod)) {
                cycleStart = modSoFar[mod];
                cycleLength = i-cycleStart;
                break;
            } else {
                modSoFar[mod] = i;
            }
        }
    }

    long long sum = n;
    {
        if (cycleLength == INF) {
            long long sum = 0;
            long long x = n;
            for (int i = 1; i <= k; i++) {
                int mod = getCf(x); //modify cyclic-function here
                x = getNext(x); //modify function here
            }
            printf("%lld\n", x);
        } else {
            long long sum = n;
            long long x = n;
            for (int i = 1; i <= cycleStart; i++) {
                int mod = getCf(x); //modify cyclic-function here
                x = getNext(x); //modify function here
                sum += mod;
                k--;
            }

            long long turns = k/cycleLength;
            long long rem = k%cycleLength;

            long long cycleSum = 0, remSum = 0;
            for (int i = 0; i < cycleLength; i++) {
                int mod = getCf(x); //modify cyclic-function here
                x = getNext(x); //modify function here
                cycleSum += mod;
                if (i < rem) {
                    remSum += mod;
                }
            }
            sum += turns * cycleSum + remSum;
        }
    }

    return sum;
}

int main() {
}
