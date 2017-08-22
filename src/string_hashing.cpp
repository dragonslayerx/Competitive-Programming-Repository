/**
 * Description: String Hashing 
 * Usage: initalize O(N), getHash O(n), getSubHash O(1), getRevSubHash O(1) 
 * Note: In case double hashing is required http://codeforces.com/contest/710/submission/20094958
 * Source: https://github.com/dragonslayerx 
 */
 
long long power(long long n, long long m, long long MOD){
    if (m == 0) return 1;
    long long x = power(n, m/2, MOD);
    if (!(m & 1)) return (x * x) % MOD;
    else return (((x * x) % MOD) * n) % MOD;
}

class StringHash {
    const static int MAX = 300005;

    ll b = 100000009;
    ll m = 1000000007;

    ll B[MAX], inverseB[MAX];
    
    void initialize() {
        B[0]=1;
        for (int i = 1; i < MAX; i++) {
            B[i]=(B[i-1]*b)%m;
        }
        inverseB[MAX-1]=power(B[MAX-1], m-2, m);
        for (int i = MAX-2; i >= 0; i--) {
            inverseB[i]=(inverseB[i+1]*b)%m;
        }
    }
 
public:
    StringHash() {
        initialize();
    }

    ll getHash(char *s) {
        long long h = 0;
        for (int i = 0; s[i]; i++) {
            h = (h + (s[i] * B[i])) % m;
        }
        return h;
    }

    int length=0;
    ll h[MAX], revh[MAX];
    ll construct(char *s) {
        length = strlen(s);
        h[0]=0, revh[length+1]=0;
        for (int i = 0, j = 1; s[i]; i++, j++) {
            h[j] = (h[j-1] + (s[i] * B[i]) % m) % m ;
        }
        for (int i = length-1, j = length, k = 0; i >= 0; i--, j--, k++) {
            revh[j] = (revh[j+1] + ((s[i] * B[k]) % m)) % m;
        }
        return h[length];
    }

    ll getSubHash(int i, int j) {
        i++, j++;
        return ((h[j] + (m-h[i-1])) * inverseB[i-1]) % m;
    }

    ll getRevHash(int i, int j) {
        i++, j++;
        return ((revh[i] + (m-revh[j+1])) * inverseB[length-j]) % m;
    }
};
