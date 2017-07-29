ll PowerMod(ll a, ll b, ll c) {
    ll ans = 1;
    a = a % c;
    while(b>0) {
        if(b % 2 == 1)
            ans = (ans * a) % c;
        b = b>>1;
        a = (a * a) % c;
    }
    return ans;
}