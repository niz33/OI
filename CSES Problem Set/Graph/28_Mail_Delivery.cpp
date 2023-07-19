#include<iostream>
#include<vector>
#include<set>
using namespace std;
int n,m,vis[200005];
set<int> s[200005];
void dfs(int x){
    vis[x]=1;
    for(int y:s[x]){
        y-=x;
        if(!vis[y]){
            dfs(y);
        }
    }
}
void hei(int x){
    //cout<<x<<" ";
    while(s[x].size()){
        int y=*s[x].begin()-x;
        s[x].erase(s[x].begin());
        s[y].erase(s[y].find(x+y));
        hei(y);
    }
    cout<<x<<" ";
}
int main(){
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        s[u].insert(u+v);
        s[v].insert(u+v);
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        if(((!vis[i])&&(s[i].size()))||(s[i].size()&1)){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    hei(1);
}