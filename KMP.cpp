/**
 * Description: KMP algorithm (Find the longest suffix match) 
 * Usage: KMP_matcher O(T + P). See below.
 * Source: https://github.com/dragonslayerx 
 */

void Compute_Prefix_Function(string &P, vector<int> &prefix){
	int m = P.length();
	int k = 0;
	prefix[1] = 0;
	for (int i = 2; i < m; i++) {
		while (k > 0 && P[k + 1] != P[i]) k = prefix[k];
		if (P[k + 1] == P[i]) k = k + 1;
		prefix[i] = k;
	}
}

int match[100005];

int KMP_matcher(string T, string P){
	int count = 0;
	int n = T.length(), m = P.length();
	T = '#' + T, P = '#' + P;
	vector<int> prefix(m + 1);
	Compute_Prefix_Function(P, prefix);
#ifdef DEBUG
	for (int i = 1; i <= m; i++)
		cout << prefix[i] << " ";
	cout << endl;
#endif
	int k = 0;
	for (int i = 1; i <= n; i++) {
		while (k > 0 && T[i] != P[k + 1]) k = prefix[k];
		if (T[i] == P[k + 1]) k = k + 1;
		match[i] = k;
		if (k == m) {
			//Todo when a valid shift is found
			count++;
		}
	}
	return count;
}

int main(){
	cout << KMP_matcher("aabaabcabaa", "aab") << endl;
	for (int i = 1; i <= 11; i++) {
        		cout << match[i] << " ";
	}
	cout << endl;
}
