/**
 * Description: Quick Select (Find Kth order statistics)
 * Usage: quick_select O(N)
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int randomised_partition(vector<int> &A, int p, int q){
	int random = (rand() % (q-p+1)) + p;
	swap(A[q], A[random]);
	int ptr = p;
	for (int i = p; i <= q; i++) {
		if (A[i] <= A[q]) {
			swap(A[i], A[ptr++]);
		}
	}
	return ptr;
}

int quick_select(vector<int> &A, int p, int q, int k){
	if (p == q) return A[p];
	int pivot = randomised_partition(A, p, q);
	if (pivot == k)
		return A[pivot];
	else if (k < pivot) {
		return quick_select(A, p, pivot - 1, k);
	} else {
		return quick_select(A, pivot + 1, q, k);
	}
}

int main(){
	srand(time(NULL));
	int t;
	cin >> t;
	while (t--) {
		int n;
		scanf("%d", &n);
		vector<int> A(n);
		for (int i = 0; i < n; i++) scanf("%d", &A[i]);
		int q;
		cin >> q;
		while (q--) {
			int k;
			cin >> k;
			cout << quick_select(A, 0, n - 1, k) << endl;
		}
	}
}
