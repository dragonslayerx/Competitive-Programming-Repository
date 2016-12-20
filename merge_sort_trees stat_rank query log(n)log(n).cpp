/**
 * Description: Merge sort tree for order statistics and rank query in range. 
 * Usage: insertST O(lg(N)), removeST O(lg(N)), queryST O(lg^2(N)), queryOrderST O(lg^2(N))
 * Source: https://github.com/dragonslayerx 
 */

int queryOrderST(int n, int ll, int rl, int ql, int qr, int k)
{
    if (ll == rl) return ll;
    int count = upper_bound(st[(n<<1)+1].begin(), st[(n<<1)+1].end(), qr) -
                lower_bound(st[(n<<1)+1].begin(), st[(n<<1)+1].end(), ql);
    int m = (ll + rl)>>1;
    if (count > k) {
        return queryOrderST((n<<1)+1, ll, m, ql, qr, k);
    } else {
        return queryOrderST((n<<1)+2, m+1, rl, ql, qr, k - count);
    }
}

int queryST(int n, int ll, int rl, int ql, int qr, int x)
{
    int mid = (ll + rl)>>1;
    if (x == mid) {
        int count = upper_bound(st[(n<<1)+1].begin(), st[(n<<1)+1].end(), qr) -
                    lower_bound(st[(n<<1)+1].begin(), st[(n<<1)+1].end(), ql);
        return count;
    }
    if (x < mid) {
        return queryST((n<<1)+1, ll, mid, ql, qr, x);
    } else {
        int count = upper_bound(st[(n<<1)+1].begin(), st[(n<<1)+1].end(), qr) -
                    lower_bound(st[(n<<1)+1].begin(), st[(n<<1)+1].end(), ql);
        return count + queryST((n<<1)+2, mid+1, rl, ql, qr, x);
    }
}

void insertST(int n, int ll, int rl, int q, int k)
{
    if (k >= ll && k <= rl) {
        st[n].push_back(q);
        if (ll != rl) {
            insertST((n<<1)+1, ll, ((ll+rl)>>1), q, k);
            insertST((n<<1)+2, ((ll+rl)>>1)+1, rl, q, k);
        }
    }
}

void removeST(int n, int ll, int rl, int q)
{
    if (q >= ll && q <= rl) {
        st[n].pop_back();
        if (ll != rl) {
            removeST((n<<1)+1, ll, ((ll+rl)>>1), q);
            removeST((n<<1)+2, ((ll+rl)>>1)+1, rl, q);
        }
    }
}