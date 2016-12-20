/**
 * Description: Ternary search
 * Usage: getMax O(lg(N))
 * Source: https://github.com/dragonslayerx 
 */

ll f(int mid) {
    
}


ll getMax(int ll, int rr) {
    int l = ll, r = rr;
    while (r - l > 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (f (m1) < f (m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    for (int i = l; i <= r; i++) maxv = max(maxv, f(i));
    return maxv;
}