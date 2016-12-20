#include <iostream>
#include <cstdio>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class nodeType, class keyType, class valueType>
class BST {
    public:
    virtual void insert(keyType key, valueType value) = 0;
    virtual void erase(keyType key) = 0;
    virtual nodeType* getRoot() const = 0;
};

template<class nodeType, class keyType, class valueType>
class Treap: public BST<nodeType, keyType, valueType> {
    nodeType *root;
    int size;

    //Rotations
    //Right Rotation
    inline nodeType* rightRotate(nodeType * x)
    {
        nodeType *y = x->left;
        nodeType *A = y->left;
        nodeType *B = y->right;
        nodeType *C = x->right;

        x->left = B;
        x->right = C;
        y->left = A;
        y->right = x;

        x->maintainAugmentation();
        y->maintainAugmentation();
        return y;
    }

    //Left Rotation
    inline nodeType* leftRotate(nodeType * x)
    {
        nodeType *y = x->right;
        nodeType *A = x->left;
        nodeType *B = y->left;
        nodeType *C = y->right;

        x->left = A;
        x->right = B;
        y->left = x;
        y->right = C;

        x->maintainAugmentation();
        y->maintainAugmentation();
        return y;
    }

    inline nodeType* createNewNode(const keyType key, const valueType value, int priority)
    {
        nodeType *newNodePtr = new nodeType(key, value, priority);
        return newNodePtr;
    }

    nodeType* insertTree(nodeType *subTreeRoot, const keyType &key, const valueType &value, const int priority)
    {
        if (subTreeRoot == NULL) {
            return createNewNode(key, value, priority);
        }
        if (key <= subTreeRoot->key) {
            subTreeRoot->left = insertTree(subTreeRoot->left, key, value, priority);
            subTreeRoot->maintainAugmentation();
            if (subTreeRoot->left->priority < subTreeRoot->priority) {
                return rightRotate(subTreeRoot);
            }
        } else {
            subTreeRoot->right = insertTree(subTreeRoot->right, key, value, priority);
            subTreeRoot->maintainAugmentation();
            if (subTreeRoot->right->priority < subTreeRoot->priority) {
                return leftRotate(subTreeRoot);
            }
        }
        return subTreeRoot;
    }

    nodeType *merge(nodeType *T1, nodeType *T2)
    {
        if (T1 == NULL) return T2;
        if (T2 == NULL) return T1;
        if (T1->priority > T2->priority) {
            swap(T1, T2);
        }
        if (T1->key > T2->key) {
            T1->left = merge(T1->left, T2);
        } else {
            T1->right = merge(T1->right, T2);
        }
        T1->maintainAugmentation();
        return T1;
    }

    nodeType *eraseTree(nodeType *subTreeRoot, const keyType &key)
    {
        if (subTreeRoot == NULL) return NULL;
        if (key == subTreeRoot->key) {
            return merge(subTreeRoot->left, subTreeRoot->right);
        } else if (key < subTreeRoot->key) {
            subTreeRoot->left = eraseTree(subTreeRoot->left, key);
        } else {
            subTreeRoot->right = eraseTree(subTreeRoot->right, key);
        }
        subTreeRoot->maintainAugmentation();
        return subTreeRoot;
    }

    pair<nodeType *, nodeType *> split(keyType x)
    {
        nodeType *root = insertTree(root, x, 0, 0);
        return make_pair(root->left, root->right);
    }

    public:
    Treap(){
        root = NULL;
        size = 0;
    }

    void insert(keyType key, valueType value){
        size++;
        std::default_random_engine generator;
        generator.seed(time(NULL));
        uniform_int_distribution<int> distribution(1,10000);
        int priority = distribution(generator);

        //int priority = rand() % 10000 + 1;

        root = insertTree(root, key, value, priority);
    }

    void erase(keyType key){
        size--;
        root = eraseTree(root, key);
    }

    nodeType *getRoot() const{
        return root;
    }

    int getSize(){
        return size;
    }

    void inOrder(nodeType *subTreeRoot){
        if (subTreeRoot == NULL) {
            return;
        }
        inOrder(subTreeRoot->left);
        cout << subTreeRoot << " " << subTreeRoot->key << " " << subTreeRoot->value << " " << subTreeRoot->size << " " << subTreeRoot->left << " "
        << subTreeRoot->right << endl;
        inOrder(subTreeRoot->right);
    }
};

struct node {
    int key;
    long long value;
    int size;
    int priority;
    node *left, *right;
    node(int key, long long value, int priority): key(key), value(value), priority(priority){
        size = 1;
        left = right = NULL;
    }

    int getSize(node *x){
        if (x == NULL) {
            return 0;
        } else {
            return x->size;
        }
    }

    void maintainAugmentation(){
        size = getSize(this->left) + getSize(this->right) + 1;
    }
};


template <class keyType, class valueType>
class OrderStatTrees {
    private:
        BST<node, keyType, valueType> &T;
    public:
        OrderStatTrees(BST<node, keyType, valueType> &T) : T(T) {}

        inline int getSize(node *x){
            if (x == NULL) {
                return 0;
            } else {
                return x->size;
            }
        }

        int getRank(keyType key){
            node *x = T.getRoot();
            int rankElement = 0;
            while (x != NULL) {
                if (key >= x->key) {
                    rankElement += getSize(x->left) + 1;
                    x = x->right;
                } else if (key < x->key) {
                    x = x->left;
                }
            }
            return rankElement;
        }

        pair<keyType, valueType> getOrderStat(int orderStat){
            node *x = T.getRoot();
            int currentOrder = orderStat;
            while (x != NULL) {
                int k = getSize(x->left);
                ++k;
                if (k == orderStat) {
                   return make_pair(x->key, x->value);
                } else if (k < orderStat) {
                    orderStat -= k;
                    x = x->right;
                } else {
                    x = x->left;
                }
            }
        }
};

int main(){
    Treap<node, int, long long> T;
    OrderStatTrees<int, long long> O(T);
}
