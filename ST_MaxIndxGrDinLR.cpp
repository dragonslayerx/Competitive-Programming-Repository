/**
 * Description: Segment tree to find max index having value greater than D in range [L, R]   
 * Usage: See below. O(lg^2(n))
 * Source: https://github.com/dragonslayerx 
 */

vector<ii> st[4*MAX];
vector<int> maxUpto[4*MAX];

void merge(int currentX, int leftX, int rightX) {
    vector<ii> &current = st[currentX];
    vector<ii> &left = st[leftX], &right = st[rightX];

    int l = 0, r = 0, cur = 0;
    while ((l < left.size()) or (r < right.size())) {
        if (l == left.size()) current[cur++]=right[r++];
        else if (r == right.size()) current[cur++]=left[l++];
        else {
            if (left[l] <= right[r]) {
                current[cur++] = left[l++];
            } else {
                current[cur++] = right[r++];
            }
        }
    }

    int sz = maxUpto[currentX].size();
    maxUpto[currentX][sz-1] = current[sz-1].second;
    for (int i = sz-2; i >= 0; i--) {
        maxUpto[currentX][i]=max(maxUpto[currentX][i+1], current[i].second);
    }

}

void construct(vector<int> &a, int n, int ll, int rl) {
    if (ll==rl) {
        st[n].push_back(make_pair(a[ll], ll));
        maxUpto[n].push_back(ll);
    } else {
        int mid = (ll+rl)/2;
        construct(a, 2*n+1, ll, mid);
        construct(a, 2*n+2, mid+1, rl);
        st[n].resize(rl-ll+1);
        maxUpto[n].resize(rl-ll+1);
        merge(n, 2*n+1, 2*n+2);
    }
}

//returns max index element > d in [ll..rl]. return -1 if none exists
int query(int n, int ll, int rl, int ql, int qr, int d) {
    if (ll >= ql && rl <= qr) {
        vector<ii>::iterator it = upper_bound(st[n].begin(), st[n].end(), make_pair(d, INF));
        if (it == st[n].begin()) {
            return rl;
        } else if (it == st[n].end()) {
            return -1;
        } else {
            int p = it-st[n].begin();
            return maxUpto[n][p];
        }
    } else {
        int mid = (ll+rl)/2;
        if (qr <= mid) return query(2*n+1, ll, mid, ql, qr, d);
        else if (ql > mid) return query(2*n+2, mid+1, rl, ql, qr, d);
        else {
            int left = query(2*n+1, ll, mid, ql, qr, d);
            int right = query(2*n+2, mid+1, rl, ql, qr, d);
            return max(left, right);
        }
    }
}