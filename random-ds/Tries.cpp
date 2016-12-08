#include <iostream>
#include <string>
using namespace std;

struct node {
    static const int MAX_SIZE = 128;
    bool isTerminal;
    node *p[MAX_SIZE];
    node(){
        isTerminal = false;
        for (int i = 0; i < MAX_SIZE; i++) {
            p[i] = NULL;
        }
    }
};

template<class valueType>
struct terminalNode: public node {
    valueType value;
    terminalNode (node *terminal, valueType &value): value(value){
        isTerminal = true;
        if (terminal != NULL) {
            for (int i = 0; i < MAX_SIZE; i++) {
                p[i] = terminal->p[i];
            }
        }
    }
};


template<class valueType>
class Trie {
    node *root;

    node* createNode() {return new node;}

    node *createTerminalNode(node *terminal, valueType &value){
        return new terminalNode<valueType>(terminal, value);
    }

    void insertTrie(const char *s, valueType &value);
    node* eraseTrie(const char *s);
    terminalNode<valueType>* findTrie(const char *s);

    public:
    Trie() {
        root = createNode();
    }

    void insert(char *s, valueType value);
    void erase(char *s);

    void insert(string s, valueType value);
    void erase(string s);

    bool contain(string &s);
    bool contain(char *s);

    valueType& operator[](string &s);
    valueType& operator[](char *s);
};

template<class valueType>
void Trie<valueType>::insertTrie(const char *s, valueType &value){
    node *x = root;
    for (int i = 0; ;i++) {
        if (s[i+1] == '\0') {
            node *oldTerminal = x->p[s[i]];
            x->p[s[i]] = createTerminalNode(x->p[s[i]], value);
            if (oldTerminal != NULL) {
                delete oldTerminal;
            }
            break;
        }

        if (x->p[s[i]] == NULL) {
            x->p[s[i]] = createNode();
        }
        x = x->p[s[i]];
    }
}

template<class valueType>
void Trie<valueType>::insert(char s[], valueType value){
    insertTrie(s, value);
}

template<class valueType>
void Trie<valueType>::insert(string s, valueType value){
    insertTrie(s.c_str(), value);
}

template<class valueType>
terminalNode<valueType>* Trie<valueType>::findTrie(const char *s){
        node *x = root;
        for (int i = 0; s[i]; i++) {
            if (x != NULL) {
                x = x->p[s[i]];
            }
            if (x == NULL) {
                return NULL;
            }
        }
        if (x->isTerminal == true) {
            return ((terminalNode<valueType> *) x);
        } else {
            return NULL;
        }
}

template<class valueType>
bool Trie<valueType>::contain(char *s){
    return findTrie != NULL;
}

template<class valueType>
bool Trie<valueType>::contain(string &s){
    return findTrie != NULL;
}

template<class valueType>
valueType& Trie<valueType>::operator[] (char *s){
    return findTrie(s)->value;
}

template<class valueType>
valueType& Trie<valueType>::operator[] (string &s){
    return findTrie(s.c_str())->value;
}

int main()
{
    Trie<int> T;
}
