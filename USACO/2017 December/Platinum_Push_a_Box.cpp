#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define ll long long
#define pb push_back
int n,m,q,cf[1505][1505],c[1505][1505],ct,dp[1505][1505][4],dep[1505][1505],vis[1505][1505];
vector<int> ch[1505][1505];
char a[1505][1505];
pair<int,int> s,t,dir[4]={{0,1},{1,0},{0,-1},{-1,0}};
vector<pair<pair<int,int>,pair<int,int>>> sid;
queue<pair<pair<int,int>,int>> qu;
void dfs1(int x,int y,int d){
    vis[x][y]=1;
    dep[x][y]=d;
    for(int i=0;i<4;i++){
        int ux=x+dir[i].first,uy=y+dir[i].second;
        if(ux<1||ux>n||uy<1||uy>m||a[ux][uy]=='#') continue;
        if(vis[ux][uy]){
            sid.pb({{x,y},{ux,uy}});
            continue;
        }
        ch[x][y].pb(i);
        dfs1(ux,uy,d+1);
    }
}
void dfs2(int x,int y){
    for(int i:ch[x][y]){
        int ux=x+dir[i].first,uy=y+dir[i].second;
        dfs2(ux,uy);
        cf[x][y]+=cf[ux][uy];
    }
}
void dfs3(int x,int y,int t){
    if(cf[x][y]==0) t=++ct;
    c[x][y]=t;
    for(int i:ch[x][y]){
        int ux=x+dir[i].first,uy=y+dir[i].second;
        dfs3(ux,uy,t);
    }
}
void dfs4(int x,int y){
    vis[x][y]=1;
    for(int i=0;i<4;i++){
        int ux=x+dir[i].first,uy=y+dir[i].second;
        if(ux<1||ux>n||uy<1||uy>m||a[ux][uy]=='#'||vis[ux][uy]) continue;
        if(a[ux][uy]=='B'){
            dp[ux][uy][(i+2)%4]=1;
            //cout<<ux<<" "<<uy<<" "<<(i+2)%4<<endl;
            qu.push({{ux,uy},(i+2)%4});
            //return;
        }
        dfs4(ux,uy);
    }
}
void bfs(){
    while(!qu.empty()){
        pair<int,int> u=qu.front().first;
        int d=qu.front().second;
        pair<int,int> v={u.first+dir[d].first,u.second+dir[d].second};
        for(int i=0;i<4;i++){
            pair<int,int> w={u.first+dir[i].first,u.second+dir[i].second};
            if(w.first<1||w.first>n||w.second<1||w.second>m||a[w.first][w.second]=='#'||dp[u.first][u.second][i]) continue;
            if(c[v.first][v.second]!=c[w.first][w.second]) continue;
            dp[u.first][u.second][i]=1;
            qu.push({u,i});
        }
        pair<int,int> w={u.first-dir[d].first,u.second-dir[d].second};
        if(w.first<1||w.first>n||w.second<1||w.second>m||a[w.first][w.second]=='#'||dp[w.first][w.second][d]) {qu.pop();continue;}
        dp[w.first][w.second][d]=1;
        qu.push({w,d});
        qu.pop();
    }
}
int main() {
    freopen("6.in","r",stdin);
    freopen("6.out","w",stdout);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
        cin>>a[i][j];
        if(a[i][j]=='A') s={i,j};
        if(a[i][j]=='B') t={i,j};
    }
    dfs1(s.first,s.second,1);
    for(auto si:sid){
        //cout<<si.first.first<<" "<<si.first.second<<" "<<si.second.first<<" "<<si.second.second<<endl;
        pair<int,int> u=si.first,v=si.second;
        if(dep[u.first][u.second]>dep[v.first][v.second]) swap(u,v);
        cf[u.first][u.second]--;
        cf[v.first][v.second]++;
    }
    cf[s.first][s.second]++;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cf[i][j]+=(signed)ch[i][j].size()-1;
            //if(a[i][j]=='#') cout<<"# ";
            
            //else cout<<cf[i][j]<<" ";
        }
        //cout<<endl;
    }
    //cout<<endl;
    dfs2(s.first,s.second);
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         if(a[i][j]=='#') cout<<"# ";
    //         else cout<<cf[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    dfs3(s.first,s.second,0);
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         if(a[i][j]=='#') cout<<"# ";
    //         else cout<<c[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) vis[i][j]=0;
    dfs4(s.first,s.second);
    bfs();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='#') cout<<"#";
            else cout<<(dp[i][j][0]||dp[i][j][1]||dp[i][j][2]||dp[i][j][3]);
        }
        cout<<endl;
    }
    int x,y;
    for(int i=1;i<=q;i++){
        cin>>x>>y;
        //if(dp[x][y][0]||dp[x][y][1]||dp[x][y][2]||dp[x][y][3]||a[x][y]=='B') cout<<"YES"<<endl;
        //else cout<<"NO"<<endl;
    }
    

    return 0;
}
