int digit[20];
int dp[20][10];
long long int dfs(int pos,int predigit,bool islast,bool notzero)
{
    if(pos==-1) {
        return 1;
    }
    if(!islast&&!notzero&&dp[pos][predigit]!=-1) {
        return dp[pos][predigit];
    }
    int ans=0;
    int to=islast?digit[pos]:9;
    for(int d=0; d<=to; d++) {
        if(notzero==0) {
            if(fabs(d-predigit)>=2) {
                ans+=dfs(pos-1,d,islast&&d==to,notzero&&!d);
            }
        }
        else {
            ans+=dfs(pos-1,d,islast&&d==to,notzero&&!d);
        }
    }
    return (islast||notzero)?ans:dp[pos][predigit]=ans;
}
long long int solve(int x)
{
    int cnt=0;
    while(x!=0) {
        digit[cnt++]=x%10;
        x=x/10;
    }
    return dfs(cnt-1,0,true,true);
}

int main()
{
    memset(dp,-1,sizeof(dp));
    long long int n,m;
    //scanf("%d%d",&n,&m);
    //cout<<solve(10)<<" "<<solve(1)<<endl;
    //printf("%I64d\n",solve(m)-solve(n-1));
    while(cin>>n>>m) {
        cout<<solve(m)-solve(n-1)<<endl;
    }
    return 0;
}
