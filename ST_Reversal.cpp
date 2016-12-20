/**
 * Description: Dynamic Segment tree (Support for inbetween insertion and array reversal)   
 * Usage: See below. insert O(lg(N)), reverse O(lg(N)), get O(lg(N))
 * Note: Override augment function appropriately for supporting distinct aggregate operation.
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 100005;
const int MOD = 1000000000+7;
const int INF = 1000000000;

struct node {
    int val, cnt[15];
    int size, pr;
    bool rev;
    node *l, *r;
    node(int val, int pr) {
        this->val = val;
        this->pr = pr;
        this->l = this->r = NULL;
        this->rev = false;
        this->size = 1;
        memset(cnt, 0, sizeof(cnt));
        this->cnt[val]++;
    }

    friend ostream& operator <<(ostream &o, node &x) {
        o << "{ x= " << &x << ", val=" << x.val << ", size=" << x.size << ", rev=" << x.rev << ", pr=" << x.pr;
        o << "l = " << x.l << " " << ", r = " << x.r << " ";
        o << " [";
        for (int i = 0; i < 15; i++) {
            o << x.cnt[i] << " ";
        }
        o << "] }";
    }
};


class Treap {
    node *root;

    int getSize(node *p) {
        if (p == NULL) return 0;
        else return p->size;
    }

    int getCnt(node *p, int i) {
        if (p == NULL) return 0;
        else return p->cnt[i];
    }

    void augment(node *p) {
        if (p==NULL) return;
        else {
            if (p->rev) {
                if (p->l) p->l->rev ^= 1;
                if (p->r) p->r->rev ^= 1;
                swap(p->l, p->r);
                p->rev=false;
            }
            p->size = getSize(p->l)+getSize(p->r)+1;
            // Change here for support for a different augment function
	for (int i = 0; i < 15; i++) p->cnt[i] = getCnt(p->l, i)+getCnt(p->r, i);
            p->cnt[p->val]++;
	//
        }
    }

    node* rightRotate(node* x){
        node *y = x->l;
        node *B = y->r;

        x->l = B;
        y->r = x;

        augment(x); augment(y);
        return y;
    }

    node* leftRotate(node* x){
        node *y = x->r;
        node *B = y->l;

        x->r = B;
        y->l = x;

        augment(x); augment(y);
        return y;
    }

    node* insert(node *p, int pos, int x, int pr) {
        if (p==NULL) {
            return new node(x, pr);
        } else {
            augment(p);
            int sz = getSize(p->l);
            if (pos <= sz) {
                p->l = insert(p->l, pos, x, pr);
                augment(p);
                node* l = p->l;
                if (l->pr < p->pr) {
                    return rightRotate(p);
                }
            } else {
                p->r = insert(p->r, pos-sz-1, x, pr);
                augment(p);
                node* r = p->r;
                if (r->pr < p->pr) {
                    return leftRotate(p);
                }
            }
            return p;
        }
    }

    node* merge(node *lt, node *rt) {
        if (lt==NULL) return rt;
        else if (rt==NULL) return lt;
        else {
            if (lt->pr < rt->pr) {
                augment(lt);
                lt->r = merge(lt->r, rt);
                augment(lt);
                return lt;
            } else {
                augment(rt);
                rt->l = merge(lt, rt->l);
                augment(rt);
                return rt;
            }
        }
    }

    pair<node*, node*> split(node* p, int pos) {
        node* tmpRt = insert(p, pos, 0, -1);
        return make_pair(tmpRt->l, tmpRt->r);
    }

    void inorder(node *p, ostream &o) {
        if (p==NULL) return;
        else {
            inorder(p->l, o);
            o << *p << endl;
            inorder(p->r, o);
        }
    }

public:
    Treap(){
        srand(time(NULL));
        root=NULL;
    }

    void insert(int pos, int x) {
        root = insert(root, pos, x, rand());
    }

    void reverse(int l, int r) {
        pair<node*, node*> p = split(root, l);
        pair<node*, node*> q = split(p.second, r-l+1);
        (q.first)->rev ^= 1;
        root = merge(merge(p.first, q.first), q.second);
    }

    void get(int l, int r, int cnt[]) {
        pair<node*, node*> p = split(root, l);
        pair<node*, node*> q = split(p.second, r-l+1);
        for (int i = 0; i < 15; i++) {
            cnt[i] = (q.first)->cnt[i];
        }
        root = merge(merge(p.first, q.first), q.second);
    }

    void inorder(ostream &o) {
        inorder(root, o);
    }

    friend std::ostream& operator<<(ostream &o, Treap D) {
        D.inorder(o);
        return o;
    }

};
