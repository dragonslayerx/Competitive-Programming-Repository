/**
 * Description: Disjoint Set. 
 * Usage: See below O(lg(N))
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
			if (rank[rep_x] > rank[rep_y]) {
				P[rep_y] = rep_x;
			} else {
				P[rep_x] = rep_y;
				if (rank[rep_x] == rank[rep_y]){
					rank[rep_y]++;
				}
			}
		}
		
		int find(int node){
			while (node != P[node]) {
				node = P[node];
			}
			return node;
		}
};
