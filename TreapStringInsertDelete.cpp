/**
 * Description: Dynamic strings (Support for insert, delete of substring at arbitary position in a string)
 * Usage: insert_substring, remove_substring, get_substring O(lg(N)) per character 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct {
    int tree_size; // Size of the subtree rooted at node
    int p; // Priority of node
    char val; // Value of node
    node *left, *right;
};

class Treap {
    node *root;

    int get_size(node *subtree_root){
        if (subtree_root == NULL) return 0;
        else return subtree_root->tree_size;
    }

    node* left_rotate(node *y, node *x){
        int a_size = get_size(y->left);
        int b_size = get_size(x->left);
        int c_size = get_size(x->right);

        x->tree_size = c_size + a_size + b_size + 2;
        y->tree_size = a_size + b_size + 1;

        node *b = x->left;
        x->left = y;
        y->right = b;
        return x;
    }

    node* right_rotate(node *x, node *y){
        int a_size = get_size(y->left);
        int b_size = get_size(y->right);
        int c_size = get_size(x->right);

        y->tree_size = c_size + a_size + b_size + 2;
        x->tree_size = b_size + c_size + 1;

        node *b = y->right;
        y->right = x;
        x->left = b;
        return y;
    }

    node *merge(node *left_treap, node *right_treap){
        if (left_treap == NULL) return right_treap;
        if (right_treap== NULL) return left_treap;
        if (left_treap->p < right_treap->p) {
            left_treap->tree_size += get_size(right_treap);
            left_treap->right = merge(left_treap->right, right_treap);
            return left_treap;
        } else {
            right_treap->tree_size += get_size(left_treap);
            right_treap->left = merge(right_treap->left, left_treap);
            return right_treap;
        }
    }

    node* _insert(node *subtree_root, int pos, node *new_node)
    {
        if (subtree_root == NULL) return new_node;
        subtree_root->tree_size += 1;
        if (pos <= get_size(subtree_root->left)) {
            subtree_root->left = _insert(subtree_root->left, pos, new_node);
            if (subtree_root->p > subtree_root->left->p) {
                return right_rotate(subtree_root, subtree_root->left);
            }
        } else {
            pos -= get_size(subtree_root->left) + 1;
            subtree_root->right = _insert(subtree_root->right, pos, new_node);
            if (subtree_root->p > subtree_root->right->p) {
                return left_rotate(subtree_root, subtree_root->right);
            }
        }
        return subtree_root;
    }

    char _get_node(node *subtree_root, int pos)
    {
        if (pos >= subtree_root->tree_size) return '#';
        if (pos == get_size(subtree_root->left))
            return subtree_root->val;
        if (pos < get_size(subtree_root->left)) {
            return _get_node(subtree_root->left, pos);
        } else {
            pos = pos - get_size(subtree_root->left) - 1;
            return _get_node(subtree_root->right, pos);
        }
    }

    node* _erase(node *subtree_root, int pos){
        if (pos >= subtree_root->tree_size) return subtree_root;
        if (pos == get_size(subtree_root->left)) {
            return merge(subtree_root->left, subtree_root->right);
        }
        subtree_root->tree_size -= 1;
        if (pos < get_size(subtree_root->left)) {
            subtree_root->left = _erase(subtree_root->left, pos);
        } else {
            pos = pos - get_size(subtree_root->left) - 1;
            subtree_root->right = _erase(subtree_root->right, pos);
        }
        return subtree_root;
    }

    pair<node*, node*> split(node *subtree_root, int pos){
        node* new_node = (node*) malloc(sizeof(node));
        new_node->val = '#';
        new_node->p = -1;
        new_node->left = new_node->right = NULL;
        root = _insert(subtree_root, pos, new_node);
        return make_pair(root->left, root->right);
    }

    int get_random(){
        return rand() * rand();
    }

    void _inorder(node *subtree_root){
        if (subtree_root == NULL) return;
        _inorder(subtree_root->left);
        cout << subtree_root->val;
        _inorder(subtree_root->right);
    }


    public:
    Treap(){
        root = NULL;
    }

    void insert(int pos, char val){
        node *new_node = (node*)malloc(sizeof(node));
        new_node->val = val;
        new_node->tree_size = 1;
        new_node->p = get_random();
        new_node->left = new_node->right = NULL;
        root = _insert(root, pos, new_node);
    }

    void erase(int pos){
        root = _erase(root, pos);
    }

    void remove_substring(int pos, int length){
        pair<node*, node*> A = split(root, pos);
        pair<node*, node*> B = split(A.second, length);
        root = merge(A.first, B.second);
    }

    void insert_substring(int pos, char *s){
        int n = strlen(s);
        for (int i = 0; i < n; i++) {
            insert(pos, s[i]);
            pos++;
        }
    }

    string get_substring(int pos, int len){
        string tmp;
        for (int i = pos; i < pos+len; i++) {
            tmp.push_back(get_node(i));
        }
        return tmp;
    }

    char get_node(int pos){
        return _get_node(root, pos);
    }

    void inorder(){
        _inorder(root);
    }
};

char a[300005];

int main()
{
    Treap T;
    int q;
    scanf("%d", &q);
    while (q--) {
        int pos;
        char choice[5];
        scanf("%s%d", choice, &pos);
        if (choice[0] == '+') {
            scanf("%s", a);
            T.insert_substring(pos, a);
        } else {
            pos--;
            int len;
            scanf("%d", &len);
            printf("%s\n", T.get_substring(pos, len).c_str());
        }
    }
}
