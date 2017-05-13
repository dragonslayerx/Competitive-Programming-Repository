/**
 * Max Xor queries : Find maximum xor of an integer with a set of integers
 * Usage: insert O(lg(N)), erase O(lg(N)), maximize O(lg(N))
 * Assumption: range of elements should be less than 2^45
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
using namespace std;

int size=0;
struct node {
    node *left;
    node *right;
    int count;
    node() {
        left = right = NULL;
        count = 0;
    }
} pool[5000005];

class Trie {
    #define MAXB 45
    node *root;
    Trie() {
        root = &pool[size++];
    }

    node* create_new_node(){
        node *t = &pool[size++];
        return t;
    }

    void tostring(char *s, long long x){
        int i;
        long long j;
        for (j = 1LL << MAXB, i = 0; j > 0; j >>= 1, i++) {
            s[i] = ((x & j) != 0) + '0';
        }
        s[i] = '\0';
    }

    void insert_trie(char *s){
        node *t = root;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '0') {
                if (t->left == NULL) {
                    t->left = create_new_node();
                }
                t = t->left;
            } else {
                if (t->right == NULL) {
                    t->right = create_new_node();
                }
                t = t->right;
            }
            t->count++;
        }
    }

    void erase_trie(char *s){
        node *t = root;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '0') {
                t = t->left;
            } else {
                t = t->right;
            }
            t->count--;
        }
    }

public:
    long long maximize(long long x){
        char s[50];
        tostring(s, x);
        long long answer = 0;
        node *t = root;
        for (int i = 0; s[i]; i++) {
            answer <<= 1;
            if (s[i] == '0') {
                if (t->right == NULL || (t->right->count==0)) {
                    t = t->left;
                } else {
                    t = t->right;
                    answer |= 1;
                }
            } else {
                if (t->left == NULL || (t->left->count==0)) {
                    t = t->right;
                } else {
                    t = t->left;
                    answer |= 1;
                }
            }
        }
        return answer;
    }

    void insert(long long x){
        char s[50];
        tostring(s, x);
        insert_trie(s);
    }

    void erase(long long x) {
        char s[50];
        tostring(s, x);
        erase_trie(s);
    }
};

int main() {
}
