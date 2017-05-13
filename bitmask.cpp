/**
 * Description: Bitmask (Support set, unset and get bit operation)
 * Usage: set O(1), unset O(1), get O(1)
 * Source: https://github.com/dragonslayerx
 */

class Bitmask {
	int mask;
	public:
	Bitmask() {
		mask = 0;
	}
	void set(int i) {
		mask |= (1 << i);
	}
	void unset(int i) {
		mask &= ~(1 << i);
	}
	int get(int i) {
		return (mask & (1 << i));
	}
	const int operator [](int i) {
	    return get(i);
	}
};
