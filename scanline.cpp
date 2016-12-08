void scanline(vii p, vii &interval) {
    int beg = p[0].first, last = p[0].second;
    for (int i = 1; i < m; i++) {
        if (p[i].first <= last)
            last = max(last, p[i].second);
        else {
            interval.pb(make_pair(beg, last));
            beg = p[i].first, last = p[i].second;
        }
    }
    interval.pb(make_pair(beg, last));
}
