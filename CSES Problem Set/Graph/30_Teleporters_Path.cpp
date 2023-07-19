#include<iostream>
#include<vector>
#include<set>
using namespace std;
int n,m,c[200005],vis[200005];
vector<int> s[200005];
void dfs(int x){
    vis[x]=1;
    for(int y:s[x]){
        if(!vis[y]){
              dfs(y);
        }
    }
}
void hei(int x){
    while(s[x].size()){
        int y=s[x][s[x].size()-1];
        s[x].pop_back();
        hei(y);
    }
    cout<<x<<" ";
}
int main(){
    cin>>n>>m;
    int u,v;
    
    for(int i=0;i<m;i++){
        cin>>u>>v;
        s[v].push_back(u);
        c[u]++;
    }
    dfs(n);
    if(s[n].size()!=c[n]+1||s[1].size()!=c[1]-1){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    for(int i=2;i<n;i++){
        if(c[i]!=s[i].size()||(!vis[i]&&(s[i].size()))){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    hei(n);
}