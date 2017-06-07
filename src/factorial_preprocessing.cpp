/**
 * Description: Preprocessing for finding factorial and inverse factorial. Support efficient binomial coefficient, Catalan no. calculation.
 * Complexity: initfact O(N),   
 * Source: https://github.com/dragonslayerx 
 */


#define MOD 1000000007
#define MAX 2000010
long long fact[MAX];
long long ifact[MAX];
long long power(long long n,int m){
    if(m==0) return 1;
    long long x=power(n,m/2);
    if(m%2==0) return (x*x)%MOD;
    else return (((x*x)%MOD)*n)%MOD;
}

void initfact(int n,long long fact[],long long ifact[]){
     int i;
     fact[0]=1;
     for(i=1;i<=n;i++)
        fact[i] = i*fact[i-1]%MOD;
     ifact[n] = power(fact[n],MOD-2);
     for(i=n;i>0;i--)
        ifact[i-1] = ifact[i]*i%MOD;
}

#define C(n, r) ((((fact[n]*ifact[r])%MOD)*ifact[n - r])%MOD)
#define Catalan(n) ((((fact[2*n]*ifact[n])%MOD)*ifact[n+1])%MOD)
