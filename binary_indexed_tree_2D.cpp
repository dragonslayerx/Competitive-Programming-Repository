/**
 * Bit 2D: Support point updates and associative operations like sum over a 2-D matrix
 * Complexity: lg(n) per query and update 
 * Usage: query and update. Indexes should be 1-based 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

#define MAX 1010

long long bit[MAX][MAX];
bool grid[MAX][MAX];

long long queryx(int x, int y){
    long long sum = 0;
    while (y) {
        sum += bit[x][y];
        y -= y & -y;
    }
    return sum;
}

long long query(int x, int y){
    long long sum = 0;
    while (x) {
        sum += queryx(x, y);
        x -= x & -x;
    }
    return sum;
}

void updatex(int x, int y, int v){
    while (y < MAX) {
        bit[x][y] += v;
        y += y & -y;
    }
}

void update(int x, int y, int v){
    while (x < MAX) {
        updatex(x, y, v);
        x += x & -x;
    }
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++) {
        memset(bit, 0, sizeof(bit));
        memset(grid, 0, sizeof(grid));

        printf("Case %d:\n", t);
        int q;
        scanf("%d", &q);
        while (q--) {
            int ch;
            scanf("%d", &ch);
            if (ch == 0) {
                int x, y;
                scanf("%d%d", &x, &y);
                x++, y++;
                if (!grid[x][y]) {
                    update(x, y, 1);
                    grid[x][y] = 1;
                }
            } else if (ch == 1) {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                x1++, y1++, x2++, y2++;
                printf("%d\n", query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1));
            }
        }
    }
}
