e.i/**
 * Description: Segment Tree 2D (Support point updates and associative operations like sum, max on a 2-D integer matrix)
 * Usage: construct O(NM),
 *  	query O( lg(N) lg(M) ),
 * 	update O( lg(N) lg(M) )
 * Source: https://github.com/dragonslayerx
 */
class SegTree2D {
    vector<vector<long long> > segtree;
    size_t n, m;

    bool OUT(int l, int r, int ql, int qr){
        return (qr < l || ql > r);
    }

    bool IN(int l, int r, int ql, int qr){
        return (ql >= l && qr <= r);
    }

    long long build_y(int node_x, int lx, int rx, int node_y, int ly, int ry, vector<vector<long long> > &array){
        if (ly == ry) {
            if (lx == rx) {
                segtree[node_x][node_y] = array[lx][ly];
            } else {
                segtree[node_x][node_y] = operation(segtree[node_x * 2 + 1][node_y], segtree[node_x * 2 + 2][node_y]);
            }
            return segtree[node_x][node_y];
        }
        int my = (ly + ry)/2;
        long long left = build_y(node_x, lx, rx, node_y * 2 + 1, ly, my, array);
        long long right = build_y(node_x, lx, rx, node_y * 2 + 2, my + 1, ry, array);
        segtree[node_x][node_y] = operation(left, right);
        return segtree[node_x][node_y];
    }

    long long build_x(int node_x, int lx, int rx, vector<vector<long long> > &array){
        if (lx != rx) {// demarcs that branching is still possible
            int mx = (lx + rx)/2;
            build_x(node_x * 2 + 1, lx, mx, array);
            build_x(node_x * 2 + 2, mx + 1, rx, array);
        }
        build_y(node_x, lx, rx, 0, 0, m - 1, array);
    }


    long long query_y(int node_x, int node_y, int ly, int ry, int qly, int qry){
        if (OUT(qly, qry, ly, ry)) {
            return def;
        } else if (IN(qly, qry, ly, ry)) {
            return segtree[node_x][node_y];
        }
        int my = (ly + ry)/2;
        long long left = query_y(node_x, node_y * 2 + 1, ly, my, qly, qry);
        long long right = query_y(node_x, node_y * 2 + 2, my + 1, ry, qly, qry);
        return operation(left, right);
    }

    long long query_x(int node_x, int lx, int rx, int qlx, int qrx, int qly, int qry){
        if (OUT(qlx, qrx, lx, rx)) {
            return def;
        } else if (IN(qlx, qrx, lx, rx)) {
            return query_y(node_x, 0, 0, m - 1, qly, qry);
        }
        int mx = (lx + rx)/2;
        long long left = query_x(node_x * 2 + 1, lx, mx, qlx, qrx, qly, qry);
        long long right = query_x(node_x * 2 + 2, mx + 1, rx, qlx, qrx, qly, qry);
        return operation(left, right);
    }

    long long update_y(int node_x, int lx, int rx, int node_y, int ly, int ry, int uy, int update_value){
        if (uy > ry || uy < ly) {
            return segtree[node_x][node_y];
        }
        if (ly == ry && ly == uy) {
            if (lx == rx) {
                segtree[node_x][node_y] = update_value;
            } else {
                segtree[node_x][node_y] = operation(segtree[node_x * 2 + 1][node_y], segtree[node_x * 2 + 2][node_y]);
            }
            return segtree[node_x][node_y];
        }
        int my = (ly + ry)/2;
        long long left = update_y(node_x, lx, rx, node_y * 2 + 1, ly, my, uy, update_value);
        long long right = update_y(node_x, lx, rx, node_y * 2 + 2, my + 1, ry, uy, update_value);
        segtree[node_x][node_y] = operation(left, right);
        return segtree[node_x][node_y];
    }

    void update_x(int node_x, int lx, int rx, int ux, int uy, long long update_value){
        if (ux > rx || ux < lx) {
            return;
        } if (lx == rx && lx == ux) {
            update_y(node_x, lx, rx, 0, 0, m - 1, uy, update_value);
            return;
        }
        int mx = (lx + rx)/2;
        update_x(node_x * 2 + 1, lx, mx, ux, uy, update_value);
        update_x(node_x * 2 + 2, mx + 1, rx, ux, uy, update_value);

        update_y(node_x, lx, rx, 0, 0, m - 1, uy, update_value);
    }


public:
    SegTree2D(int n, int m, long long def): def(def), n(n), m(m) {
         segtree.resize(4*n, vector<long long>(4*m));
    }

    SegTree2D(vector<vector<long long> > &array, int n, int m, long long def): def(def), n(n), m(m) {
        segtree.resize(4*n, vector<long long>(4*m));
        construct(array);
    }

    void construct(vector<vector<long long> > &array){
        build_x(0, 0, n - 1, array);
    }

    long long query(int qlx, int qrx, int qly, int qry){
        return query_x(0, 0, n - 1, qlx, qrx, qly, qry);
    }

    void update(int ux, int uy, long long update_value){
        update_x(0, 0, n - 1, ux, uy, update_value);
    }

#ifdef DEBUG
 void print(){
    for (int i = 0; i < 4*n; i++) {
        for (int j = 0; j < 4*m; j++)
            printf("(%d, %d)", segtree[i][j].maxx, segtree[i][j].count);
        cout << endl;
    }
 }
#endif

private:
    long long operation(long long left, long long right){
        return max(left, right);
    }
};

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t=1; t<=tc; t++) {
        printf("Case %d:\n", t);
        int n, q;
        scanf("%d%d", &n, &q);
        vector<vector<int> > array(n, vector<int> (n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &array[i][j]);
            }
        }
        SegTree2D<int> S(array, n, n, 0);
        while (q--) {
            int x, y, s;
            scanf("%d%d%d", &x, &y, &s);
            x--, y--;
            //cout << x << " " << y << " " << x+s-1 << " " << y+s-1 << endl;
            printf("%d\n", S.query(x, x+s-1, y, y+s-1));
        }
    }
}
