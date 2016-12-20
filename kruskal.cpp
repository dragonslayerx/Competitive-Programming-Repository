/**
 * Description: Kruskal Algorithm (Minimum Spanning Tree). 
 * Usage: See below O((V + E) lg(E))
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
class Disjoint_Set {
	private:
		vector<int> P;
		vector<int> rank;
	public:
		Disjoint_Set(int n){
			P.resize(n);
			rank.resize(n);
			for (int i = 0; i < n; i++) {
				P[i] = i;
			}
		}
		
		void merge(int node_x, int node_y){
			int rep_x = find(node_x);
			int rep_y = find(node_y);
			if (rank[rep_x] > rank[rep_y])
				P[rep_y] = rep_x;
			else {
			        P[rep_x] = rep_y;
				if (rank[rep_x] == rank[rep_y])
					rank[rep_y]++;
			}
		}
		
		int find(int node){
			int tmp = node;
			while (node != P[node]) {
				node = P[tmp];
				tmp = node;
			}
			return node;
		}
};


struct edge {
    int a, b;
    long long w;
    int index;
};

bool compare(const edge &a, const edge &b){
    return a.w < b.w;
}

#define MAX 505
int main(){
	ios::sync_with_stdio(false);
	int v, e;
	cin >> v >> e;
	vector<edge> E(e);
	for (int i = 0; i < e; i++) {
		cin >> E[i].a;
		cin >> E[i].b;
		E[i].a-- , E[i].b--;
		cin >> E[i].w;
		E[i].index = i;
	}
	int u;
	cin >> u;
	sort(E.begin(), E.end(), compare);
	Disjoint_Set D(v);
	int selected = 0;
	cout << v-1 << endl;
	for (int i = 0; i < E.size(); i++) {
		int w = E[i].w;
		int a = E[i].a;
		int b = E[i].b;
		if (D.find(a) != D.find(b))	{
			cout << E[i].index + 1 << endl;
			selected++;
			D.merge(a, b);
		}
		if (selected == v - 1) {
			break;
		}
	}
}
