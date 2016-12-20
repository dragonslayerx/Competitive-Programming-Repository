/**
 * Description: Z function
 * Usage: calculateZfunc O(|S|)
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <vector>
using namespace std;

class Z {
    public:
    static vector<int> calculateZfunc(const string &s)
    {
        int L = 0, R = 0;
        int n = s.size();
        vector<int> Zf(n);
        for (int i = 1; i < n; i++){
            if (R < i) {
                int j, k;
                for (j = i, k = 0; j < n && (s[j] == s[k]); j++, k++);
                L = i;
                R = j-1;
                Zf[i] = R - i + 1;
            } else {
                int p = i - L;
                if (Zf[p] >= R-i+1) {
                    int j, k;
                    for (j = R+1, k = R-i+1; j < n && (s[j] == s[k]); j++, k++)
                    L = i;
                    R = j-1;
                    Zf[i] = R - i + 1;
                } else {
                    Zf[i] = Zf[p];
                }
            }

        }
        return Zf;
    }
};

int main()
{
    string s = "ddcdddc";
    cerr << s << endl;
    vector<int> Zf = Z::calculateZfunc(s);
    for (int i = 0; i < Zf.size(); i++) {
        cout << Zf[i] << " ";
    }
    cout << endl;
}
