const int MAXN = 1010;
int n;
int a[MAXN];
int dp[MAXN];

int lis()
{
    memset(dp, 0, sizeof(int)*n);
    int len = 1;
    dp[0] = a[0];
    for (int i = 1; i < n; ++i)
    {
        int pos = lower_bound(dp, dp + len, a[i]) - dp;
        dp[pos] = a[i];
        len = max(len, pos + 1);
    }
    return len;
}