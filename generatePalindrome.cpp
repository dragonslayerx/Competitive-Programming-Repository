/**
 * Description: Generate all palindromes
 * Usage: generatePalindromes
 * Source: https://github.com/dragonslayerx 
 */

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

vector<int> generatePalindromes() {
    vector<int> palindrome;
    string s;
    for (int i = 1; i <= 9; i++) {
        fillDigits(0, i-1, s, palindrome);
    }
    return palindrome;
}
