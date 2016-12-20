/**
 * Description: Dynamic String Hashing (Supports updating string characters)    
 * Usage: See below, update O(lg(N)), getHash O(lg(N))
 * Source: https://github.com/dragonslayerx 
 */

long long power(long long n, long long m, long long MOD)
{
    if (m == 0) return 1;
    long long x = power(n, m / 2, MOD);
    if (!(m & 1)) return (x * x) % MOD;
    else return (((x * x) % MOD) * n) % MOD;
}

const long long B = 100000007;
const long long M = 1000000009;
const long long invB = power(B-1, M-2, M); //inverse of B-1

long long pB[MAX];
void pInit() {
    pB[0] = 1;
    for (int i = 1; i < MAX; i++) {
        pB[i] = (pB[i-1] * B) % M;
    }
}

struct node {
    long long val;
    bool flag;
    long long lazy;
    node() {
        flag = false;
        val = lazy = 0;
    }
} st[4*MAX];

long long update(int n, int l, int r, int ql, int qr, int c) {
    if (st[n].flag) {
        st[n].val = (((st[n].lazy * (pB[r-l+1]+M-1) % M) % M) * invB) % M;
        if (l != r) {
            st[2*n+1].flag = true;
            st[2*n+1].lazy = st[n].lazy;
            st[2*n+2].flag = true;
            st[2*n+2].lazy = st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }

    if (qr < l or ql > r) {
        return st[n].val;
    } else if (l >= ql and r <= qr) {
        st[n].val = (((c * (pB[r-l+1]+M-1) % M) % M) * invB) % M;
        if (l != r) {
            st[2*n+1].flag = true;
            st[2*n+1].lazy = c;
            st[2*n+2].flag = true;
            st[2*n+2].lazy = c;
        }
        return st[n].val;
    } else {
        int mid = (l + r)/2;
        long long leftHash = update(2*n+1, l, mid, ql, qr, c);
        long long rightHash = update(2*n+2, mid+1, r, ql, qr, c);
        st[n].val = ((leftHash * pB[r - mid]) % M + rightHash) % M;
        return st[n].val;
    }
}

long long getHash(int n, int l, int r, int ql, int qr) {
    if (st[n].flag) {
        st[n].val = (((st[n].lazy * (pB[r-l+1]+M-1) % M) % M) * invB) % M;
        if (l != r) {
            st[2*n+1].flag = true;
            st[2*n+1].lazy = st[n].lazy;
            st[2*n+2].flag = true;
            st[2*n+2].lazy = st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }
    if (qr < l or ql > r) {
        return 0;
    } else if (l >= ql &&  r <= qr) {
        return (st[n].val * pB[qr - r]) % M;
    } else {
        int mid = (l + r)/2;
        long long leftHash = getHash(2*n+1, l, mid, ql, qr);
        long long rightHash = getHash(2*n+2, mid+1, r, ql, qr);
        long long h = (leftHash + rightHash) % M;
        return h;
    }
}

int main(){
    pInit();
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    char s[MAX];
    scanf("%s", s);
    for (int i = 0; i < n; i++) {
        update(0, 0, n-1, i, i, s[i] - '0');
    }
    for (int i = 0; i < m+k; i++) {
        int choice;
        scanf("%d", &choice);
        if (choice == 1){
            int l, r, c;
            scanf("%d%d%d", &l, &r, &c);
            l--, r--;
            update(0, 0, n-1, l, r, c);
        } else if (choice == 2) {
            int l, r, c;
            scanf("%d%d%d", &l, &r, &c);
            l--, r--;
            if (r-c < l) {
                printf("YES\n");
            } else {
                long long h1 = getHash(0, 0, n-1, l, r-c);
                long long h2 = getHash(0, 0, n-1, l+c, r);
                if (h1 == h2) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            }
        }
    }
}

