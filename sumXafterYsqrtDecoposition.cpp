const int INF = 1000000050;

long long a[300005];
long long dp[550][550][550];

int ceilDiv(int x, int y) {
    return (x/y + ((x%y)? 1: 0));
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    int size = sqrt(n);
    int blocks = ceilDiv(n, size);
    for (int i = 0; i < blocks; i++) {
        int left = i * size;
        int right = min(n-1, left + size - 1);


        int sizeBlock = right-left+1;

        for (int j = 1; j <= sizeBlock; j++) {
            for (int k = right; k >= left; k--) {
                dp[i][k - left][j] += a[k];
                if (k + j <= right) {
                    dp[i][k - left][j] += dp[i][(k + j) - left][j];
                }
            }
        }
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--;
        if (y >= size) {
            long long sum = 0;
            for (int i = x; i < n; i += y) {
                sum += a[i];
            }
            printf("%lld\n", sum);
        } else {
            int leftmost = x / size;
            long long sum = dp[leftmost][x - size*leftmost][y];
            for (int i = leftmost + 1; i < blocks; i++) {
                 int left = i * size;
                 int right = min(n-1, left + size - 1);

                 int j = ceilDiv(left-x, y);

                 sum += dp[i][(x + j*y) - left][y];
            }
            printf("%lld\n", sum);
        }
    }

}
