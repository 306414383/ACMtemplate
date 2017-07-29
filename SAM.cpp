/*
后缀自动机是个自动机，能够接受所有后缀（接受点就是last和其fail指针一直到root的链上的点）。
自动机上每个点都是一个状态，代表了一个字符串集合S，其中每个字符串都是原串的子串，而且出现位置的右端点集合(right集合）都是一样的。

例如原串是ABBABBABBBBBABBA
BBABBABBBBBABBA
BBABBBBBABBA
BBABBA
BBA
此时S集合就是
由此可以推出一个性质，就是S集合里面的字符串长度是递增的，并且小串都是大串的后缀。
对于点p，我们不妨记长度区间为[Min(p),Max(p)]。
在我的代码中，l[p]就是Max(p)。上述例子中l[p]就是3。为了方便描述，我们定义S(p)是p的代表串集合。

对于一个点p，fa[p]代表的意思就是|right|最小的且right(q)包含right(p)的q。
可以发现S(q)肯定都是S(p)的后缀，而且Min(p) == Max(q) + 1。由此可以推出|S(p)|。

ch[p]就是自动机上面的转移。而且如果q可以由p转移到，那么Max(q)>Max(p) 而且 Min(q)<=Min(p)+1（后面那个是我自己yy的，不知道有没有错。。。有问题的话欢迎留言）

说说lp[p]吧。注意到我们建自动机的时候都只记了长度l，那如果我们想要输出p的代表串S集合呢？
可以记一个lp[p]，代表S(p)中最长串在原串中的任意一个出现位置的左端点。
新建一个前缀时，lp[p]=0，
如果新建一个nq用替代原来的点q时，lp[nq] = lp[q] + l[q] - 1 - l[p];（详见代码）
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 250000 * 2 + 9;//250000为原始长度 需要开2倍
struct SAM {
    int l[N],ch[N][26],fa[N],cnt,len,last;//其中l就是clj课件里面的Max，fa就是fail指针，也是后缀树上的父亲，ch[26]是自动机上的转移
    //ch第一维只起标记作用 类似指针指向 fa
    void init() {
        cnt = last = 1;
        len = 0;
        memset(ch[1],0,sizeof ch[1]);
    }
    void add(int c) {
        cout << "add" << (c + 'a') << endl;
        int np = ++cnt,p = last;    // p 为前一个点 np 为新点 last = np
        last = np;
        l[np] = ++len;     //建立一个Lth为len+1的节点
        //   cout << "np=" << np << " cnt="<< cnt << " p=" <<p << " last=" << last << " l[np]=" << l[np] << endl;
        memset(ch[np],0,sizeof ch[np]);
        for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;//沿祖先向上，寻找插入位置。同时更新ch
        if (!p) fa[np] = 1;    //插入到根的下面
        else {
            int q = ch[p][c];
            if (l[q] == l[p] + 1)
                fa[np] = q;  //成为q的孩子
            else {
                int nq = ++cnt;
                fa[nq] = fa[q];
                l[nq] = l[p] + 1;     //新建一个节点nq ，表示np和q的公共前缀
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                fa[q] = fa[np] = nq;   // 兄弟节点
                for (; ch[p][c] == q; p = fa[p])
                    ch[p][c] = nq;  //更新第二部分的ch
            }
        }
    }
    void construct(string s) {
        init();
        int tmp = s.length();
        for (int i = 0; i < tmp; ++i) add(str[i] - 'a');
    }
} sam;
int main() {
    string str,str2;
    cin >> str>>str2;
    sam.construct(str);

}
