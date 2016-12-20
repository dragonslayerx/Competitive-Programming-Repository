/**
 * Description: Finds GCD of two integers 
 * Source: https://github.com/dragonslayerx 
 */

long long gcd (long long a, long long b) {
	if (b==0) return a;
	else return gcd(b,a%b);
}

