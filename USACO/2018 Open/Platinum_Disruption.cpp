#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
int n,m,ans[500005],bl[50005][20],dep[50005];
map<pair<int,int>,int> mp;
vector<int> adj[50005];
vector<int> add[50005];
vector<int> rem[50005];
multiset<int> s[50005];
void init(int x,int ff){
    bl[x][0]=ff;
    dep[x]=dep[ff]+1;
    for(int y:adj[x]) if(y!=ff) init(y,x);
}
int lca(int x,int y){
    if(x==y) return x;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[bl[x][i]]>=dep[y]) x=bl[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(bl[x][i]!=bl[y][i]) x=bl[x][i],y=bl[y][i];
    return bl[x][0];
}
void getans(int x,int ff){
    for(int y:adj[x]) if(y!=ff){
        getans(y,x);
        if(s[y].size()>s[x].size()) swap(s[x],s[y]);
        for(int i:s[y]) s[x].insert(i);
    } 
    for(int i:add[x]) s[x].insert(i);
    for(int i:rem[x]) s[x].erase(s[x].find(i)),s[x].erase(s[x].find(i));
    if(s[x].size()) ans[mp[{x,ff}]]=*s[x].begin();
    else ans[mp[{x,ff}]]=-1;
    // cout<<"----------"<<endl;
    // cout<<x<<" "<<ff<<endl;
    // for(int i:s[x]) cout<<i<<" ";
    // cout<<endl;
}
int main() {
    freopen("disrupt.in","r",stdin);
    freopen("disrupt.out","w",stdout);
    int u,v,p,w;
    cin>>n>>m;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        mp[{u,v}]=i;
        mp[{v,u}]=i;
    }
    init(1,0);
    for(int i=1;i<20;i++) for(int j=1;j<=n;j++) bl[j][i]=bl[bl[j][i-1]][i-1];
    for(int i=1;i<=m;i++){
        cin>>u>>v>>p;
        w=lca(u,v);
        add[u].push_back(p);
        add[v].push_back(p);
        rem[w].push_back(p);
    }
    getans(1,0);
    for(int i=1;i<n;i++) cout<<ans[i]<<endl;
    return 0;
}