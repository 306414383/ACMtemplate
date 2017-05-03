ll primes[300000];//1e6以内为78498个 1e7以内为664579个 1e8 57614555个
bool isPrime[1000000];
int cnt=0;
ll fuck(){
    mst(isPrime,1);
    isPrime[0]=isPrime[1]=0;
    rep(i,2,1000000)
    {
        if(isPrime[i]){
            primes[cnt++]=i;
            for(ll k=1ll*i*i;k<1000000;k+=i)
                isPrime[k]=0;
        }

    }
    cout<<cnt;
}