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
int n,q,p[100005],si[100005],dep[100005],fa[100005],he[100005],ord[100005],ordt=0,ordi[100005],top[100005];
vector<int> adj[100005];
vector<int> pos[100005];
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
//check if color c exists between range u and v
bool check(int u,int v,int c){
    int f=lower_bound(pos[c].begin(),pos[c].end(),u)-pos[c].begin();
    return f<pos[c].size()&&pos[c][f]<=v;
}
int main() {
    freopen("milkvisits.in","r",stdin);
    freopen("milkvisits.out","w",stdout);
    string anss="";
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>p[i];
    int u,v;
    for(int i=1;i<=n-1;i++){
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    top[1]=1;
    int c;
    dfs1(1,0);
    dfs2(1);
    for(int i=1;i<=n;i++) pos[p[ordi[i]]].pb(i);
    for(int i=1;i<=q;i++){
        cin>>u>>v>>c;
        int ans=0;
        while(top[u]!=top[v]){
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            ans=ans|check(ord[top[u]],ord[u],c);
            u=fa[top[u]];
        }
        if(dep[u]>dep[v]) swap(u,v);
        ans=ans|check(ord[u],ord[v],c);
        anss+=ans+'0';
    }
    cout<<anss<<endl;
    return 0;
}