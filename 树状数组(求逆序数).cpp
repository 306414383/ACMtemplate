//code by gwait 2017/4/17
#include <bits/stdc++.h>
using namespace std;
int a[100010],c[100010],ans[100010];
int t,n;
int max(int a,int b)
{
    return a>b?a:b;
}
int min(int a,int b)
{
    return a<b?a:b;
}
int lowbit(int x)
{
    return x&(-x);
}
int sum(int x)
{
    int res=0;
    while(x>0)
    {
        res+=c[x];
        x-=lowbit(x);
    }
    return res;
}
void  update(int i,  int x)
{
	while(i<=n)  {c[i] = c[i]+x; i += lowbit(i);}
}
int main()
{
    int tmp,le,ri;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>n;
        for(int j=0;j<n;j++)
           cin>>a[j];
        memset(c,0,sizeof(c));
        for(int j=n-1;j>=0;j--)
        {
           tmp=sum(a[j]);
           update(a[j],1);
           le=min(a[j]-1,j);
           ri=j+tmp;
           ans[a[j]]=ri-le;
        }
        printf("Case #%d:",i);
        for(int j=1;j<=n;j++)
            printf(" %d",ans[j]);
        printf("\n");
    }
    return 0;
}
