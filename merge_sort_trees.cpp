/**
 * Description: Merge sort tree
 * Usage: construct O(Nlg(N)), query O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

#define MAX 30050

vector<vector<int> > st;
int a[MAX];

void merge(int n, int left, int right) {
    int lptr = 0, rptr = 0, cptr = 0;;
    while (lptr < st[left].size() || rptr < st[right].size()) {
        if (lptr == st[left].size())
            st[n][cptr++] = st[right][rptr++];
        else if (rptr == st[right].size())
            st[n][cptr++] = st[left][lptr++];
        else {
            if (st[left][lptr] < st[right][rptr])
                st[n][cptr++] = st[left][lptr++];
            else
                st[n][cptr++] = st[right][rptr++];
        }
    }
}

void construct(int n, int ll, int rl) {
    if (ll == rl) {
        st[n].push_back(a[ll]);
        return;
    }
    construct(2*n+1, ll, (ll+rl)/2);
    construct(2*n+2, (ll+rl)/2+1, rl);
    st[n].resize(rl-ll+1);
    merge(n, 2*n+1, 2*n+2);
}

int query(int n, int ll, int rl, int ql, int qr, int k) {
    if (rl < ql || ll > qr) return 0;
    if (ll >= ql && rl <= qr) {
        // modify here
        int t = st[n].end() - upper_bound(st[n].begin(), st[n].end(), k);
        return t;
    }
    int left = query(2*n+1, ll, (ll+rl)/2, ql, qr, k);
    int right = query(2*n+2, (ll+rl)/2+1, rl, ql, qr, k);
    return left + right;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    st.resize(4*MAX);
    construct(0, 0, n-1);

    int q;
    scanf("%d", &q);
    while (q--) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        i--, j--;
        int answer = query(0, 0, n-1, i, j, k);
        printf("%d\n", answer);
    }

}
