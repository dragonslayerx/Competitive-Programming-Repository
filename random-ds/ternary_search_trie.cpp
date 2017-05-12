struct node {
    bool isTerminal;
    char c;

    node *left;
    node *right;
    node *middle;
    node(char c):c(c){
        isTerminal = false;
        left = right = middle = NULL;
    }
};

template<class valueType>
struct terminalNode: public node{
    valueType value;
    terminalNode(node *terminal, char c, valueType &value): value(value), node(c){
        isTerminal = true;
        if (terminal != NULL) {
            left = terminal->left;
            right = terminal->right;
            middle = terminal->middle;
        }
    }
};

template<class valueType>
class TST {
    node *root;

    inline node* createNode(char c);
    inline node* createTerminalNode(node *terminal, char c, valueType &value);

    node* insertTST(node *subTreeRoot, const char *s, valueType &value);
    node* getTST(node *subTreeRoot, const char *s);
    void collect(node *subTreeRoot, string &s, vector<string> &stringsWithPrefix);

    public:
    TST() { root = NULL; }
    void insert(const char *s, valueType value);
    valueType& operator[](const char *s);
    vector<string> havePrefix(const char *s);
    bool contain(const char *s);
};

template<class valueType>
inline node* TST<valueType>:: createNode(char c){
    return new node(c);
}

template<class valueType>
inline node* TST<valueType>:: createTerminalNode(node *terminal, char c, valueType &value){
    return new terminalNode<valueType>(terminal, c, value);
}

template<class valueType>
node* TST<valueType>::insertTST(node *subTreeRoot, const char *s, valueType &value){
    char c = *s;
    if (s[1] == '\0') {
        return createTerminalNode(subTreeRoot, c, value);
    }

    if (subTreeRoot == NULL) {
        node *newNode = createNode(c);
        newNode->middle = insertTST(newNode->middle, s+1, value);
        return newNode;
    }

    if (subTreeRoot->c < c) {
        subTreeRoot->left = insertTST(subTreeRoot->left, s, value);
    } else if (subTreeRoot->c > c) {
        subTreeRoot->right = insertTST(subTreeRoot->right, s, value);
    } else {
        subTreeRoot->middle = insertTST(subTreeRoot->middle, s+1, value);
    }
    return subTreeRoot;
}

template<class valueType>
void TST<valueType>::insert(const char *s, valueType value){
    root = insertTST(root, s, value);
}

template<class valueType>
node* TST<valueType>::getTST(node *subTreeRoot, const char *s){
    if (subTreeRoot == NULL) {
        return NULL;
    }

    char c = *s;
    if (s[1] == '\0') {
        return subTreeRoot;
    }

    if (subTreeRoot->c < c) {
        return getTST(subTreeRoot->left, s);
    } else if (subTreeRoot->c > c) {
        return getTST(subTreeRoot->right, s);
    } else {
        return getTST(subTreeRoot->middle, s+1);
    }
}

template<class valueType>
valueType& TST<valueType>::operator [](const char *s){
    return ((terminalNode<valueType> *) getTST(root, s))->value;
}

template<class valueType>
bool TST<valueType>::contain(const char *s){
    node *x = getTST(root, s);
    if (x == NULL) {
        return false;
    } else {
        if (x->isTerminal == true) {
            return true;
        } else {
            return false;
        }
    }
}

template<class valueType>
vector<string> TST<valueType>::havePrefix(const char *s){
    vector<string> stringsWithPrefix;
    node *x = getTST(root, s);
    if (x == NULL) {
        return stringsWithPrefix;
    }
    string initialString(s);
    if (x->isTerminal == true) {
        stringsWithPrefix.push_back(initialString);
    }
    collect(x->middle, initialString, stringsWithPrefix);
    return stringsWithPrefix;
}

template<class valueType>
void TST<valueType>::collect(node *subTreeRoot, string &s, vector<string> &stringsWithPrefix){
    if (subTreeRoot == NULL) {
        return;
    } else {
        collect(subTreeRoot->left, s, stringsWithPrefix);
        collect(subTreeRoot->right, s, stringsWithPrefix);
        s.push_back(subTreeRoot->c);
        if (subTreeRoot->isTerminal == true) {
            stringsWithPrefix.push_back(s);
        }
        collect(subTreeRoot->middle, s, stringsWithPrefix);
        s.pop_back();
    }
}


int main(){
    TST<int> T;
    T.insert("hello", 3);
    T.insert("hell", 1);
    T.insert("helsinki", 1);
    T.insert("books", 1);
    T.insert("book worm", 1);
    vector<string> searchSuggestions = T.havePrefix("hel");
    vector< pair<int, string> > rankings;
    for (string s : searchSuggestions) {
        rankings.push_back({T[s.c_str()], s});
    }
    sort(rankings.rbegin(), rankings.rend());
    cerr << rankings << endl;
}
