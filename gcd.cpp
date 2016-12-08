long long gcd (long long a, long long b) {
	if (b==0) return a;
	else return gcd(b,a%b);
}

