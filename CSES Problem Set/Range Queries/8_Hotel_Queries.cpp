#include<iostream>
using namespace std;
int n,q;
int a[200005],t[500000];
void build(int x,int l,int r){
    if(l==r){
        t[x]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(2*x,l,m);
    build(2*x+1,m+1,r);
    t[x]=max(t[2*x],t[2*x+1]);
}
void update(int x,int l,int r,int p,int v){
    if(l==r){
        t[x]-=v;
        return;
    }
    int m=(l+r)/2;
    if(p<=m) update(2*x,l,m,p,v);
    else update(2*x+1,m+1,r,p,v);
    t[x]=max(t[2*x],t[2*x+1]);
}
void find(int x,int l,int r,int v){
    if(l==r){
        cout<<l<<endl;
        update(1,1,n,l,v);
        return;
    }
    int m=(l+r)/2;
    if(t[2*x]>=v) find(2*x,l,m,v);
    else find(2*x+1,m+1,r,v);
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for(int i=0;i<q;i++){
        int p;
        cin>>p;
        if(t[1]<p) cout<<0<<endl;
        else find(1,1,n,p);
    }
}