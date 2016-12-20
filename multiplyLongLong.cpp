/**
 * Description: Multiply two 64 bit integers and returns result mod M,
 * Source: https://github.com/dragonslayerx 
 */

long long int multiply(long long int val, long long int n,long long int mod){
  long long int q=((double)val*(double)n/(double)mod);
  long long int res=val*n-mod*q;
  res=(res%mod+mod)%mod;
  return res;
}