#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define int long long
int n,l;
vector<pair<int,int>> adj[200005];
int bl[200005][20],dep[200005],dp[200005];
void init(int x, int dept){
    dep[x]=dep[bl[x][0]]+dept;
    for(auto y:adj[x]) init(y.first,y.second);
}
void getans(int x){
    for(auto i:adj[x]){
        getans(i.first);
        dp[x]+=dp[i.first];
    }
}
signed main(){
    freopen("runaway.in","r",stdin);
    freopen("runaway.out","w",stdout);
    int f,d;
    cin>>n>>l;
    for(int i=2;i<=n;i++){
        cin>>f>>d;
        adj[f].push_back({i,d});
        bl[i][0]=f;
    }
    for(int i=1;i<20;i++) for(int j=1;j<=n;j++) bl[j][i]=bl[bl[j][i-1]][i-1];
    init(1,0);
    for(int i=1;i<=n;i++){
        int ni=i;
        for(int j=19;j>=0;j--) if(dep[i]-dep[bl[ni][j]]<=l) ni=bl[ni][j];
        dp[i]++;
        dp[bl[ni][0]]--;
    }
    getans(1);
    for(int i=1;i<=n;i++) cout<<dp[i]<<endl;
    return 0;
}