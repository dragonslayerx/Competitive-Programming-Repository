/**
 * Description: Edit distance (Find the levenstein distance between two strings)
 * Usage: solve O(NM)
 * Source: https://github.com/dragonslayerx
 */

int d[2][1005];
int solve(string &s, string &t){
    int prev = 0, current = 1;
    for (int i = 0; i <= s.size(); i++){
        for (int j = 0; j <= t.size(); j++){
            if (i == 0) d[current][j]=j;
            else if (j == 0) d[current][j]=i;
            else {
                d[current][j] = min(d[prev][j]+1, d[current][j-1]+1);
                if (s[i-1]==t[j-1]) {
                    d[current][j] = min(d[current][j], d[prev][j-1]);
                } else {
                    d[current][j] = min(d[current][j], d[prev][j-1]+1);
                }
            }
        }
        swap(prev, current);
    }
    return d[prev][t.size()];
}
