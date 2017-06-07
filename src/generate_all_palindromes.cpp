#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Description: Generate all palindromes haing 'numDigits' digits
 * Usage: generatePalindromes
 * Source: https://github.com/dragonslayerx
 */

long long toInt(string x){
    long long sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum *= 10;
        sum += (x[i]-'0');
    }
    return sum;
}

void fillDigits(int begin, int end, string&s, vector<int> &palindrome){
    if (begin > end) {
        string t = s;
        reverse(t.begin(), t.end());
        if (s[0] != '0') {
            palindrome.push_back(toInt(s + t));
        }
    } else if (begin == end) {
        string t = s;
        reverse(t.begin(), t.end());
        for (int i = 0; i <= 9; i++) {
            s.push_back(i + '0');
            if (s[0] != '0') {
                palindrome.push_back(toInt(s + t));
            }
            s.pop_back();
        }
    } else {
        for (int i = 0; i <= 9; i++) {
            s.push_back(i + '0');
            fillDigits(begin+1, end-1, s, palindrome);
            s.pop_back();
        }
    }
}

vector<int> generatePalindromes(int numDigits) {
    vector<int> palindrome;
    string s;
    for (int i = 1; i <= numDigits; i++) {
        fillDigits(0, i-1, s, palindrome);
    }
    return palindrome;
}

int main() {
    vector<int> palindromes = generatePalindromes(3);
    for (int i = 0; i < palindromes.size(); i++) {
        cout << palindromes[i] << ", ";
    }
    cout << endl;
}
