#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
int n,k,bl[50005][20],dep[50005],dp[50005];
vector<int> adj[50005];
void dfs(int x,int f){
    dep[x]=dep[f]+1;
    for(int i=0;i<adj[x].size();i++){
        if(adj[x][i]==f) continue;
        bl[adj[x][i]][0]=x;
        dfs(adj[x][i],x);
    }
}
int lca(int x,int y){
    if(x==y) return x;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[bl[x][i]]>=dep[y]) x=bl[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(bl[x][i]!=bl[y][i]) x=bl[x][i],y=bl[y][i];
    return bl[x][0];
}
void dpp(int x,int f){
    for(int i=0;i<adj[x].size();i++){
        if(adj[x][i]==f) continue;
        dpp(adj[x][i],x);
        dp[x]+=dp[adj[x][i]];
    }
}
int main() {
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);
    cin>>n>>k;
    int u,v,w;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    for(int i=1;i<20;i++) for(int j=1;j<=n;j++) bl[j][i]=bl[bl[j][i-1]][i-1];
    for(int i=1;i<=k;i++){
        cin>>u>>v;
        w=lca(u,v);
        dp[u]+=1;
        dp[v]+=1;
        dp[w]-=1;
        dp[bl[w][0]]-=1;
    }
    dpp(1,0);
    int max=0;
    for(int i=1;i<=n;i++) if(dp[i]>max) max=dp[i];
    cout<<max<<endl;
    return 0;
}