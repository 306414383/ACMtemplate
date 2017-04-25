//求(a+a^2+a^3+......+a^n)%mod
LL power(LL a,LL b)
{
    LL ans = 1;
    a %= M;
    while(b)
    {
        if(b & 1)
        {
            ans = ans * a % mod;
            b--;
        }
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}
LL sum(LL a,LL n)
{
    if(n == 1) return a;
    LL t = sum(a,n/2);
    if(n & 1)
    {
        LL cur = power(a,n/2+1);
        t = (t + t * cur % mod) % mod;
        t = (t + cur) % M;
    }
    else
    {
        LL cur = power(a,n/2);
        t = (t + t * cur % mod) % mod;
    }
    return t;
}
int main()
{
    LL a,n;
    while(cin>>a>>n)
        cout<<sum(a,n)<<endl;
    return 0;
}
