#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define int long long
#define pb push_back
template<typename T1, typename T2>
struct rpair {T1 r;T2 l;};
template<typename T1, typename T2>
struct cpair {T1 x;T2 y;};
int n,t[300005],lazy[300005],u[100005],d[100005];
void unlazy(int x,int xl,int xr){
    if(lazy[x]&&xl!=xr){
        int m=(xl+xr)/2;
        t[x*2]+=lazy[x]*(m-xl+1);
        t[x*2+1]+=lazy[x]*(xr-m);
        lazy[x*2]+=lazy[x];
        lazy[x*2+1]+=lazy[x];
        lazy[x]=0;
    }
}
void add(int l,int r,int x,int xl,int xr,int v){
    if(l<=xl&&xr<=r){
        t[x]+=v*(xr-xl+1);
        lazy[x]+=v;
        return;
    }
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    if(l<=m)add(l,r,x*2,xl,m,v);
    if(r>m)add(l,r,x*2+1,m+1,xr,v);
    t[x]=t[x*2]+t[x*2+1];
}
int query(int l,int r,int x,int xl,int xr){
    if(l<=xl&&xr<=r)return t[x];
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    int res=0;
    if(l<=m)res+=query(l,r,x*2,xl,m);
    if(r>m)res+=query(l,r,x*2+1,m+1,xr);
    return res;
}
cpair<int,int> ps[100005];
signed main() {
    freopen("sprinklers.in","r",stdin);
    freopen("sprinklers.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>ps[i].x>>ps[i].y,ps[i].x++,ps[i].y++;
    sort(ps+1,ps+n+1,[](cpair<int,int> a,cpair<int,int> b){return a.x<b.x;});
    int my=0;
    for(int i=n;i>=1;i--){
        d[i]=n+1;
        if(ps[i].y<=my)continue;
        my=ps[i].y;
        u[ps[i].x]=my;
    }
    d[0]=n+1;
    my=n+1;
    for(int i=1;i<=n;i++){
        ps[i].x++;
        ps[i].y++;
    }
    for(int i=1;i<=n;i++){
        if(ps[i].y>=my)continue;
        my=ps[i].y;
        d[ps[i].x]=my;
    }
    for(int i=n;i>=1;i--) u[i]=max(u[i],u[i+1]);//cout<<u[i]<<" ";cout<<endl;
    for(int i=1;i<=n;i++) d[i]=min(d[i],d[i-1]);//cout<<d[i]<<" ";cout<<endl;
    int lx=0;
    int ans=0;
    const int MOD=1000000007;
    for(int i=1;i<=n;i++){
        
        if(d[i]!=d[i-1]){
            for(int j=d[i];j<d[lx];j++){
                add(j,n,1,1,n,i-1);
            }
            lx=i;
        }
        if(u[i]<d[i]) continue;
        int h=i,v=u[i]-d[i]+1;
        ans+=(h%MOD)*((v*(v+1)/2)%MOD);
        ans%=MOD;
        ans-=query(d[i],u[i],1,1,n);
        ans%=MOD;
        ans+=MOD;
        ans%=MOD;
        //cout<<i<<" "<<lx<<" "<<endl;
        
        
        //cout<<ans<<endl;
    }
    cout<<ans;
    return 0;
}