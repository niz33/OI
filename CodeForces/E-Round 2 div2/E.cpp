#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define int long long
#define pb push_back
int n,c[100005],ans[100005],l[100005];
vector<int> adj[100005];
map<int,int> cnt[100005];
set<int> ex[100005];
void dfs(int x,int f){
    for(int y:adj[x]){
        if(y==f) continue;
        dfs(y,x);
        if(ex[x].size()<ex[y].size()) swap(ex[x],ex[y]),swap(cnt[x],cnt[y]),ans[x]=ans[y],l[x]=l[y];
        for(int i:ex[y]){
            ex[x].insert(i),cnt[x][i]+=cnt[y][i];
            if(cnt[x][i]==l[x]) ans[x]+=i;
            else if(cnt[x][i]>l[x]) l[x]=cnt[x][i],ans[x]=i;
        }
    }
}
signed main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i],cnt[i][c[i]]++,ex[i].insert(c[i]),l[i]=1,ans[i]=c[i];
    int u,v;
    for(int i=1;i<=n-1;i++){
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    return 0;
}