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

//----------------------
// inputs
string s;
int n;

const int MAX = 1000005;
const int INF = 1000000000+5;

int lgn=0;
int sa[25][MAX];
int rankSuf[MAX];
void constructSA() {
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
        if (p>=n || q>=n) break;
    }
    return l;
}

int lcp[25][MAX];
void processlcp() {
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
int processFrameSize(){
    for(int i=0, pow2=1; pow2<MAX;  pow2*=2, i++) frameSize[pow2]=i;
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
//---------------------

int main() {
    s = "banana";
    n = s.size();

    constructSA();
    for (int i = 0; i < n; i++) cout << s.substr(rankSuf[i]) << endl;

    cout << getLCP(1, 3) << endl;

    processlcp();
    processFrameSize();

    cout << query(1, 1) << endl;
}
