/**
 * Description: Find the longest common subsequence from S and T. (Non standard)
 * Usage: construct_LCS O(NM)
 */

class LCS {
	private static const int MAX = 505;
	private:
		int LCS[MAX][MAX];
		char btrack[MAX][MAX];
	public:
		string S;
		int construct_LCS(string S1, string S2){
			for (int i = 0; i <= S1.size(); i++) {
				for (int j = 0; j <= S2.size(); j++) {
					if (i == 0 || j == 0) {
						LCS[i][j] = 0;
						btrack[i][j] = ' ';
					} else {
						if (S1[i - 1] == S2[j - 1]) {
							LCS[i][j] = 1 + LCS[i - 1][j - 1];
							btrack[i][j] = '\\';
						} else {
							LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
							if (LCS[i][j] == LCS[i - 1][j]) {
								btrack[i][j] = '|';
							} else {
								btrack[i][j] = '_';
							}
						}
					}
				}
			}
			return LCS[S1.size()][S2.size()];
		}

		void get_subsequence(int i, int j){
			if (btrack[i][j] == ' ') return;
			else if (btrack[i][j] == '_') get_subsequence(i, j - 1);
			else if (btrack[i][j] == '|') get_subsequence(i - 1, j);
			else if (btrack[i][j] == '\\') {
				get_subsequence(i - 1, j - 1);
				S += S1[i - 1];
			}
		}
};


int main()
{
	int t;
	cin >> t;
	while (t--) {
		string S1, S2;
	        	cin >> S1 >> S2;
		LCS L;
		cout << L.construct_LCS(S1, S2) << endl;
	       	 L.get_subsequence(S1.size(), S2.size());
		cout << L.S;
		cout << endl;
	}
	return 0;
}
