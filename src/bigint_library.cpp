/*
 * Description: BigInt (Big Integer library)
 * Usage:  See constructors, operators like +, -, *, /, >, >=, <, <=, ==, toString
 * Note: Remove references '&' in overloaded operators for chaining operations.
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

class Bigint {

    const static int MAX = 100005;
    char x[MAX];
    int length;

    void align(char *X, int numDigits) {
        int length = strlen(X);
        for (int i = length; i < numDigits; i++) X[i]='0';
        X[numDigits]='\0';
    }

    int add(char *X, int lenX, char *Y, int lenY, int carry, char *Z) {
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = 0; i < maxLen; i++) {
            int num = (X[i]-'0') + (Y[i]-'0') + carry;
            Z[i] = num%10 + '0';
            carry = num / 10;
        }
        if (carry) Z[maxLen++] = carry+'0';
        Z[maxLen] = '\0';

        //Put everything back to original state
        X[lenX]='\0'; Y[lenY]='\0';

        return maxLen;
    }

    int substract(char *X, int lenX, char *Y, int lenY, char *Z){
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = 0; i < maxLen; i++) Y[i]=('9'-Y[i])+'0';
        int len = add(X, lenX, Y, maxLen, 1, Z);
        Z[len--] = '\0';

        //Put everything back to original state
        for (int i = 0; i < maxLen; i++) Y[i]=('9'-Y[i])+'0';
        X[lenX]='\0'; Y[lenY]='\0';

        return len;
    }

    int multiply(char *X, int lenX, char *Y, int lenY, char *Z) {
        if (lenX < lenY) {
            swap(X, Y); swap(lenX, lenY);
        }
        char result[MAX];
        int lenZ = 0;
        for (int i = 0; Y[i]; i++) {
            int digit = Y[i]-'0';
            int carry = 0, size = 0;
            for (int j = 0; X[j]; j++) {
                int val = ((X[j]-'0')*digit) + carry;
                carry = val/10;
                val %= 10;
                result[size++] = val+'0';
            }
            if (carry) result[size++] = carry + '0';
            result[size]='\0';

            for (int j = size; j >= 0; j--) result[j+i] = result[j];
            for (int j = 0; j < i; j++) result[j]='0';

            char finalResult[MAX];
            lenZ = add(result, size+i, Z, lenZ, 0, finalResult);
            strcpy(Z, finalResult);
        }
        return lenZ;
    }

    template<class T>
        int divideNmodulo(char *X, int lenX, T divisor, char *Z, T &modulo) {
            int remainder = 0;
            int size = 0;
            for(int i = lenX-1; i >= 0; i--){
                remainder *= 10;
                remainder += X[i]- '0';
                Z[size++] = remainder/divisor + '0';
                remainder %= divisor;
            }
            Z[size]='\0';
            reverse(Z, Z+size);
            modulo = remainder;
            return size;
        }

    // Relational Operations
    bool equals(char *X, int lenX, char *Y, int lenY) {
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = maxLen; i >= 0; i--) {
            if (X[i] != Y[i]) return false;
        }

        //Put everything back to original state
        X[lenX] = '\0'; Y[lenY] = '\0';

        return true;
    }

    bool greater(char *X, int lenX, char *Y, int lenY) {
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = maxLen - 1; i >= 0; i--) {
            if (X[i] > Y[i]) return true;
            if (X[i] < Y[i]) return false;
        }

        //Put everything back to original state
        X[lenX] = '\0'; Y[lenY] = '\0';

        return false;
    }

public:
    //Constructors
    Bigint() {
        x[0]='0'; x[1]='\0';
        length=1;
    }

    Bigint(string s) {
        length = s.size();
        for (int i=0, j=length-1; i < s.size(); i++, j--) x[j]=s[i];
        x[length]='\0';
    }

    Bigint(int v) {
        int size = 0;
        while (v) {
            x[size++] = v % 10 + '0';
            v /= 10;
        }
        x[size]='\0';
        length = size;
    }

    //Arithmetic Operations
    Bigint operator +(Bigint &b) {
        Bigint r;
        r.length = add(this->x, this->length, b.x, b.length, 0, r.x);
        return r;
    }

    Bigint operator *(Bigint &b) {
        Bigint r;
        r.length = multiply(this->x, this->length, b.x, b.length, r.x);
        return r;
    }

    Bigint operator -(Bigint &b) {
        Bigint r;
        r.length = substract(this->x, this->length, b.x, b.length, r.x);
        return r;
    }

    Bigint operator /(int divisor) {
        Bigint r;
        int modulo = 0;
        r.length = divideNmodulo(this->x, this->length, divisor, r.x, modulo);
        return r;
    }

    int operator %(int divisor) {
        Bigint r;
        int modulo = 0;
        r.length = divideNmodulo(this->x, this->length, divisor, r.x, modulo);
        return modulo;
    }

    // Relational Operators
    bool operator ==(Bigint &b) {
        return equals(this->x, this->length, b.x, b.length);
    }

    bool operator >(Bigint &b) {
        return greater(this->x, this->length, b.x, b.length);
    }

    bool operator >=(Bigint &b) {
        return (((*this)>b) || ((*this)==b));
    }

    bool operator <(Bigint &b) {
        return !((*this)>=b);
    }

    bool operator <=(Bigint &b) {
        return !((*this)>b);
    }


    string trimZeros(string &s) {
        int start = 0;
        while (s[start]=='0') start++;
        return s.substr(start);
    }

    string toString() {
        string s(x, x+length);
        reverse(s.begin(), s.end());
        s = trimZeros(s);
        if(s.length() == 0)
            return "0";
        return s;
    }

    friend std::ostream& operator<<(ostream &o, Bigint v) {
        o << v.toString();
        return o;
    }
};

int main() {
    Bigint A("123456789"); // Construct Bigint using string representation
    Bigint B(987654321); // Construct Bigint using integer representation
    Bigint C("456789");
    Bigint D("0");
    cout << "A * B: " << A * B << endl; // Overridden ostream
    cout << "A * B + C: " << A * B + C << endl; // Chaining operations
    cout << "(A > B): " << (A > B) << endl;
    cout << "D: " << D << endl;
    // logical operations
    if (A > B) cout << "A is greater than B" << endl;
    if (B > A) cout << "B is greater than A" << endl;
    if (A == B) cout << "A is equal to B" << endl;
}
