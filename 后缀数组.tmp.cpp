#include <cstdio>
#include <ctime>
#include <cstring>
#include <algorithm>
const int N = 2000000 + 9;
int n,sa[N],height[N],pos,rank[N],tcnt;
char s[N];
struct SAM {
    int l[N * 2],ch[N * 2][28],fa[N * 2],cnt,last,len,lp[N * 2];
    int son[N * 2],son1[N * 2],lnk[N * 5],nxt[N * 5],tcnt,b[28],t[N * 2],ec,d;
    bool mark[N * 2];
    char s[N];
    void addedge1(int x,int y) {
        nxt[++ec] = son1[x];
        lnk[son1[x] = ec] = y;
    }
    void add(int c) {
        int np = ++cnt,p = last;
        last = np;
        l[np] = ++len;
        mark[np] = true; //memset(ch[np],0,sizeof ch[np]);
        lp[np] = 0;
        for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np/*,addedge1(p,c)*/;
        if (!p) fa[np] = 1;
        else {
            int q = ch[p][c];
            if (l[p] + 1 == l[q]) fa[np] = q;
            else {
                int nq = ++cnt;
                lp[nq] = lp[q] + l[q] - 1 - l[p];
                l[nq] = l[p] + 1;
                mark[nq] = false;
                memcpy(ch[nq],ch[q],sizeof ch[q]);
                // for (int i = son1[q]; i; i = nxt[i])
                //     addedge1(nq,lnk[i]),ch[nq][lnk[i]] = ch[q][lnk[i]];
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                for (; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
            }
        }
    }
    void dfs(int u,int *sa) {
        for (int p = u; p; )
            if (son[p]) {
                int v = lnk[son[p]];
                son[p] = nxt[son[p]];
                if (mark[v]) sa[tcnt++] = len - l[v];
                p = v;
            } else p = fa[p];
    }
    void addedge(int x,int y) {
        nxt[++ec] = son[x];
        lnk[son[x] = ec] = y;
    }
    void build_tree() {
        memset(b,0,sizeof b);
        //memset(son,0,sizeof(*son) * (cnt+1));ec = 0;
        for (int i = 2; i <= cnt; ++i) ++b[s[lp[i] + l[i] - l[fa[i]] - 1] - 'a'];
        for (int i = 1; i < 28; ++i) b[i] += b[i - 1];
        for (int i = 2; i <= cnt; ++i) t[b[s[lp[i] + l[i] - l[fa[i]] - 1] - 'a']--] = i;
        for (int i = cnt - 1; i; --i) addedge(fa[t[i]],t[i]);
    }
    void construct_sa(char *ss,int n,int *sa) {
        tcnt = 0;
        for (int i = 0; i < n; ++i) s[n - i - 1] = ss[i];
        construct(n);
        build_tree();
        dfs(1,sa);
    }
    void construct(int n) {
        len = 0;
        last = cnt = 1;
        //memset(ch[1],0,sizeof ch[1]);
        for (int i = 0; i < n; ++i) add(s[i] - 'a');
    }
} sam;
void set_h() {
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    height[n - 1] = 0;
    for (int i = 0,j,k = 0; i < n - 1; height[rank[i++]] = k)
        for (k = k ? k - 1 : 0,j = sa[rank[i] - 1]; s[i + k] == s[j + k]; ++k);
}
int main() {
// #ifndef ONLINE_JUDGE
//     freopen("sam_to_sa.in","r",stdin);
//     freopen("sam_to_sa.out","w",stdout);
// #endif
    double st = clock();
    scanf("%s",s);
    sam.construct_sa(s,strlen(s),sa);
    for (int i = 0,len = strlen(s); i < len; ++i) printf("%d\n",sa[i]);
    printf("%.5f\n",(clock() - st) / CLOCKS_PER_SEC);
    //set_h();
//printf("%d\n",solve());
}