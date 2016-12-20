/**
 * Description: Finds no of divisors of p from l to r
 * Usage: getCount O(1) 
 * Source: https://github.com/dragonslayerx 
 */

ll getCount(ll l, ll r, ll p) {
    ll start = l/p + ((l%p)? 1: 0);
    ll end = r/p;
    if (end < start)
        return 0;
    else
        return (end-start+1);
}