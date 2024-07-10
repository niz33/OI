#include<iostream>
using namespace std;
long long n,q,a[1000005],t[3000000],lazy[3000000],lazys[3000000];
void init(int x,int l,int r){
    if(l==r) {t[x]=a[l]; return;}
    int m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
    t[x]=t[2*x]+t[2*x+1];
}
long long sum(long long l,long long r,long long v,long long s){
    return (2*v+s*(r-l))*(r-l+1)/2;
}
void unlazy(long long x,long long l,long long r){
    if(l!=r&&lazy[x]!=0){
        long long m=(l+r)/2;
        lazy[2*x]+=lazy[x];
        lazys[2*x]+=lazys[x];
        lazy[2*x+1]+=lazy[x]+(m+1-l)*lazys[x];
        lazys[2*x+1]+=lazys[x];
        t[2*x]+=sum(l,m,lazy[x],lazys[x]);
        t[2*x+1]+=sum(m+1,r,lazy[x]+(m+1-l)*lazys[x],lazys[x]);
        lazy[x]=0;
        lazys[x]=0;
    }
}
void update(long long l,long long r,long long v,long long x,long long lx,long long rx){
    if(l<=lx&&rx<=r){
        lazy[x]+=v+lx-l;
        lazys[x]+=1;
        t[x]+=sum(lx,rx,v+lx-l,1);
        return;
    }
    unlazy(x,lx,rx);
    long long m=(lx+rx)/2;
    if(l<=m)update(l,r,v,2*x,lx,m);
    if(r>m)update(l,r,v,2*x+1,m+1,rx);
    t[x]=t[2*x]+t[2*x+1];
}
long long query(long long l,long long r,long long x,long long lx,long long rx){
    unlazy(x,lx,rx);
    if(l<=lx&&rx<=r){return t[x];}
    long long m=(lx+rx)/2;
    long long res=0;
    if(l<=m)res+=query(l,r,2*x,lx,m);
    if(r>m)res+=query(l,r,2*x+1,m+1,rx);
    return res;
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    int c,l,r;
    init(1,1,1000000);
    for(int i=0;i<q;i++){
        cin>>c>>l>>r;
        if(c==1)update(l,r,1,1,1,1000000);
        else cout<<query(l,r,1,1,1000000)<<endl;
    }
}