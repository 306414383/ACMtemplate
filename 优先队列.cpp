//-----------------------------------------------------------------
struct point{
int num;int pos;
};
struct cmp{   ///给优先队列定义比较规则
    bool operator ()(point &a,point &b){
        return a.pos<b.pos;
    }
};
priority_queue <point,vector<point>,cmp> que1,que2;
/**说明
    top为优先队列反向，例如此处为pos小排序，实际顺序为pos最大为top**/
/**----------------------------------------------------------**/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    string str,str2;
    point tmp;
    int cnt=0;
    while(cin>>n,n)
    {
        while(!que1.empty()) que1.pop();
        while(!que2.empty()) que2.pop();
        cnt++;
        cout<<"Case #"<<cnt<<":"<<endl;
        rep(i,0,n)
        {
            cin>>str;
            if(str=="push")
            {
                cin>>str>>k;
                tmp.pos=i,tmp.num=k;
                if(str=="A")
                    que1.push(tmp);
                else
                    que2.push(tmp);
            }
            else if(str=="pop")
            {
                cin>>str;
                if(str=="A")
                {
                    tmp=que1.top();
                    cout<<tmp.num<<endl;
                    que1.pop();
                }
                else if(str=="B")
                {
                    tmp=que2.top();
                    cout<<tmp.num<<endl;
                    que2.pop();
                }
            }
            else
            {
                cin>>str>>str2;
                if(str==str2)
                    continue;
                int sz1=que1.size();
                int sz2=que2.size();
                if(sz1>sz2)
                {
                    while(!que2.empty())
                    {
                        tmp=que2.top();
                        que1.push(tmp);
                        que2.pop();
                    }
                    if(str=="B")
                        swap(que1,que2);
                }
                else
                {
                    while(!que1.empty())
                    {
                        tmp=que1.top();
                        que2.push(tmp);
                        que1.pop();
                    }
                    if(str=="A")
                        swap(que1,que2);
                }
            }
        }
    }

}
