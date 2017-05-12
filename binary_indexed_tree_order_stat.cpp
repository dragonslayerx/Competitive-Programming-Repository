/**
 * Description: BIT Orderstat (Returns Kth order statistic). 
 * Usage: update O(lg(N)), statquery O(lg^2(N))
 * Note: Perform range compression if range is large.
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 100005;
typedef long long ll;

ll bit[MAX];

ll query(int indx){
    ll sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= (indx & -indx);
    }
    return sum;
}

void update(ll indx, ll x){
    while (indx < MAX) {
        bit[indx] += x;
        indx += (indx & -indx);
    }
}

int statquery(int k){
    int low = 0, high = MAX-1, ans = 0;
    while (low <= high) {
        int mid = low + ((high - low)>>1);
        int qr = query(mid);
        if (qr >= k) {ans = mid, high = mid - 1;}
        else if (qr < k) low = mid + 1;
    }
    return ans;
}