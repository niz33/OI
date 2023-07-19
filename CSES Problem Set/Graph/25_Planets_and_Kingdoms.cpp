#include<iostream>
#include<vector>
using namespace std;
int n,m,vis[100005],low[100005],scc[100005],viscnt,inst[100005],st[100005],stt,scccnt;
vector<int> s[100005];
void tarjan(int x){
    vis[x]=++viscnt;
    low[x]=vis[x];
    inst[x]=1;
    st[++stt]=x;
    for(int y:s[x]){
        if(!vis[y]){
            tarjan(y);
            low[x]=min(low[y],low[x]);
        }
        else if(inst[y]){
            low[x]=min(low[x],low[y]);
        }
    }
    if(vis[x]==low[x]){
        scccnt++;
        while(st[stt]!=x){
            scc[st[stt]]=scccnt;
            inst[st[stt]]=0;
            stt--;
        }
        scc[x]=scccnt;
        inst[x]=0;
        stt--;
    }
}
int main(){
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        s[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            tarjan(i);
        }
        //cout<<i<<" "<<vis[i]<<" "<<low[i]<<endl;
        
    }
    cout<<scccnt<<endl;
    for(int i=1;i<=n;i++){
        cout<<scc[i]<<" ";
    }
}