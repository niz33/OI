#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#define int long long
using namespace std;
int n,k;
pair<int,int> a[100005];
int t[400005];
void update(int p,int v,int x,int l,int r){
    t[x]+=v;
    if(l==r) return;
    int m=(l+r)/2;
    if(p<=m) update(p,v,x*2,l,m);
    else update(p,v,x*2+1,m+1,r);
}
int query(int l,int r,int x,int xl,int xr){
    if(l<=xl&&xr<=r) return t[x];
    int m=(xl+xr)/2, res=0;
    if(l<=m) res+=query(l,r,x*2,xl,m);
    if(r>m) res+=query(l,r,x*2+1,m+1,xr);
    return res;
}
struct thing{
    int t,sec,ind;
};
int cdq(int l,int r){
    if(l==r) return 0;
    int res=0;
    int m=(l+r)/2;
    res+=cdq(l,m);
    res+=cdq(m+1,r);
    vector<thing> things;
    for(int i=l;i<=m;i++) things.push_back({1,a[i].first,a[i].second});
    for(int i=m+1;i<=r;i++) things.push_back({2,a[i].first,a[i].second});
    // cout<<"-----------------"<<endl;
    // cout<<l<<" "<<r<<" "<<m<<endl;
    // for(int i=l;i<=r;i++) cout<<a[i].first<<" ";
    // cout<<endl;
    // for(int i=l;i<=r;i++) cout<<a[i].second<<" ";
    // cout<<endl;
    sort(things.begin(),things.end(),[&](thing a,thing b){
        return a.sec<b.sec;
    });
    int tot=0;
    for(thing t: things){
        //cout<<t.t<<" "<<t.sec<<" "<<t.ind<<endl;
        if(t.t==2) update(t.ind,1,1,1,n),tot++;
        else res+=tot-query(max(1ll,t.ind-k),min(n,t.ind+k),1,1,n);
        //cout<<tot<<" "<<res<<endl;
    }
    for(thing t: things) if(t.t==2) update(t.ind,-1,1,1,n);
    //cout<<res<<endl;
    return res;
}
signed main(){
    freopen("friendcross.in","r",stdin);
    freopen("friendcross.out","w",stdout);
    cin>>n>>k;
    int temp;
    int temps[100005];
    for(int i=1;i<=n;i++){
        cin>>a[i].second;
        temps[a[i].second]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>temp;
        a[temps[temp]].first=i;
    }
    cout<<cdq(1,n);
}