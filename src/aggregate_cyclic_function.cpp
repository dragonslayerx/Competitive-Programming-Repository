/**
 * Description: Calculate aggregate of k terms in a cyclic function
 * Note: cycle length must be small.
 *	 getNext and getCyclicFuncfion must be overridden accordingly.
 * Assumption: seed is considered as the 0th element of the sequence
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

long long getNext(long long x) {
    return x + 1;
}

long long getCyclic(long long x) {
    return x % 5;
}

long long getSum(long long seed, long long k) {
    const int INF = 1e9;
    long long cycleLength = INF, cycleStart = -1;
    map<int,int> index;
    index[getCyclic(seed)] = 0;
    {
        long long x = seed;
        for (int i = 1; i <= k; i++) {
            x = getNext(x);
            long long c = getCyclic(x);
            if (index.count(c)) {
                cycleStart = index[c];
                cycleLength = i-cycleStart;
                break;
            } else {
                index[c] = i;
            }
        }
    }
    long long sum = 0;
    {
        if (cycleLength == INF) {
            sum += getCyclic(seed);
            long long x = seed;
            for (int i = 1; i <= k; i++) {
                x = getNext(x);
                sum += getCyclic(x);
            }
        } else {
            k++;
            long long x = seed;
            for (int i = 1; i <= cycleStart; i++) {
                sum += getCyclic(x);
                x = getNext(x);
                k--;
            }

            long long turns = k/cycleLength;
            long long rem = k%cycleLength;

            long long cycleSum = 0, remSum = 0;
            for (int i = 0; i < cycleLength; i++) {
                long long c = getCyclic(x);
                cycleSum +=  c;// modify here
                if (i < rem) {
                    remSum += c; // modify here
                }
                x = getNext(x);
            }
            sum += turns * cycleSum + remSum;
        }
    }
    return sum;
}

int main() {
    cout << getSum(1, 6) << endl;
}
