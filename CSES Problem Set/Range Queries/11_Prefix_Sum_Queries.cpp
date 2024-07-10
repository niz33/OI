#include<iostream>
using namespace std;
int n,q,t[600000],a[200005],lazy[600005];
void init(int x,int l,int r){
    if(l==r){
        t[x]=a[l];
        return;
    }
    int m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
    t[x]=max(t[2*x],t[2*x+1]);
}
void unlazy(int x,int l,int r){
    if(l!=r&&lazy[x]){
        int m=(l+r)/2;
        lazy[2*x]+=lazy[x];
        lazy[2*x+1]+=lazy[x];
        t[2*x]+=lazy[x];
        t[2*x+1]+=lazy[x];
        lazy[x]=0;
    }
}
void update(int l,int r,int v,int x,int lx,int rx){
    if(l<=lx&&rx<=r){
        t[x]+=v;
        lazy[x]+=v;
        return;
    }
    unlazy(x,lx,rx);
    int m=(lx+rx)/2;
    if(l<=m)update(l,r,v,2*x,lx,m);
    if(r>m)update(l,r,v,2*x+1,m+1,rx);
    t[x]=max(t[2*x],t[2*x+1]);
}
int query(int l,int r,int x,int lx,int rx){
    unlazy(x,lx,rx);
    if(l<=lx&&rx<=r)return t[x];
    int m=(lx+rx)/2;
    int res=-1e9;
    if(l<=m)res=max(res,query(l,r,2*x,lx,m));
    if(r>m)res=max(res,query(l,r,2*x+1,m+1,rx));
    return res;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
    init(1,1,n);
    int c,a,b;
    for(int i=0;i<q;i++){
        cin>>c>>a>>b;
        if(c==1)update(a,n,b,1,1,n);
        else cout<<query(a,b,1,1,n)-query(a-1,a-1,1,1,n)<<endl;
    }

}