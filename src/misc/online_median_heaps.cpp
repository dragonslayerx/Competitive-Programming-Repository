#include <iostream>
#include <queue>
#include <cstdio>
#include <climits>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    priority_queue<int> firstHalf;
    priority_queue<int, vector<int>, greater<int> > secondHalf;
    int elementsSoFar = 0;
    firstHalf.push(-1);
    secondHalf.push(INT_MAX);

    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        ++elementsSoFar;

            if (k <= firstHalf.top()) {
                firstHalf.push(k);
            } else {
                secondHalf.push(k);
            }
            if (elementsSoFar & 1) {
                int median;
                if (firstHalf.size() > secondHalf.size()) {
                    median = firstHalf.top();
                } else {
                    median = secondHalf.top();
                }
                printf("%.1f\n", (float)median);
            } else {
                if (firstHalf.size() > secondHalf.size()) {
                    int maxFirstHalf = firstHalf.top();
                    firstHalf.pop();
                    secondHalf.push(maxFirstHalf);
                } else if (firstHalf.size() < secondHalf.size()){
                    int minSecondHalf = secondHalf.top();
                    secondHalf.pop();
                    firstHalf.push(minSecondHalf);
                }
                int lowerMedian = firstHalf.top();
                int upperMedian = secondHalf.top();
                printf("%.1f\n", (float)(lowerMedian + upperMedian) / 2);
            }
    }
}
