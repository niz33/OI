#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#pragma GCC optimize("O2")
using namespace std;
#define int long long
#define ll long long
#define pb push_back
template<typename T1,typename T2> struct cpair{T1 x;T2 y;};
template<typename T1,typename T2> struct rpair{T1 l;T2 r;};
template<typename T1,typename T2> struct epair{T1 u;T2 v;};
int n,k;
rpair<int,int> a[100005];
ll t[11][800005],lazy[11][800005],mod=1e9+7,binom[15][15];
void unlazy(int ti,int l,int r,int x){
    if(lazy[ti][x]==1||l==r)return;
    lazy[ti][x<<1]=lazy[ti][x<<1]*lazy[ti][x]%mod;
    lazy[ti][(x<<1)+1]=lazy[ti][(x<<1)+1]*lazy[ti][x]%mod;
    t[ti][x<<1]=t[ti][x<<1]*lazy[ti][x]%mod;
    t[ti][(x<<1)+1]=t[ti][(x<<1)+1]*lazy[ti][x]%mod;
    lazy[ti][x]=1;
}
void add(int ti,int p,int l,int r,int x,int v){
    if(l==r){
        t[ti][x]+=v;
        if(t[ti][x]>=mod)t[ti][x]-=mod;
        //if(v==3) cout<<t[ti][x]<<endl;
        return;
    }
    unlazy(ti,l,r,x);
    int mid=(l+r)>>1;
    if(p<=mid)add(ti,p,l,mid,x<<1,v);
    else add(ti,p,mid+1,r,(x<<1)+1,v);
    t[ti][x]=t[ti][x<<1]+t[ti][(x<<1)+1];
    if(t[ti][x]>=mod)t[ti][x]-=mod;
}
void mul(int ti,int al,int ar,int l,ll r,int x){
    if(al<=l&&r<=ar){
        t[ti][x]<<=1;
        if(t[ti][x]>=mod)t[ti][x]-=mod;
        lazy[ti][x]=lazy[ti][x]<<=1;
        if(lazy[ti][x]>=mod)lazy[ti][x]-=mod;
        return;
    }
    unlazy(ti,l,r,x);
    int mid=(l+r)/2;
    if(al<=mid)mul(ti,al,ar,l,mid,x<<1);
    if(ar>mid)mul(ti,al,ar,mid+1,r,(x<<1)+1);
    t[ti][x]=(t[ti][x<<1]+t[ti][(x<<1)+1]);
    if(t[ti][x]>=mod)t[ti][x]-=mod;
}
ll query(int ti,int al,int ar,int l,int r,int x){
    //cout<<ti<<" "<<al<<" "<<ar<<" "<<l<<" "<<r<<" "<<x<<endl;
    if(al<=l&&r<=ar)return t[ti][x];
    unlazy(ti,l,r,x);
    int mid=(l+r)>>1;
    ll ans=0;
    if(al<=mid)ans+=query(ti,al,ar,l,mid,x<<1);
    if(ar>mid)ans+=query(ti,al,ar,mid+1,r,(x<<1)+1);
    if(ans>=mod)ans-=mod;
    return ans;
}
void calc_binom(){
    for(int i=0;i<=10;i++){
        binom[i][0]=1;
        for(int j=1;j<=i;j++){
            binom[i][j]=binom[i-1][j-1]+binom[i-1][j];
            if(binom[i][j]>=mod)binom[i][j]-=mod;
        }
    }
}
bool comp(rpair<int,int> a,rpair<int,int> b){
    return a.l<b.l;
}
signed main() {
    freopen("help.in","r",stdin);
    freopen("help.out","w",stdout);
    calc_binom();
    cin>>n>>k;
    int nn=2*n;
    for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].l,&a[i].r);
    sort(a+1,a+n+1,comp);

    for(int ii=1;ii<=n;ii++){

        for(int i=0;i<=k;i++){

            add(i,a[ii].r,1,nn,1,query(i,a[ii].l,a[ii].r,1,nn,1));
            if(a[ii].r<nn)mul(i,a[ii].r+1,nn,1,nn,1);
        }
        if(a[ii].l>1){
            ll s[11],ss[11];
            for(int i=0;i<=k;i++) s[i]=query(i,1,a[ii].l-1,1,nn,1),ss[i]=0;
            for(int i=0;i<=k;i++){
                for(int j=0;j<=i;j++){
                    ss[i]+=s[j]*binom[i][j]%mod;
                    if(ss[i]>=mod)ss[i]-=mod;
                }
                add(i,a[ii].r,1,nn,1,ss[i]);
            }
        }
        
        for(int i=0;i<=k;i++)add(i,a[ii].r,1,nn,1,1);
    }
    cout<<query(k,1,nn,1,nn,1)<<endl;
    return 0;
}