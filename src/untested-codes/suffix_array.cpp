#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cmath>
#include <queue>
using namespace std;

#define trace(x) {cerr << #x << "=" << x <<endl;}
#define trace2(x, y) {cerr << #x << "=" << x << " " << #y << "=" << y <<endl;}
template <typename T> ostream& operator<<(ostream& os, const vector<T> &p){os << "[ "; for (T x: p) os << x << " "; os << "]" << endl; return os;}
template <typename T> ostream& operator<<(ostream& os, const set<T> &p){os << "{ "; for (T x: p) os << x << " "; os << "}" << endl; return os;}
template <typename Tk, typename Tv> ostream& operator<<(ostream& os, const map<Tk, Tv> &p){os << "{ "; for (pair<Tk, Tv> x: p) os << x << " "; os << "}" << endl; return os;}
template <typename Tk, typename Tv> ostream& operator<<(ostream& os, const pair<Tk, Tv> &p){os << "{" << p.first << ',' << p.second << "}";return os;}

typedef long long ll;

const int MOD = 1000000000+7;
const int INF = 1000000000+5;
const int MAX = 200005;

int lgn=0;
int sa[25][1000005];
int rankSuf[1000005];
void constructSA(const char s[], int n) {
    cout << s << endl;
    map<int,int> rank;
    for (int i=0; i<n; i++) rank[s[i]]=0;
    int ctr=1;
    for (auto it=rank.begin(); it!=rank.end(); it++) it->second=ctr++;
    int p2=1;
    while (p2<=n) {p2<<=1; lgn++;}
    for (int i=0; i<n; i++) sa[0][i]=rank[s[i]];
    for (int i=1, l=1; i<=lgn; i++, l<<=1) {
        vector<pair<pair<int,int>,int>> rank;
        for (int j=0; j<n; j++) {
            pair<pair<int,int>, int> r = {{sa[i-1][j], ((j+l<n)?sa[i-1][j+l]:0)}, j};
            rank.push_back(r);
        }
        sort(rank.begin(), rank.end());
        for (int j=0, ctr=1; j<n; j++) {
            if (j>0 && (rank[j].first!=rank[j-1].first)) ctr++;
            sa[i][rank[j].second]=ctr;
        }
    }
    for (int i=0; i<n; i++) rankSuf[sa[lgn][i]-1]=i;
}

int getLCP(int p, int q) {
    int l=0;
    for (int i=lgn, len=(1<<lgn); i>=0; i--, len>>=1) {
        if (sa[i][p]==sa[i][q]) {
            l+=len; p+=len, q+=len;
        }
    }
    return l;
}

int lcp[25][1000005];
void processlcp(int n) {
    int N=n-1;
    for (int i=0; i<N; i++) lcp[0][i]=getLCP(rankSuf[i], rankSuf[i+1]);
    int lgn=0, p2=1;
    while (p2<=N) {p2<<=1; lgn++;}
    for (int i=1,l=1; i<=lgn; i++,l<<=1) {
        for (int j=0; j<n; j++) {
            lcp[i][j] = min(lcp[i-1][j], (j+l<N)?lcp[i-1][j+l]:INF);
        }
    }
}

int frameSize[MAX];
int preprocess(){
    for(int i=0, pow2=1; pow2 < MAX;  pow2*=2, i++) frameSize[pow2]=i;
    for(int i=3;i<MAX;i++) {
        if(frameSize[i]==0) {
            frameSize[i]=frameSize[i-1];
        }
    }
}

inline int query(int l, int r){
    int p = frameSize[r-l+1];
    return min(lcp[p][l], lcp[p][r-(1<<p)+1]);
}

int main() {
    string s = "bananan";
    int n = s.size();
    constructSA(s.c_str(), n);
    cout << "---" << endl;
    for (int i = 0; i < n; i++) cout << rankSuf[i] << " "; cout << endl;
    for (int i = 0; i < n; i++) cout << s.substr(rankSuf[i]) << endl;

    cout << getLCP(1, 3) << endl;

    processlcp(n);
    preprocess();
    cout << query(0, 0) << endl;
}
