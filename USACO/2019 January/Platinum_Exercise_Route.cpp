#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define int long long
#define pb push_back
template<typename T1,typename T2> struct cpair{T1 x;T2 y;};
template<typename T1,typename T2> struct rpair{T1 l;T2 r;};
template<typename T1,typename T2> struct epair{T1 u;T2 v;};
bool operator<(epair<int,int> a,epair<int,int> b){return a.u<b.u||(a.u==b.u&&a.v<b.v);}
int n,m,bl[200005][20],dp[200005],dep[200005];
vector<int> adj[200005];
map<epair<int,int>,int> ss[200005];
void dfs1(int x,int f){
    bl[x][0]=f;
    dep[x]=dep[f]+1;
    for(int i=1;i<20;i++)bl[x][i]=bl[bl[x][i-1]][i-1];
    for(int i:adj[x])if(i!=f)dfs1(i,x);
}
void dfs2(int x){
    dp[x]+=dp[bl[x][0]];
    for(int i:adj[x])if(i!=bl[x][0])dfs2(i);
}
int get_lca(int u,int v,int b){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=19;i>=0;i--)if(dep[bl[u][i]]>=dep[v])u=bl[u][i];
    if(u==v)return u;
    for(int i=19;i>=0;i--)if(bl[u][i]!=bl[v][i])u=bl[u][i],v=bl[v][i];
    if(b) ss[bl[u][0]][{min(u,v),max(u,v)}]++;
    return bl[u][0];
}
int get_top(int x,int lca){
    for(int i=19;i>=0;i--)if(dep[bl[x][i]]>dep[lca])x=bl[x][i];
    return x;
}
vector<epair<int,int>> es;
signed main() {
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    cin>>n>>m;
    int u,v,ans=0;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=0;i<=m-n;i++){
        cin>>u>>v;
        es.pb({u,v});
    }
    dfs1(1,0);
    for(auto e:es){
        int lca=get_lca(e.u,e.v,1);
        //cout<<e.u<<" "<<e.v<<" "<<lca<<endl;
        if(lca!=e.u) dp[get_top(e.u,lca)]++;
        if(lca!=e.v) dp[get_top(e.v,lca)]++;
    }
    //for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<endl;
    dfs2(1);
    for(auto e:es){
        int lca=get_lca(e.u,e.v,0);
        ans+=dp[e.u]+dp[e.v]-2ll*dp[lca];
    }
    //cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        int s=dp[i]-dp[bl[i][0]];
        ans+=s*(s-1ll)/2ll-s*s;
        //cout<<i<<" "<<ans<<endl;
        for(auto e:ss[i]) ans-=e.second*(e.second-1ll)/2ll;
        //cout<<i<<" "<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}