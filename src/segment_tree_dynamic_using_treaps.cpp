/**
 * Description: Dynamic segment tree (Perform associative operations on dynamic array. Support insertion, deletion of elements at any index, point updates)
 * Usage: insert O(lg(N)), erase O(lg(N)), update O(lg(N)), query O(lg(N)) 
 * Source: https://github.com/dragonslayerx 
 * Note: Override augment function for supporting other associative operations
 */

template<typename Tv>
struct node {
    Tv val, mval;
    int size, pr;
    node *l, *r;
    node(Tv val, int pr) {
        this->val = this->mval = val;
        this->size = 1;
        this->pr = pr;
        this->l = this->r = NULL;
    }
};
 
template <typename Tv>
ostream& operator <<(ostream &o, node<Tv> &x) {
    o << "{val=" << x.val << ", mval=" << x.mval << ", size=" << x.size << ", pr=" << x.pr << "}";
    return o;
}
 
template<typename Tv>
class DST {
    node<Tv> *root;
 
    int getSize(node<Tv> *p) {
        if (p == NULL) return 0;
        else return p->size;
    }
 
    Tv getVal(node<Tv> *p) {
        if (p==NULL) return 0;
        else return p->mval;
    }
 
    void augment(node<Tv> *p) {
        if (p==NULL) return;
        else {
            p->size = getSize(p->l) + getSize(p->r) + 1;
            // Change here 
            p->mval = p->val + getVal(p->l) + getVal(p->r);
        }
    }
 
    node<Tv>* rightRotate(node<Tv>* x){
        node<Tv> *y = x->l;
        node<Tv> *B = y->r;
 
        x->l = B;
        y->r = x;
 
        augment(x); augment(y);
        return y;
    }
 
    node<Tv>* leftRotate(node<Tv>* x){
        node<Tv> *y = x->r;
        node<Tv> *B = y->l;
 
        x->r = B;
        y->l = x;
 
        augment(x); augment(y);
        return y;
    }
 
    node<Tv>* insert(node<Tv> *p, int pos, Tv x, int pr) {
        if (p==NULL) {
            return new node<Tv>(x, pr);
        } else {
            int sz = getSize(p->l);
            if (pos <= sz) {
                p->l = insert(p->l, pos, x, pr);
                augment(p);
                node<Tv> *l = p->l;
                if (l->pr < p->pr) {
                    return rightRotate(p);
                }
            } else {
                p->r = insert(p->r, pos-sz-1, x, pr);
                augment(p);
                node<Tv> *r = p->r;
                if (r->pr < p->pr) {
                    return leftRotate(p);
                }
            }
            return p;
        }
    }
 
    void update(node<Tv> *p, int pos, Tv x) {
        int sz = getSize(p->l);
        if (pos == sz) {
            p->val += x;
        } else if (pos < sz) {
            update(p->l, pos, x);
        } else {
            update(p->r, pos-sz-1, x);
        }
        augment(p);
    }
 
 
    node<Tv>* merge(node<Tv> *lt, node<Tv> *rt) {
        if (lt==NULL) return rt;
        else if (rt==NULL) return lt;
        else {
            if (lt->pr < rt->pr) {
                lt->r = merge(lt->r, rt);
                augment(lt);
                return lt;
            } else {
                rt->l = merge(lt, rt->l);
                augment(rt);
                return rt;
            }
        }
    }
 
    pair<node<Tv>*, node<Tv>*> split(node<Tv> *p, int pos) {
        node<Tv> *tmpRt = insert(p, pos, 0, -1);
        return make_pair(tmpRt->l, tmpRt->r);
    }
 
    void inorder(node<Tv> *p, ostream &o) {
        if (p==NULL) return;
        else {
            inorder(p->l, o);
            o << *p << endl;
            inorder(p->r, o);
        }
    }
 
public:
    DST() {srand(time(NULL)); this->root = NULL;}
 
    void insert(int pos, Tv x) {
        root = insert(root, pos, x, rand()%100000);
    }
 
    void update(int pos, Tv x) {
        update(root, pos, x);
    }
 
    void erase(int pos) {
        pair<node<Tv>*, node<Tv>*> p = split(root, pos);
        pair<node<Tv>*, node<Tv>*> q = split(p.second, 1);
        root = merge(p.first, q.second);
    }
 
    Tv query(int l, int r) {
        pair<node<Tv>*, node<Tv>* > p = split(root, l);
        pair<node<Tv>*, node<Tv>* > q = split(p.second, r-l+1);
        Tv v = q.first->mval;
        root = merge(merge(p.first, q.first), q.second);
        return v;
    }
 
    void inorder(ostream &o) {
        inorder(root, o);
    }
 
    friend std::ostream& operator<<(ostream &o, DST<Tv> D) {
        D.inorder(o);
        return o;
    }
};
