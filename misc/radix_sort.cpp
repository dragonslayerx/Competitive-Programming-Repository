#include <iostream>
#include <vector>
using namespace std;

//Valid Indexes are from [0, n-1] and value are from [0, k-1]
//Digits are taken from LSB
template<class T, size_t digits, size_t k>
class RadixSort{
    void stableCountingSort(T a[], int d, int n, int (*get)(T, int)){
        int position[k] = {};
        T b[k];
        for (int i = 0; i < n; i++) {
            ++position[get(a[i], d)];
        }
        for (int i = 1; i < k; i++) {
            position[i] += position[i-1];
        }
        for (int i = n-1; i >= 0; i--) {
            b[position[get(a[i], d)]--] = a[i];
        }
        for (int i = 0; i < n; i++) {
            a[i] = b[i+1];
        }
    }
    public:
    void sort(T a[], int n, int (*get)(T, int)){
        for (int i = 1; i <= digits; i++) {
            stableCountingSort(a, i, n, get);
        }
    };
};
