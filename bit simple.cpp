#define MAX 100005
long long bit[MAX];

long long query(int indx){
    long long sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= (indx & -indx);
    }
    return sum;
}

void update(int indx, int x){
    while (indx < MAX) {
        bit[indx] += x;
        indx += (indx & -indx);
    }
}
