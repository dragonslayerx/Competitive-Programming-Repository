/**
 * Description: BIT (Returns associative operation like sum for a prefix query i.e. say sum[1...i]) 
 * Usage: query O(lg(N)), update O(lg(N))
 * Note: Use 1-based indexing. 
 * Source: https://github.com/dragonslayerx 
 */

#define MAX 100005
long long bit[MAX];

long long query(int indx){
    long long sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= (indx & -indx);
    }
    return sum;
}

void update(int indx, int x){
   assert(indx != 0);
   while (indx < MAX) {
        bit[indx] += x;
        indx += (indx & -indx);
    }
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        update(i, a[i]);
    }
    int q;
    cin >> q;
    while (q--) {
        int choice;
        cin >> choice;
        if (choice) {
            int l, r;
            cin >> l >> r;
            cout << query(r) - query(l-1) << endl;
        } else {
            int p; 
            long long x;
            cin >> p >> x; 
            update(p, x);
        }
    }
}
        
