/**
 * Description: Ternary search
 * Usage: getMax O(lg(N))
 * Note: The function f should be strictly increasing and then strictly decreasing. 
 *       See http://codeforces.com/blog/entry/11497 for more help. 
 * Source: https://github.com/dragonslayerx 
 */

ll f(int mid) {
    
}

ll getMax(int ll, int rr) {
    int lo = ll, hi = rr;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(f(mid) > f(mid+1)) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    return lo+1;
}
