#include<iostream>
using namespace std;
long long n,q,t[800000],a[200005],lazy[800000];
void init(long long x,long long l,long long r){
    if(l==r){
        t[x]=a[l];
        return;
    }
    long long m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
    t[x]=max(t[2*x],t[2*x+1]);
}
void unlazy(long long x,long long l,long long r){
    if(l!=r&&lazy[x]!=0){
        lazy[2*x]+=lazy[x];
        lazy[2*x+1]+=lazy[x];
        t[2*x]+=lazy[x];
        t[2*x+1]+=lazy[x];
        lazy[x]=0;
    }
}
void update(long long l,long long r,long long v,long long x,long long lx,long long rx){
    if(l<=lx&&rx<=r){
        t[x]+=v;
        lazy[x]+=v;
        return;
    }
    unlazy(x,lx,rx);
    long long m=(lx+rx)/2;
    if(l<=m)update(l,r,v,2*x,lx,m);
    if(r>m)update(l,r,v,2*x+1,m+1,rx);
    t[x]=max(t[2*x],t[2*x+1]);
}
long long query(long long l,long long r,long long x,long long lx,long long rx){
    if(l==0){
        return 0;
    }
    if(l<=lx&&rx<=r)return t[x];
    unlazy(x,lx,rx);
    long long m=(lx+rx)/2;
    long long res=0;
    if(l<=m)res=max(res,query(l,r,2*x,lx,m));
    if(r>m)res=max(res,query(l,r,2*x+1,m+1,rx));
    return res;
}
signed main(){
    cin>>n>>q;
    for(long long i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
    init(1,1,n);
    for(long long i=n;i>=1;i--)a[i]=a[i]-a[i-1];
    long long c,aa,b;
    for(long long i=0;i<q;i++){
        cin>>c>>aa>>b;
        if(c==1)update(aa,n,b-a[aa],1,1,n),a[aa]=b;
        else cout<<max(0ll,query(aa,b,1,1,n)-query(aa-1,aa-1,1,1,n))<<endl;
    }

}