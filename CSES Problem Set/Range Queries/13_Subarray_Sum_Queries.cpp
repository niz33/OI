#include<iostream>
using namespace std;
int n,m,a[200005];
int tm[600000],tl[600000],tr[600000],ts[600000];
void update(int x,int l,int r){
    ts[x]=ts[2*x]+ts[2*x+1];
    tl[x]=std::max(tl[2*x],ts[2*x]+tl[2*x+1]);
    tr[x]=std::max(tr[2*x+1],ts[2*x+1]+tr[2*x]);
    tm[x]=std::max(std::max(tm[2*x],tm[2*x+1]),tr[2*x]+tl[2*x+1]);
}
void init(int x,int l,int r){
    if(l==r){
        ts[x]=a[l];
        tm[x]=tl[x]=tr[x]=a[l];
        return;
    }
    int m=(l+r)/2;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
    update(x,l,r);
}
void change(int p,int v,int x,int l,int r){
    if(l==r){
        ts[x]=a[l]=v;
        tl[x]=tr[x]=ts[x]=std::max(0,v);
        return;
    }
    int m=(l+r)/2;
    if(p<=m) change(p,v,2*x,l,m);
    else change(p,v,2*x+1,m+1,r);
    update(x,l,r);
}
void printt(int x,int l,int r){
    cout<<x<<" "<<l<<" "<<r<<": "<<tm[x]<<" "<<tl[x]<<" "<<tr[x]<<" "<<ts[x]<<endl;
    if(l==r){  
        return;
    }
    int m=(l+r)/2;
    printt(2*x,l,m);
    printt(2*x+1,m+1,r);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    init(1,1,n);
    for(int i=0;i<m;i++){
        int p,v;
        cin>>p>>v;
        change(p,v,1,1,n);
        printt(1,1,n);
        cout<<tm[1]<<endl;
    }
}