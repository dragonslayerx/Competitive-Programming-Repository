#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int SENTINEL = -1;
struct Node {
    int count;
    int link[26];
    int suffixLink;
    int fall;
    Node() {
        count=0;
        for (int i = 0; i < 26; i++) {
            link[i]=SENTINEL;
        }
        suffixLink=fall=SENTINEL;
    }
};

const int MAX_SIZE = 5000005;
Node trie[MAX_SIZE];

class AhoCorasick {
    int size;
    int root;

    int createNode() {
        return size++;
    }

public:
    AhoCorasick() {
        size=0;
        root = createNode();
    }

    void construct(char *patterns[], int m) {
        for (int k = 0; k < m; k++) {
            insert(patterns[k]);
        }
    }

    void insert(char *pattern) {
        int current = 0;
        for (int i = 0; pattern[i]; i++) {
            char c = pattern[i]-'a';
            if (trie[current].link[c] == SENTINEL) {
                trie[current].link[c] = createNode();
            }
            current = trie[current].link[c];
        }
        trie[current].count++;
    }

    void erase(char *pattern) {
        int current = 0;
        for (int i = 0; pattern[i]; i++) {
            char c = pattern[i]-'a';
            current = trie[current].link[c];
        }
        trie[current].count--;
    }

    void createSuffixLinks(int node, int parent, int i) {
        int current = trie[parent].suffixLink;
        while (current && (trie[current].link[i] == SENTINEL)) current = trie[current].suffixLink;
        if (current) {
            trie[node].suffixLink = trie[current].link[i];
        } else {
            if (!parent) trie[node].suffixLink = 0;
            else if (trie[current].link[i] == SENTINEL) {
                trie[node].suffixLink = 0;
            } else {
                trie[node].suffixLink = trie[current].link[i];
            }
        }
        for (int k = 0; k < 26; k++) {
            if (trie[node].link[k] != SENTINEL) {
                createSuffixLinks(trie[node].link[k], node, k);
            }
        }
    }

    int getFall(int node) {
        if (node == 0) return 0;
        else if (trie[node].fall != SENTINEL) return trie[node].fall;
        else if (trie[trie[node].suffixLink].count) {
            return (trie[node].fall = trie[node].suffixLink);
        } else {
            trie[node].fall = getFall(trie[node].suffixLink);
        }
    }

    void createFall() {
        for (int i = 0; i < size; i++) {
            getFall(i);
        }
    }
};

long long getCount(char *p) {
    int current = 0;
    long long count = 0;
    for (int i = 0; p[i]; i++) {
        int current = trie[current].link[p[i]-'a'];
        count += trie[current].count;
    }
    return count;
}

int main() {
    int m, q;
    scanf("%d%d", &m, &q);
    AhoCorasick A;
    for (int i = 1; i <= m; i++) {
        char s[10005];
        scanf("%s", s);
        A.insert(s);
    }
    A.createSuffixLinks(0, 0, '#');
}
