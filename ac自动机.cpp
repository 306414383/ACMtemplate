#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#define all(a) (a).begin(), (a).end()
#define ll long long
#define endl "\n"
#define DE cout << "------" << endl
#define mems(a, b) memset(a, b, sizeof a)
#define pii pair<int, int>
#define mk make_pair
using namespace std;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

const int maxnode = 100010 + 5;
const int SIGMA_SIZE = 128;
char str[100010][10010];
struct ACAutomata
{
    int ch[maxnode][SIGMA_SIZE]; //节点
    int fail[maxnode];           //失配指针
    int val[maxnode];            //每个字符串的结尾结点都有一个非0的val,记录以i结尾的字符串个数
    int last[maxnode];           // last[i]=j表j节点表示的单词是i节点单词的后缀，且j节点是单词节点（部分题目不需要）
    int sz;

    int idx(char c)
    {
        return c - 'a';
    } //获取索引
    void init()
    {
        sz = 1;
        memset(ch[0], -1, sizeof(ch[0]));
        memset(val, -1, sizeof(val));
    } //建立根节点
    void insert(char *s)
    {
        int len = strlen(s);
        int now = 0;
        for (int i = 0; i < len; ++i)
        {
            int id = idx(s[i]);
            if (ch[now][id] == -1)
            {
                memset(ch[sz], -1, sizeof(ch[sz]));
                ch[now][id] = sz++;
            }
            now = ch[now][id];
        }
        val[now]++;
    } //建立字典树
    void build()
    { //建立索引
        queue<int> q;
        fail[0] = 0;
        for (int i = 0; i < SIGMA_SIZE; ++i)
            if (ch[0][i])
            {
                fail[ch[0][i]] = 0;
                q.push(ch[0][i]);
            }
        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            for (int i = 0; i < SIGMA_SIZE; ++i)
                if (!ch[now][i]) //若该点不存在，直接将该位置指向失配指针的下一位
                    ch[now][i] = ch[fail[now]][i];
                else
                {
                    fail[ch[now][i]] = ch[fail[now]][i];
                    q.push(ch[now][i]);
                }
        }
    }
    int query(char *s)
    {
        int len = strlen(s);
        int now = 0;
        int res = 0;
        for (int i = 0; i < len; i++)
        {
            now = ch[now][idx(s[i])];
            int tmp = now;
            while (tmp != 0)
            {
                res += val[tmp];
                // val[tmp] = 0; //防止重复，如考虑重复情况请注释掉本行，如Hdu5384
                tmp = fail[tmp];
            }
        }
        return res;
    }
    void Debug()
    {
        for (int i = 0; i < sz; i++)
        {
            printf("id = %3d,fail = %3d,val = %3d,chi = [", i, fail[i], val[i]);
            for (int j = 0; j < SIGMA_SIZE; j++)
                printf("%2d", ch[i][j]);
            printf("]\n");
        }
    }
};
char buf[1000010];
ACAutomata ac;
int main()
{
    int t;
    int n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        ac.init();
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str[i]);
        }
        for (int i = 0; i < m; i++)
        {
            scanf("%s", buf);
            ac.insert(buf);
        }
        ac.build();

        for (int i = 0; i < n; ++i)
            printf("%d\n", ac.query(str[i]));
    }
    return 0;
}
