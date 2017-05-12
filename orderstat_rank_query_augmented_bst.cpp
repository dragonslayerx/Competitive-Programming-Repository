/**
 * Description: Augmented tree for order statistics, rank query
 * Usage: See below O(lg(N))
 * Source: https://github.com/dragonslayerx 
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> //required
#include <ext/pb_ds/tree_policy.hpp> //required
using namespace __gnu_pbds; //required
using namespace std;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set <int> s;
/* or:
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
ordered_set s;
This works in C++98 but the above version only works in C++11
*/
int main(){
	// It has C++ `set` functions:
	for(auto i: {1,3,5,8})
		s.insert(i);
	s.erase(8);
	s.erase(s.find(8));
	cout << * s.begin() << endl;
	if(s.begin() == s.end() or s.empty())
		cout << "empty" << endl;
	s.lower_bound(3);
	s.upper_bound(1);
	cout << s.size() << endl;
	// special `tree` functions:
	cout << s.order_of_key(3) << endl; // the number of elements in s less than 3 (in this case, 0-based index of element 3)
	cout << *s.find_by_order(1) << endl; // 1-st elemt in s (in sorted order, 0-based)
}
