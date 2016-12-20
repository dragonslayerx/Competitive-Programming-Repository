/**
 * Description: Suffix Array (Manber's Algorithm)
 * Usage: See https://www.codechef.com/viewsolution/9631939 for detailed usage. 
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 100005;
const int MOD = 1000000000+7;
const int INF = 1000000000;
 
//Valid Indexes are from [0, n-1] and value are from [0, k-1]
//Digits are numbered from LSD
template<class T, size_t digits, size_t k>
class RadixSort
{
    static void stableCountingSort(T a[], int d, int n, int (*get)(T, int))
    {
        int position[k] = {};
        T *b = new T[k];
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
        delete(b);
    }
    public:
    static void sort(T a[], int n, int (*get)(T, int))
    {
        for (int i = 1; i <= digits; i++) {
            stableCountingSort(a, i, n, get);
        }
    };
};
 
struct Pair {
    int first;
    int second;
    int index;
    Pair(){}
    Pair(int first, int second, int index): first(first), second(second), index(index) {}
 
    bool operator ==(const Pair& p)
    {
        return ((first == p.first) && (second == p.second))? true: false;
    }
};
 
int get(Pair p, int d)
{
    return (d == 1)? p.second: p.first;
}
 
 
//Output Arrays
int P[25][100100];
int suffixArray[100100];
Pair orderedPair[100100];
 
class SuffixArray {
    static const int MAXSIZE = 100100;
 
    char s[MAXSIZE];
    int n;
    int lgn;
 
 
    int calculateLgN(int n);
 
    public:
    SuffixArray() {
        initialize();
    }
 
    SuffixArray(string s)
    {
        initialize();
        setString(s);
        createSuffixArray();
    }
    SuffixArray(char* s)
    {
        initialize();
        setString(s);
        createSuffixArray();
    }
 
    void initialize();
    void setString(char *s);
    void setString(const string &s);
    void createSuffixArray();
    inline int operator[] (int index) const;
    int getLCP(int a, int b) const;
    inline int getPosition(int index) const;
};
 
void SuffixArray::initialize()
{
    n = 0;
}
 
void SuffixArray::setString(char *inputString)
{
    strcpy(s, inputString);
    n = strlen(s);
}
 
void SuffixArray::setString(const string &inputString)
{
    int i = 0;
    for (; inputString[i]; i++) {
        s[i] = inputString[i];
    }
    s[i] = '\0';
    n = i;
}
 
int SuffixArray::calculateLgN(int n)
{
    int i = 0;
    int l = 1;
    while (l <= n) {
        l <<= 1;
        i++;
    }
    i--;
    return i;
}
 
void SuffixArray::createSuffixArray()
{
    //Assign Rank to every Character
    {
        bool isPresent[128] = {false};
        int rankCharacter[128];
        for (int i = 0; i < n; i++) {
            isPresent[s[i]] = true;
        }
        int currentRank = 1;
        for (int i = 0; i < 128; i++) {
            if (isPresent[i]) {
                rankCharacter[i] = currentRank++;
            }
        }
        for (int i = 0; i < n; i++) {
            P[0][i] = rankCharacter[s[i]];
        }
    }
    lgn = calculateLgN(n);
    int length = 1;
    lgn++;
    for (int k = 1; k <= lgn; k++) {
        for (int i = 0; i < n; i++) {
            if (i + length < n)
                orderedPair[i] = Pair(P[k-1][i], P[k-1][i+length], i);
            else
                orderedPair[i] = Pair(P[k-1][i], 0, i);
        }
 
        RadixSort<Pair,2,MAXSIZE> R;
        R.sort(orderedPair, n, get);
 
        int rank = 1;
        for (int i = 0; i < n; i++) {
            if (i > 0 && !(orderedPair[i] == orderedPair[i-1])) {
                ++rank;
            }
            P[k][orderedPair[i].index] = rank;
        }
        length <<= 1;
    }
 
    for (int i = 0; i < n; i++) {
        suffixArray[P[lgn][i]-1] = i;
    }
};
 
inline int SuffixArray::operator [](int index) const
{
    return suffixArray[index];
}
 
inline int SuffixArray::getPosition(int index) const
{
    return P[lgn][index];
}
 
int SuffixArray::getLCP(int a, int b) const
{
    int lps = 0;
    int k = lgn;
    int length = 1 << k;
    for (int k = lgn; k >= 0; k--) {
        if (P[k][a] == P[k][b]) {
            lps += length;
            a += length;
            b += length;
        }
        if (a >= n || b >= n) break;
        length >>= 1;
    }
    return lps;
}