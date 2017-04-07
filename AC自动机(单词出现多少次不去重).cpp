/*
Input
1
5 6
orz
sto
kirigiri
danganronpa
ooooo
o
kyouko
dangan
ronpa
ooooo
ooooo
Output
1
1
0
3
7
*/
#include<bits/stdc++.h>
char sub[10010],str[100010][10010];
int cnt[100010];
long long int sum;
using namespace std;
struct ACautomata{
    int ch[500010][128],fail[500010],val[500010],num[500010];
    int last[500010];
    int sz;
    void init(){
        sz=1;
        memset(ch[0],0,sizeof(ch[0]));
        memset(num,0,sizeof(num));
        val[0]=0;
        fail[0]=0;
        last[0]=0;
    }

    void insert(char *s,int v){
        int n,now=0;
        n=strlen(s);
        for(int i=0;i<n;i++){
            int id=s[i];
            if(ch[now][id]==0){
                ch[now][id]=sz;
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz++]=0;
            }
            now=ch[now][id];

        }
        val[now]=v;
        num[now]++;
    }
    void getans(int i){
        if(val[i]!=0){
            //cnt[val[i]]++;//debug
            sum+=num[i];
            getans(last[i]);
        }
    }
    void build(){
        queue <int> q;
        while(!q.empty()){
            q.pop();
        }
        fail[0]=0;
        for(int i=0;i<128;i++){
            int u=ch[0][i];
            if(u!=0){
                last[u]=0;
                fail[u]=0;
                q.push(u);
            }
        }
        while(!q.empty()){
            int r=q.front();
            q.pop();
            for(int c=0;c<128;c++){
                int u=ch[r][c];
                if(u==0) continue;
                q.push(u);
                int v=fail[r];
                while(v&&ch[v][c]==0) v=fail[v];
                fail[u]=ch[v][c];
                if(val[fail[u]]!=0){
                    last[u]=fail[u];
                }
                else{
                    last[u]=last[fail[u]];
                }
            }
        }
    }
    void query(char *s){
        int n,now=0;
        n=strlen(s);
        for(int i=0;i<n;i++){
            int id=s[i];
            while(now&&ch[now][id]==0){
                now=fail[now];
            }
            now=ch[now][id];
            if(val[now]!=0){
                getans(now);
            }
            else if(last[now]!=0){
                getans(last[now]);
            }
        }
    }
}ac;
int main()
{
    ios::sync_with_stdio(0);
    int t;
    int n,m;
    cin>>t;
    while(t--){
        memset(cnt,0,sizeof(cnt));
        ac.init();
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>str[i];
        }
        for(int i=1;i<=m;i++){
            cin>>sub;
            ac.insert(sub,i);
        }
        ac.build();
        for(int i=1;i<=n;i++){
            sum=0;
            ac.query(str[i]);
            cout<<sum<<"\n";
        }
    }
    return 0;
}