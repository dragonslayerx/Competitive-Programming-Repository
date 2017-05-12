/**
 * Description: Converts integer to string and vice versa
 * Usage: toString (Converts an integer to its string representation)
 * 	toValue (Converts a string to its interger representation)
 * Source: https://github.com/dragonslayerx
 */

template <typename T>
string toString(T x){
    string s;
    while (x) {
        s.push_back(x % 10 + '0');
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

long long toInt(string &x){
    long long sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum *= 10;
        sum += (x[i]-'0');
    }
    return sum;
}
