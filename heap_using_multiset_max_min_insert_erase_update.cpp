/**
 * Description: A MaxMin priority queue that supports erase operation.
 * Usage: insert O(lg(N)), erase O(lg(N)), maxElement O(lg(N)), minElement O(lg(N)) 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <map>
#include <set>
using namespace std;

template<typename Tk, typename Tv>
class Heap {
    map<Tk, Tv> lookup;
    multiset< pair<Tv, Tk> > prQ;
public:
    void insert(Tk key, Tv val) {
        lookup[key] = val;
        prQ.insert(make_pair(val, key));
    }

    void update(Tk key, Tv val) {
        typename multiset<Tv>::iterator it = prQ.find(make_pair(lookup[key], key));
        prQ.erase(it);
        lookup[key] = val;
        prQ.insert(make_pair(val, key));
    }

    void erase(Tk key) {
        typename multiset<Tv>::iterator it = prQ.find(make_pair(lookup[key], key));
        prQ.erase(it);
        lookup.erase(key);
    }

    pair<Tv, Tk> maxElement() {
        return *prQ.rbegin();
    }

    pair<Tv, Tk> minElement() {
        return *prQ.begin();
    }
};

int main() {
    Heap<int,int> H;
    H.insert(1, 5);
    H.insert(2, 4);
    H.insert(3, 9);
    H.insert(4, 7);
    cout << H.minElement().first << " " << H.minElement().second << endl;
}
