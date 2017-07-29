#define maxn 200000+5

using namespace std;

int dim,n,cnt,root,ans,pos;

struct Point{
    int x[2],val;
    Point(int a=0,int b=0,int c=0){ x[0]=a; x[1]=b; val=c; }
    inline int operator [] (int i){ return x[i]; }
    inline bool operator < (const Point &T)const{ return x[dim]<T.x[dim]; }
}p[maxn];

struct KD_Tree{
    int l,r,sum;
    int mx[2],mi[2];
    Point t;
}tr[maxn];

inline int in(){
    int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}

inline void Update_mx(int &x,int y){ if(y>x) x=y; }

inline void Update_mi(int &x,int y){ if(y<x) x=y; }

void Update(int k){
    for(int i=0;i<2;i++){
        if(tr[k].l) Update_mx(tr[k].mx[i],tr[tr[k].l].mx[i]),Update_mi(tr[k].mi[i],tr[tr[k].l].mi[i]);
        if(tr[k].r) Update_mx(tr[k].mx[i],tr[tr[k].r].mx[i]),Update_mi(tr[k].mi[i],tr[tr[k].r].mi[i]);
    }
    tr[k].sum=tr[tr[k].l].sum+tr[tr[k].r].sum+tr[k].t.val;
}

void Insert(int &k,Point pt,int d){
    if(!k){
        k=++cnt; tr[k].t=pt; tr[k].sum=pt.val;
        for(int i=0;i<2;i++) tr[k].mx[i]=tr[k].mi[i]=pt[i];
        return;
    }
    if(pt[0]==tr[k].t[0] && pt[1]==tr[k].t[1]){ tr[k].sum+=pt.val; tr[k].t.val+=pt.val; return; }
    dim=d;
    if(pt<tr[k].t) Insert(tr[k].l,pt,d^1);
    else Insert(tr[k].r,pt,d^1);
    Update(k);
}

inline bool cross(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
    if(x1<x4 || x2>x3 || y2<y3 || y1>y4) return false;
    return true;
}

inline bool cover(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){ //1-2 cover 3-4
    if(y1<=y3 && y2>=y4 && x1>=x3 && x2<=x4) return true;
    return false;
}

int Query(int k,int x1,int y1,int x2,int y2){
    if(cover(x1,y1,x2,y2,tr[k].mx[0],tr[k].mi[1],tr[k].mi[0],tr[k].mx[1])) return tr[k].sum;
    int tmp=0,l=tr[k].l,r=tr[k].r;
    if(tr[k].t[0]<=x1 && tr[k].t[0]>=x2 && tr[k].t[1]>=y1 && tr[k].t[1]<=y2) tmp+=tr[k].t.val;
    if(l && cross(x1,y1,x2,y2,tr[l].mx[0],tr[l].mi[1],tr[l].mi[0],tr[l].mx[1])) tmp+=Query(l,x1,y1,x2,y2);
    if(r && cross(x1,y1,x2,y2,tr[r].mx[0],tr[r].mi[1],tr[r].mi[0],tr[r].mx[1])) tmp+=Query(r,x1,y1,x2,y2);
    return tmp;
}

#define mid ((l+r)>>1)

void Rebuild(int &k,int l,int r,int d){
    dim=d; k=++cnt;
    nth_element(p+l,p+mid,p+r+1);
    tr[k].t=p[mid];
    for(int i=0;i<2;i++) tr[k].mx[i]=tr[k].mi[i]=p[mid][i];
    if(l<mid) Rebuild(tr[k].l,l,mid-1,d^1);
    else tr[k].l=0;
    if(r>mid) Rebuild(tr[k].r,mid+1,r,d^1);
    else tr[k].r=0;
    Update(k);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("4066.in","r",stdin);
    freopen("4066.out","w",stdout);
#endif
    n=in(); int flag=10000;
    for(int opt;(opt=in())!=3;){
        if(opt==1){
            int x,y,c;
            x=in()^ans; y=in()^ans; c=in()^ans;
            Insert(root,Point(x,y,c),0);
            if(cnt==flag){
                for(int i=1;i<=cnt;i++) p[i]=tr[i].t,tr[i].sum=0;               
                int tmp=cnt; cnt=0; flag+=10000;
                Rebuild(root,1,tmp,0);
            }
        }
        else{
            int x1,y1,x2,y2;
            x1=in()^ans; y1=in()^ans; x2=in()^ans; y2=in()^ans;
            printf("%d\n",ans=Query(root,x2,y1,x1,y2));
        }
    }
    return 0;
}