#include<iostream>
using namespace std;
int n,m;
int lt[1500005],rt[1500005],mt[1500005],lazy[1500005];
int ans;
void init(int x,int l,int r){
    lt[x]=rt[x]=mt[x]=r-l+1;
    if(l==r) return;
    int m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
}
void update(int x,int l,int r){
    int m=(l+r)/2;
    if(lt[x*2]==m-l+1) lt[x]=lt[x*2]+lt[x*2+1];
    else lt[x]=lt[x*2];
    if(rt[x*2+1]==r-m) rt[x]=rt[x*2+1]+rt[x*2];
    else rt[x]=rt[x*2+1];
    mt[x]=max(max(mt[x*2],mt[x*2+1]),rt[x*2]+lt[x*2+1]);
}
void unlazy(int x,int l,int r){
    if(lazy[x]==1&&l!=r){
        int m=(l+r)/2;
        lazy[2*x]=lazy[2*x+1]=lazy[x];
        lt[2*x]=rt[2*x]=mt[2*x]=m-l+1;
        lt[2*x+1]=rt[2*x+1]=mt[2*x+1]=r-m;
        lazy[x]=0;
    }
    if(lazy[x]==2&&l!=r){
        lazy[2*x]=lazy[2*x+1]=lazy[x];
        lt[2*x]=rt[2*x]=mt[2*x]=0;
        lt[2*x+1]=rt[2*x+1]=mt[2*x+1]=0;
        lazy[x]=0;
    }
}
void erase(int l,int r,int x,int xl,int xr){
    if(l<=xl&&xr<=r){
        lt[x]=rt[x]=mt[x]=xr-xl+1;
        lazy[x]=1;
        return;
    }
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    if(l<=m) erase(l,r,2*x,xl,m);
    if(r>m) erase(l,r,2*x+1,m+1,xr);
    update(x,xl,xr);
}
void add(int l,int r,int x,int xl,int xr){
    if(l<=xl&&xr<=r){
        lt[x]=rt[x]=mt[x]=0;
        lazy[x]=2;
        return;
    }
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    if(l<=m) add(l,r,2*x,xl,m);
    if(r>m) add(l,r,2*x+1,m+1,xr);
    update(x,xl,xr);
}  
int find(int v,int x,int l, int r){
    unlazy(x,l,r);
    int m=(l+r)/2;
    if(mt[x*2]>=v) return find(v,x*2,l,m);
    if(rt[x*2]+lt[x*2+1]>=v) return m-rt[x*2]+1;
    return find(v,x*2+1,m+1,r);
}

int main(){
    cin>>n>>m;
    int a,b;
    char c;
    init(1,1,n);
    for(int i=1;i<=m;i++){
        cin>>c;
        if(c=='A'){
            cin>>a;
            if(mt[1]<a) ans++;
            else{
                int f=find(a,1,1,n);
                add(f,f+a-1,1,1,n);
            }
        }
        else{
            cin>>a>>b;
            erase(a,b,1,1,n);
        }
    }
    cout<<ans;
}