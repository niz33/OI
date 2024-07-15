#include<iostream>
#include<algorithm>
#include <string.h>
#include <vector>
#define ll long long
using namespace std;
ll b,n,d,m;
ll divv(ll a,ll b){
    ll c=a+b;
    return c>=0?c/2:(c-1)/2;
}
class tree{
    public:
    ll t[600000];
    void update(ll p,ll x,ll l,ll r,ll v){
        //cout<<x<<" "<<l<<" "<<r<<endl;
        if(l==r){
            t[x]+=v;
            return;
        }
        ll m=divv(l,r);
        if(p<=m)update(p,x*2,l,m,v);
        else update(p,x*2+1,m+1,r,v);
        t[x]+=v;
    }
    ll query(ll l,ll r,ll x,ll xl,ll xr){
        //cout<<x<<" "<<l<<" "<<r<<endl;
        if(l<=xl&&xr<=r)return t[x];
        ll m=divv(xl,xr);
        ll res=0;
        if(l<=m)res+=query(l,r,x*2,xl,m);
        if(r>m)res+=query(l,r,x*2+1,m+1,xr);
        return res;
    }
}t;
void b1(){
    ll p[100005],ans=0;
    for(int i=1;i<=n;i++)cin>>p[i];
    sort(p+1,p+n+1);
    int l=1;
    for(int r=1;r<=n;r++){
        while(p[r]-p[l]>d)l++;
        ans+=r-l;
    }
    cout<<ans;
}
void b2(){
    ll ans=0;
    pair<ll,ll> p[100005];
    ll x,y;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        p[i].first=x+y;
        p[i].second=x-y;
    }
    sort(p+1,p+n+1,[&](pair<ll,ll> a,pair<ll,ll> b){
        return a.first<b.first;
    });
    //cout<<endl;
    //for(int i=1;i<=n;i++)cout<<p[i].first<<" "<<p[i].second<<endl;
    int l=1;
    for(int r=1;r<=n;r++){
        while(p[r].first-p[l].first>d){
            t.update(p[l].second,1,-m,m,-1);
            l++;
        }
        ans+=t.query(max(-m,p[r].second-d),min(m,p[r].second+d),1,-m,m);
        t.update(p[r].second,1,-m,m,1);
    }
    cout<<ans;
}
ll s[152][152];
void b3(){
    ll x,y,z;
    vector<pair<ll,ll>> ps[76];
    ll ans=0;
    for(int i=1;i<=n;i++){
        cin>>x>>y>>z;
        ps[x].push_back({y+z,y-z+m});
    }
    for(int x=1;x<=m;x++){
        for(int y=1;y<=2*m;y++) for(int z=1;z<=2*m;z++) s[y][z]=0;
        for(pair<ll, ll> p:ps[x]){
            //cout<<p.first<<" "<<p.second<<endl;
            s[p.first][p.second]++;
        }
        for(int y=1;y<=2*m;y++) for(int z=1;z<=2*m;z++) s[y][z]+=s[y][z-1];
        for(int y=1;y<=2*m;y++) for(int z=1;z<=2*m;z++) s[y][z]+=s[y-1][z];
        ll pans=0;
        for(int px=1;px<=m;px++){
            for(pair<ll, ll> p:ps[px]){
                ll rad=d-abs(px-x);
                if(rad<0)continue;
                ll l=max(1ll,p.first-rad);
                ll r=min(2*m,p.first+rad);
                ll d=max(1ll,p.second-rad);
                ll u=min(2*m,p.second+rad);
                if(x!=px)ans+=s[r][u]-s[r][d-1]-s[l-1][u]+s[l-1][d-1];
                else pans+=s[r][u]-s[r][d-1]-s[l-1][u]+s[l-1][d-1];
                
            }
        }
        pans-=ps[x].size();
        ans+=pans;
    }
    cout<<ans/2;
}
int main(){
    cin>>b>>n>>d>>m;
    switch(b){
        case 1:b1();break;
        case 2:b2();break;
        case 3:b3();break;
    }   
}