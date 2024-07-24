#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
int n,p[100005],ans[100005];
vector<int> adj[100005];
set<int> ps[100005];
namespace std {
    void swap(set<int> &a, set<int> &b) { a.swap(b); }
}
void dfs(int x){
    for(int y:adj[x]){
        dfs(y);
        if(ps[x].size()<ps[y].size()) swap(ps[x],ps[y]);
        for(int i:ps[y]) ps[x].insert(i);
    }
    ans[x]=distance(ps[x].upper_bound(p[x]),ps[x].end());
}
int main() {
    freopen("promote.in","r",stdin);
    freopen("promote.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i],ps[i].insert(p[i]);
    int f;
    for(int i=2;i<=n;i++){
        cin>>f;
        adj[f].pb(i);
    }
    dfs(1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}