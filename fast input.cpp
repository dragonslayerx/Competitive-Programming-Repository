/**
 * Description: Fast Input & Output
 * Usage: readInt, writeInt
 * Source: https://github.com/dragonslayerx 
 */

#ifdef ONLINE_JUDGE
	#define GETCHAR getchar_unlocked
	#define PUTCHAR putchar_unlocked
#endif
#ifndef ONLINE_JUDGE
	#define GETCHAR getchar
	#define PUTCHAR putchar
#endif

template <typename T>
inline void readInt(T &n){
    n = 0;
    bool flag=1;
    char c;
    int sign=1;
    while (1){
	c = GETCHAR();
    	if(c=='-') sign=-1;
	else if(c>='0'&&c<='9') {n = n * 10 + c - '0';flag=0;}
	else if(flag!=1) break;
    }
    n *= sign;
}


template <typename T>
inline void writeInt(T x) {
    bool sign = false; 
    if (x < 0) {
        x = -x;
    }
    bool flag = false;
    char buf[20];
    int i = 0;
    while (x > 0) {
    	flag = true;
	buf[i++] = x % 10 + '0';
	x /= 10;
    }
    if (flag) {
	if (sign) PUTCHAR('-');
	i--;
	for (; i >=0; i--) {
		PUTCHAR(buf[i]);
	}
    } else {
    	PUTCHAR('0');
    }
}