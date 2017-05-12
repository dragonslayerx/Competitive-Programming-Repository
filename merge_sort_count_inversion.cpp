/**
 * Description: Merge sort (Find inversions in an array)
 * Usage: merge_sort O(N lg(N)). See below
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX 100050

int merge(int a[], int b[], int l, int r, int mid)
{
    int lptr = l;
    int rptr = mid+1;
    int current_ptr = 0;
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (lptr > mid) {
            b[current_ptr++] = a[rptr++];
            count += (mid - lptr + 1);
        } else if (rptr > r) {
            b[current_ptr++] = a[lptr++];
        } else {
            if (a[lptr] < a[rptr]) {
                b[current_ptr++] = a[lptr++];
            } else {
                b[current_ptr++] = a[rptr++];
                count += (mid - lptr + 1);
            }
        }
    }
    for (int i = l, j = 0; i <= r; i++, j++) {
        a[i] = b[j];
    }
    return count;
}

int merge_sort(int a[], int b[], int l, int r)
{
    if (l == r) {
        return 0;
    }
    int mid = (l + r)/2;
    int inversion_left = merge_sort(a, b, l, mid);
    int inversion_right = merge_sort(a, b, mid+1, r);
    int inversion_count = merge(a, b, l, r, mid);
    return inversion_left + inversion_right + inversion_count;
}

int main()
{
    int a[MAX], b[MAX];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        //a[i] = rand() % 32;
    }
    cout << merge_sort(a, b, 0, n-1) << endl ;
    cout << endl;
}
