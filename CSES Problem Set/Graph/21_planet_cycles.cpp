#include<iostream>
using namespace std;
int n,t[200005],dis[200005],vis[200005],loop[200005];
void dfs(int x,int ord){
    vis[x]=ord;
    if(dis[t[x]]){
        dis[x]=dis[t[x]]+1;
        loop[x]=0;
    }
    else if(vis[t[x]]){
        loop[x]=t[x];
        dis[x]=vis[x]-vis[t[x]]+1;
        if(loop[x]==x){
            loop[x]=0;
        }
    }
    else{
        dfs(t[x],ord+1);
        if(loop[t[x]]){
            dis[x]=dis[t[x]];
            if(loop[t[x]]==x){
                loop[x]=0;
            }
            else{
                loop[x]=loop[t[x]];
            }
        }
        else{
            dis[x]=dis[t[x]]+1;
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,1);
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dis[i]<<" ";
    }
}