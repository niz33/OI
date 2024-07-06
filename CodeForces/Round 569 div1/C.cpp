#include<iostream>
using namespace std;
int t[4000005],lazy[4000005];
int n,m,q,a[300005],b[300005];
void init(int x,int l,int r){
    if(l==r){
        t[x]=0;
        return;
    }
    int m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
}
void unlazy(int x,int l,int r){
    if(lazy[x]&&l!=r){
        t[2*x]+=lazy[x];
        t[2*x+1]+=lazy[x];
        lazy[2*x]+=lazy[x];
        lazy[2*x+1]+=lazy[x];
        lazy[x]=0;
    }
}
void add(int l,int r,int v,int x,int xl,int xr){
    if(l<=xl&&xr<=r){
        t[x]+=v;
        lazy[x]+=v;
        return;
    }
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    if(l<=m) add(l,r,v,2*x,xl,m);
    if(r>m) add(l,r,v,2*x+1,m+1,xr);
    t[x]=std::max(t[2*x],t[2*x+1]);
}
int get(int k,int x,int xl,int xr){
    if(xl==xr) return xl;
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    if(t[2*x]>=k) return get(k,2*x,xl,m);
    return get(k,2*x+1,m+1,xr);
}
int find(int x,int l,int r){
    if(l==r) return l;
    unlazy(x,l,r);
    if(t[x*2+1]>0) return find(x*2+1,(l+r)/2+1,r);
    return find(x*2,l,(l+r)/2);
}
int main(){
    cin>>n>>m;
    init(1,1,1000000);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        add(1,a[i],1,1,1,1000000);
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
        add(1,b[i],-1,1,1,1000000);
    }
    cin>>q;
    for(int i=0;i<q;i++){
        int type,x,v;
        cin>>type>>x>>v;
        if(type==1){
            add(1,a[x],-1,1,1,1000000);
            a[x]=v;
            add(1,a[x],1,1,1,1000000);
        }
        else{
            add(1,b[x],1,1,1,1000000);
            b[x]=v;
            add(1,b[x],-1,1,1,1000000);
        }
        if(t[1]<=0){
            cout<<-1<<endl;
            continue;
        }
        cout<<find(1,1,1000000)<<endl;
    }
}