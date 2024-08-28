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
int n,m,x,y,c[2000],ct=0,cn[2000][3000][2],dp[2000][3000][2];
vector<cpair<int,int>> adj[2000];
void dfs1(int x,int p,int d){
    if(p){
        cn[c[x]][min(y,d)][0]++;
        cn[c[x]][min(y,d)][1]+=d;
        cn[c[x]][min(y,d)][1]%=1000000007;
    }
    
    for(auto i: adj[x]){
        if(i.x==p) continue;
        c[i.x]=c[x];
        dfs1(i.x,x,d+i.y);
    }
}
signed main() {
    freopen("mooriokart.in","r",stdin);
    freopen("mooriokart.out","w",stdout);
    cin>>n>>m>>x>>y;
    y=max(x+1,y);
    int u,v,l;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>l;
        adj[u].pb({v,l});
        adj[v].pb({u,l});
    }
    for(int i=1;i<=n;i++){
        if(!c[i]) c[i]=++ct;
        dfs1(i,0,x);
    }
    dp[0][0][0]=1;
    for(int t=1;t<=ct;t++){
        for(int j=1;j<=y;j++){
            if(cn[t][j][0]==0) continue;
            for(int i=0;i<=y;i++){
                dp[t][min(i+j,y)][0]+=dp[t-1][i][0]*cn[t][j][0];
                dp[t][min(i+j,y)][0]%=1000000007;
                dp[t][min(i+j,y)][1]+=(dp[t-1][i][0]*cn[t][j][1]+dp[t-1][i][1]*cn[t][j][0]);
                dp[t][min(i+j,y)][1]%=1000000007;
            }
        }
        // for(int i=0;i<=y;i++){
        //     cout<<dp[t][i][1]<<" ";
        // }cout<<endl;
    }
    int fac=500000004;
    for(int i=2;i<ct;i++){
        fac*=i;
        fac%=1000000007;
    }
    cout<<(fac*dp[ct][y][1]) % 1000000007<<endl;
    return 0;
}