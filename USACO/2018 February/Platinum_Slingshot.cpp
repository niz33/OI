#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
class segtree{
public:
    long long t[600000];
    void init(){
        for(int i=0;i<600000;i++){
            t[i]=1e18;
        }
    }
    void update(int p,long long v,int x,int l, int r){
        if(l==r){
            t[x]=v;
            return;
        }
        int m=(l+r)/2;
        if(p<=m)update(p,v,2*x,l,m);
        else update(p,v,2*x+1,m+1,r);
        t[x]=min(t[2*x],t[2*x+1]);
    }
    long long query(int l,int r,int x,int lx,int rx){
        if(l<=lx&&rx<=r)return t[x];
        if(rx<l||r<lx)return 1e18;
        int m=(lx+rx)/2;
        return min(query(l,r,2*x,lx,m),query(l,r,2*x+1,m+1,rx));
    }
};
int n,m;
segtree ll,rr;
long long ans[200005];
struct slingshot{
    long long x,y,t;
};
vector<slingshot> s;
vector<long long> values;
int main(){
    freopen("slingshot.in","r",stdin);
    freopen("slingshot.out","w",stdout);
    int n,m;
    cin>>n>>m;
    long long x,y,t;
    for(int i=0;i<n;i++){
        cin>>x>>y>>t;
        s.push_back({x,y,t});
        values.push_back(x);
        values.push_back(y);
    }
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        s.push_back({x,y,-i});
        ans[i]=abs(x-y);
    }
    sort(values.begin(),values.end());
    sort(s.begin(),s.end(),[](slingshot a,slingshot b){
        return a.y<b.y;
    });
    ll.init();
    rr.init();
    for(int i=0;i<s.size();i++){
        if(s[i].t>=0){
            ll.update(lower_bound(values.begin(),values.end(),s[i].x)-values.begin(),s[i].t-s[i].x-s[i].y,1,0,n*2-1);
            rr.update(lower_bound(values.begin(),values.end(),s[i].x)-values.begin(),s[i].t+s[i].x-s[i].y,1,0,n*2-1);
        }else{
            ans[-s[i].t]=min(ans[-s[i].t],s[i].y+s[i].x+ll.query(0,upper_bound(values.begin(),values.end(),s[i].x)-values.begin()-1,1,0,n*2-1));
            ans[-s[i].t]=min(ans[-s[i].t],s[i].y-s[i].x+rr.query(lower_bound(values.begin(),values.end(),s[i].x)-values.begin(),n*2-1,1,0,n*2-1));
        }
    }
    sort(s.begin(),s.end(),[](slingshot a,slingshot b){
        return a.y>b.y;
    });
    ll.init();
    rr.init();
    for(int i=0;i<s.size();i++){
        if(s[i].t>=0){
            ll.update(lower_bound(values.begin(),values.end(),s[i].x)-values.begin(),s[i].t-s[i].x+s[i].y,1,0,n*2-1);
            rr.update(lower_bound(values.begin(),values.end(),s[i].x)-values.begin(),s[i].t+s[i].x+s[i].y,1,0,n*2-1);
        }else{
            ans[-s[i].t]=min(ans[-s[i].t],-s[i].y+s[i].x+ll.query(0,upper_bound(values.begin(),values.end(),s[i].x)-values.begin()-1,1,0,n*2-1));
            ans[-s[i].t]=min(ans[-s[i].t],-s[i].y-s[i].x+rr.query(lower_bound(values.begin(),values.end(),s[i].x)-values.begin(),n*2-1,1,0,n*2-1));
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
}
