#include <bits/stdc++.h>
#include <map>
using namespace std;
map<int,pair<int,int>>mp;
namespace SegmentTree {
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int MAXN = 200000 + 5;
struct Node {
    int sum;
    int mx, mn;
    int add;
    int mul;
    int lazy;
    int lazyMax, lazyMin;
    Node(int _sum = 0, int _max = 0, int _min = inf, int _add = 0, int _mul =1,
         int _lazy = 0, int _lazyMax = 0, int _lazyMin = inf) {
        sum = _sum;
        mx = _max;
        mn = _min;
        add = _add;
        mul = _mul;
        lazy = _lazy;
        lazyMax = _lazyMax;
        lazyMin = _lazyMin;
    }
    friend Node operator +(const Node &a, const Node &b) {
        return Node(a.sum + b.sum, max(a.mx, b.mx), min(a.mn, b.mn));
    }
} seg[MAXN << 2];
void pushUp(int rt) {
    seg[rt].sum = seg[rt << 1].sum + seg[rt << 1 | 1].sum;
    seg[rt].mx = max(seg[rt << 1].mx, seg[rt << 1 | 1].mx);
    seg[rt].mn = min(seg[rt << 1].mn, seg[rt << 1 | 1].mn);
}
void pushDown(int rt, int m) {
// add
    if (seg[rt].add != 0) {
        seg[rt << 1].add += seg[rt].add;
        seg[rt << 1 | 1].add += seg[rt].add;
        seg[rt << 1].sum += seg[rt].add * (m - (m >> 1));
        seg[rt << 1 | 1].sum += seg[rt].add * (m >> 1);
        seg[rt << 1].mx += seg[rt].add;
        seg[rt << 1 | 1].mx += seg[rt].add;
        seg[rt << 1].mn += seg[rt].add;
        seg[rt << 1 | 1].mn += seg[rt].add;
        seg[rt].add = 0;
    }
// multiply
    if (seg[rt].mul != 1) {
        seg[rt << 1].mul *= seg[rt].mul;
        seg[rt << 1 | 1].mul *= seg[rt].mul;
        seg[rt << 1].sum *= seg[rt].mul;
        seg[rt << 1 | 1].sum *= seg[rt].mul;
        seg[rt << 1].mx *= seg[rt].mul;
        seg[rt << 1 | 1].mx *= seg[rt].mul;
        seg[rt << 1].mn *= seg[rt].mul;
        seg[rt << 1 | 1].mn *= seg[rt].mul;
        seg[rt].mul = 1;
    }
// replace
    if (seg[rt].lazy != 0) {
        seg[rt << 1].lazy = seg[rt].lazy;
        seg[rt << 1 | 1].lazy = seg[rt].lazy;
        seg[rt << 1].sum = seg[rt].lazy * (m - (m >> 1));
        seg[rt << 1 | 1].sum = seg[rt].lazy * (m >> 1);
        seg[rt].lazy = 0;
    }
    if (seg[rt].lazyMax != 0) {
        seg[rt << 1].lazyMax = max(seg[rt << 1].lazyMax, seg[rt].lazyMax);
        seg[rt << 1 | 1].lazyMax = max(seg[rt << 1 | 1].lazyMax, seg[rt].
                                       lazyMax);
        seg[rt << 1].mx = max(seg[rt << 1].mx, seg[rt].lazyMax);
        seg[rt << 1 | 1].mx = max(seg[rt << 1 | 1].mx, seg[rt].lazyMax);
        seg[rt].lazyMax = 0;
    }
    if (seg[rt].lazyMin != inf) {
        seg[rt << 1].lazyMin = min(seg[rt << 1].lazyMin, seg[rt].lazyMin);
        seg[rt << 1 | 1].lazyMin = min(seg[rt << 1 | 1].lazyMin, seg[rt].
                                       lazyMin);
        seg[rt << 1].mn = min(seg[rt << 1].mn, seg[rt].lazyMin);
        seg[rt << 1 | 1].mn = min(seg[rt << 1 | 1].mn, seg[rt].lazyMin);
        seg[rt].lazyMin = inf;
    }
// add + multiply + replace
    if (seg[rt].lazy != 0) {
        seg[rt << 1].lazy = seg[rt].lazy;
        seg[(rt << 1) | 1].lazy = seg[rt].lazy;
        seg[rt << 1].add = 0;
        seg[(rt << 1) | 1].add = 0;
        seg[rt << 1].mul = 1;
        seg[(rt << 1) | 1].mul = 1;
        seg[rt << 1].sum = seg[rt].lazy * (m - (m >> 1));
        seg[rt << 1 | 1].sum = seg[rt].lazy * (m >> 1);
        seg[rt].lazy = 0;
    }
    if (seg[rt].add != 0 || seg[rt].mul != 1) {
        seg[rt << 1].add = seg[rt].mul * seg[rt << 1].add + seg[rt].add;
        seg[rt << 1].mul *= seg[rt].mul;
        seg[rt << 1].sum = seg[rt << 1].sum * seg[rt].mul + (m - (m >> 1)) *
                           seg[rt].add;
        seg[(rt << 1) | 1].add = seg[rt].mul * seg[(rt << 1) | 1].add + seg[
                                     rt].add;
        seg[(rt << 1) | 1].mul *= seg[rt].mul;
        seg[(rt << 1) | 1].sum = seg[(rt << 1) | 1].sum * seg[rt].mul + (m >>
                                                                        ) * seg[rt].add;
        seg[rt].add = 0;
        seg[rt].mul = 1;
    }
}
void build(int l, int r, int rt = 1) {
    seg[rt].add = 0;
    seg[rt].mul = 1;
    seg[rt].lazy = 0;
    seg[rt].lazyMax = 0;
    seg[rt].lazyMin = inf;
    if (l == r) {
// init
        seg[rt].sum = 0;
        seg[rt].mx = 0;
        seg[rt].mn = inf;
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}
void update(int L, int R, int c, int l, int r, int rt = 1) {
    if (L <= l && r <= R) {
// add
        seg[rt].add += c;
        seg[rt].sum += c * (r - l + 1);
        seg[rt].mx += c;
        seg[rt].mn += c;
// multiply
        seg[rt].mul *= c;
        seg[rt].sum *= c;
        seg[rt].mx *= c;
        seg[rt].mn *= c;
// replace
        seg[rt].lazy = c;
        seg[rt].sum = c * (r - l + 1);
        seg[rt].lazyMax = max(seg[rt].lazyMax, c);
        seg[rt].lazyMin = min(seg[rt].lazyMin, c);
        seg[rt].mx = max(seg[rt].mx, c);
        seg[rt].mn = min(seg[rt].mn, c);
// square root
        if (seg[rt].mx == 1) {
            return;
        }
        if (l == r) {
            seg[rt].sum = (int) sqrt(seg[rt].sum);
            seg[rt].mx = seg[rt].mn = seg[rt].sum;
            return;
        }
        if (seg[rt].mx == seg[rt].mn) {
            int tmp = seg[rt].mx;
            seg[rt].mx = seg[rt].mn = (int) sqrt(tmp);
            seg[rt].sum = seg[rt].mx * (r - l + 1);
            seg[rt].add += seg[rt].mx - tmp;
            return;
        }
// pushDown(rt,r - l + 1);
// int m = (l + r)>>1;
// update(L, R, c, lson);
// update(L, R, c, rson);
// pushUp(rt);
        return;
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) {
        update(L, R, c, lson);
    }
    if (m < R) {
        update(L, R, c, rson);
    }
    pushUp(rt);
}
Node query(int L, int R, int l, int r, int rt = 1) {
    if (L <= l && r <= R) {
        return seg[rt];
    }
    pushDown(rt, r - l + 1);
    Node ret;
    int m = (l + r) >> 1;
    if (L <= m) {
        ret = ret + query(L, R, lson);
    }
    if (m < R) {
        ret = ret + query(L, R, rson);
    }
    return ret;
}
} // namespace SegmentTree
int main()
{
    return 0;
}