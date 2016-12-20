/**
 * Desciption: Maximum bipartite matching:  
 * Usage: max matching O(E sqrt(V))
 * Source: https://github.com/dragonslayerx 
 */

class Max_Bipartite_Match {
	vector<vector<int> > &G;
	public:

	vector<int> match, mark;
	int max_match, stamp;

	Max_Bipartite_Match(vector<vector<int> > &bipartite_graph, int v): G(bipartite_graph){
		match.resize(v);
		mark.resize(v);
		for (int i = 0; i < v; i++) {
			match[i] = -1;
			mark[i] = -1;
		}
		stamp = 0;
	}

	bool augment_path(int vertex){
		for (int i = 0; i < G[vertex].size(); i++) {
			int v = G[vertex][i];
			if (mark[v] == stamp)
				continue;
			mark[v] = stamp;
			if (match[v] == -1 || augment_path(match[v])) {
				match[v] = vertex;
				return true;
			}
		}
		return false;
	}

	int max_matching(){
		max_match = 0;
		for (int i = 0; i < G.size(); i++) {
			stamp++;
			if (augment_path(i)) max_match++;
		}
		return max_match;
	}
};

