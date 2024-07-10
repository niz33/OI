#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,ans[1000000];
int ss=1000000;
vector<pair<int,int>> cows;
class segtree{
public:
int t[3000000];
void init(int x,int l,int r){
    if(l==r){
        t[x]=0;
        return;
    }
    int m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
    t[x]=t[2*x]+t[2*x+1];
}
void update(int p,int v,int x,int l,int r){
    if(l==r){
        t[x]+=v;
        return;
    }
    int m=(l+r)/2;
    if(p<=m)update(p,v,2*x,l,m);
    else update(p,v,2*x+1,m+1,r);
    t[x]=t[2*x]+t[2*x+1];
}
}up,down;
int query(int x,int l,int r,int lsu,int rsu,int lsd,int rsd){
    if (l==r) return min(max(max(up.t[x]+lsu,rsu),max(down.t[x]+lsd,rsd)),max(max(up.t[x]+rsu,lsu),max(down.t[x]+rsd,lsd)));
    int m=(l+r)/2;
    if(max(max(up.t[2*x]+lsu,rsu),max(down.t[2*x]+lsd,rsd))<max(max(up.t[2*x+1]+rsu,lsu),max(down.t[2*x+1]+rsd,lsd)))return query(2*x+1,m+1,r,lsu+up.t[2*x],rsu,lsd+down.t[2*x],rsd);
    else return query(2*x,l,m,lsu,rsu+up.t[2*x+1],lsd,rsd+down.t[2*x+1]);
}
int main(){
    freopen("balancing.in","r",stdin);
    freopen("balancing.out","w",stdout);
    cin>>n;
    int x,y;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        cows.push_back({x,y});
    }
    sort(cows.begin(),cows.end(),[](pair<int,int> a,pair<int,int> b){
        return a.second<b.second;
    });
    for(int i=0;i<n;i++) down.update(cows[i].first,1,1,1,ss);
    int actualans=query(1,1,ss,0,0,0,0);
    for(int i=1;i<n;i++){
        up.update(cows[i-1].first,1,1,1,ss);
        down.update(cows[i-1].first,-1,1,1,ss);
        if(cows[i].second!=cows[i-1].second){
            actualans=min(actualans,query(1,1,ss,0,0,0,0));
        }
    }
    cout<<actualans;
}