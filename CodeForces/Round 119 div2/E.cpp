#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
int n,m,vis[100005],siz[100005],f[100005],cl[100005];
vector<int> dist[100005];
vector<int> adj[100005];
void dist_size(int x,int p){
    siz[x]=1;
    for(int y:adj[x]) if((!vis[y])&&y!=p){
        dist[y].pb(dist[x][dist[x].size()-1]+1);
        dist_size(y,x);
        siz[x]+=siz[y];
    }
}
void build(int x,int s,int fa){
    //cout<<"-------------"<<endl;
    //cout<<x<<endl;
    bool b=true;
    int lx=0;
    while(b){
        b=false;
        for(int y:adj[x]) if(!vis[y]&&siz[y]>s/2&&y!=lx){
            b=true;
            lx=x;
            x=y;
            //cout<<x<<endl;
            break;
        }
    }
    f[x]=fa;
    vis[x]=1;
    dist[x].pb(0);
    dist_size(x,0);

    // for(int y:adj[x]) if(!vis[y]){
    //     cout<<y<<" ";
    // }cout<<endl;
    for(int y:adj[x]) if(!vis[y]) build(y,siz[y],x);
    
}
void update(int x){
    //cout<<"update---------"<<x<<endl;
    int xx=x,i=dist[x].size()-1;
    while(xx){
        //cout<<xx<<" "<<dist[x][i]<<endl;
        cl[xx]=min(cl[xx],dist[x][i]);
        xx=f[xx];
        i--;
    }
    //for(int t=1;t<=n;t++) cout<<cl[t]<<" ";cout<<endl;
}
int query(int x){
    //cout<<"query---------"<<x<<endl;
    int xx=x,i=dist[x].size()-1,ans=1e9;
    while(xx){
        //cout<<xx<<" "<<dist[x][i]<<endl;
        ans=min(ans,cl[xx]+dist[x][i]);
        xx=f[xx];
        i--;
    }
    //for(int t=1;t<=n;t++) cout<<cl[t]<<" ";cout<<endl;
    return ans;
}
int main() {
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=n-1;i++){
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=1;i<=n;i++) cl[i]=1e9;
    dist[1].pb(0);
    dist_size(1,0);
    build(1,n,0);
    // for(int i=1;i<=n;i++){
    //    cout<<f[i]<<" ";
    // }cout<<endl;
    update(1);
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        if(u==1) update(v);
        else cout<<query(v)<<endl;
    }
    return 0;
}