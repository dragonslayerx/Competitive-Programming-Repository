/**
 * Description: Subset generation
 * Usage: See below. O(2^n)
 * Source: https://github.com/dragonslayerx 
 */

int size = a.size();
int ways = 1 << size;
for (int i = 1; i < ways; i++) {
    vector<int> s;
    for (int j = 0; j < a.size(); j++)
        if (i & (1 << j))
            s.push_back(a[j]);
}
