#pragma GCC optimize(3,"Ofast","inline")
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
int n,q,p[200005],si[200005],t[600000],dep[200005],fa[200005],he[200005],ord[200005],ordt=0,ordi[200005],top[200005];
vector<int> adj[200005];
inline void init(int x,int l,int r){
    if(l==r){
        t[x]=p[ordi[l]];
        return;
    }
    int m=(l+r)>>1;
    init(2*x,l,m);
    init(2*x+1,m+1,r);
    t[x]=max(t[2*x],t[2*x+1]);
}
inline void update(int p,int v,int x,int l,int r){
    if(l==r){
        t[x]=v;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m) update(p,v,2*x,l,m);
    else update(p,v,2*x+1,m+1,r);
    t[x]=max(t[2*x],t[2*x+1]);
}
inline int query(int l,int r,int x,int lx,int rx){
    if(l<=lx&&rx<=r){
        return t[x];
    }
    int m=(lx+rx)/2;
    if(r<=m) return query(l,r,2*x,lx,m);
    if(l>m) return query(l,r,2*x+1,m+1,rx);
    return max(query(l,r,2*x,lx,m),query(l,r,2*x+1,m+1,rx));
}
inline void dfs1(int x, int f){
    si[x]=1;
    fa[x]=f;
    dep[x]=dep[f]+1;
    int h=0;
    for(int y:adj[x]){
        if(y==f) continue;
        dfs1(y,x);
        si[x]+=si[y];
        if(si[y]>h) he[x]=y,h=si[y];
    }
}
inline void dfs2(int x){
    ord[x]=++ordt;
    ordi[ordt]=x;
    if(!he[x]) return;
    top[he[x]]=top[x];
    dfs2(he[x]);
    for(int y:adj[x]){
        if(y==fa[x]||y==he[x]) continue;
        top[y]=y;
        dfs2(y);
    }
}
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57)
    {
        if(ch=='-') f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
   	return x*f;
}
int main() {
    n=read(),q=read();
    for(int i=1;i<=n;i++) p[i]=read();
    int u,v;
    for(int i=1;i<=n-1;i++){
        u=read(),v=read();
        adj[u].pb(v);
        adj[v].pb(u);
    }
    top[1]=1;
    dfs1(1,0);
    dfs2(1);
    init(1,1,n);
    int c;
    for(int i=1;i<=q;i++){
        c=read(),u=read(),v=read();
        if(c==1) update(ord[u],v,1,1,n);
        else{
            int ans=0;
            while(top[u]!=top[v]){
                if(dep[top[u]]<dep[top[v]]) swap(u,v);
                ans=max(ans,query(ord[top[u]],ord[u],1,1,n));
                u=fa[top[u]];
            }
            if(dep[u]>dep[v]) swap(u,v);
            ans=max(ans,query(ord[u],ord[v],1,1,n));
            cout<<ans<<endl;
        }
    }
    return 0;
}