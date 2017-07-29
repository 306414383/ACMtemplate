ll primes[300000];//1e5 9593 个 1e6以内为78498个 1e7以内为664579个 1e8 57614555个
bool isPrime[1000000];
int cntp=0;
ll getprime() {
    mst(isPrime,1);
    isPrime[0]=isPrime[1]=0;
    rep(i,2,1000000) {
        if(isPrime[i]) {
            primes[cntp++]=i;
            for(ll k=1ll*i*i; k<1000000; k+=i)
                isPrime[k]=0;
        }

    }
}