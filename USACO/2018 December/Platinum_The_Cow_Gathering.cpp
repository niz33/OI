#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<stack>
using namespace std;
#define ll long long
#define pb push_back
int n,m,lia[100005],ac[100005],gone[100005],dp[100005],vis[100005];
vector<int> adj[100005];
vector<int> aft[100005];
void dfs(int x,int f){
    dp[x]=(dp[x]|dp[f]);
    for(int y:adj[x]){
        if(y==f) continue;
        dfs(y,x);
    }

}
int main() {
    freopen("gathering.in","r",stdin);
    freopen("gathering.out","w",stdout);
    cin>>n>>m;
    int a,b;
    for(int i=1;i<=n-1;i++){
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
        ac[a]++;
        ac[b]++;
    }
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        aft[a].pb(b);
        lia[b]++;
        dp[a]=1;
    }
    stack<int> s;
    int cnt=0,last;
    for(int i=1;i<=n;i++) if(ac[i]==1&&!lia[i]) s.push(i);
    while(!s.empty()){
        int x=s.top();
        s.pop();
        for(int y:aft[x]){
            lia[y]--;
            if(!lia[y]&&ac[y]==1&&!vis[y]) s.push(y),vis[y]=1;
        }
        for(int y:adj[x]){
            if(gone[y]) continue;
            ac[y]--;
            if(ac[y]==1&&!lia[y]&&!vis[y]) s.push(y),vis[y]=1;
        }
        last=x;
        cnt++;
        gone[x]=1;
    }
    if(cnt!=n){
        for(int i=1;i<=n;i++) cout<<0<<endl;
        return 0;
    }
    //cout<<last<<endl;
    dfs(last,0);
    for(int i=1;i<=n;i++) cout<<1-dp[i]<<endl;
    return 0;
}