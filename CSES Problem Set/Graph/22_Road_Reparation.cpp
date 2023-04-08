#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector<pair<long long,long long>> s[100005];
priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> edges;
long long n,m,vis[100005],ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        s[u].push_back({w,v});
        s[v].push_back({w,u});
    }
    edges.push({0,1});
    while(!edges.empty()){
        int x=edges.top().second;
        //cout<<x<<endl;
        if(vis[x]){
            edges.pop();
            continue;
        }
        ans+=edges.top().first;
        edges.pop();
        vis[x]=1;
        for(pair<int,int> y : s[x]){
            edges.push({y});
        }
        
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    cout<<ans;
}