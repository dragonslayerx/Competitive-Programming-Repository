#define MAX 2050
int edist[MAX][MAX];

class Edist {
    public:
		int solve(string &S1, string &S2){
			int last = 0;
			int current = 1;
			for (int i = 0; i <= S1.size(); i++){
				for (int j = 0; j <= S2.size(); j++){
					if (i == 0) edist[current][j] = j;
					else if (j == 0) edist[current][j] = i;
					else {
						edist[current][j] = min(edist[last][j] + 1, edist[current][j - 1] + 1);
						if (S1[i - 1] == S2[j - 1]) {
							edist[current][j] = min(edist[current][j], edist[last][j - 1]);
						} else {
							edist[current][j] = min(edist[current][j], edist[last][j - 1] + 1);
						}
					}
				}
				swap(last, current);
			}
			return edist[last][S2.size()];
		}
};
