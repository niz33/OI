#include<iostream>
using namespace std;
int n,q,tar[200005],vis[200005],co[200005],dep[200005],cotop=0,jump[200005][20],ord[200005],si[200005];
int dfs(int x){
    if(vis[tar[x]]==1){
        co[x]=++cotop;
        dep[x]=0;
        ord[x]=1;
        vis[x]=2;
        return tar[x];
    }
    if(vis[tar[x]]==2){
        co[x]=co[tar[x]];
        dep[x]=dep[tar[x]]+1;
        vis[x]=2;
        return 0;
    }
    vis[x]=1;
    int res=dfs(tar[x]);
    vis[x]=2;
    co[x]=co[tar[x]];
    if(res!=0){
        dep[x]=0;
        ord[x]=ord[tar[x]]+1;
        if(res==x){
            si[co[x]]=ord[x];
            return 0;
        }
    }
    else dep[x]=dep[tar[x]]+1;
    return res;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>tar[i];
        if(tar[i]==i){
            co[i]=++cotop;
            ord[i]=1;
            si[cotop]=1;
            dep[i]=0;
        }
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
    for(int i=1;i<=n;i++){
        //cout<<co[i]<<" "<<dep[i]<<" "<<ord[i]<<" "<<si[co[i]]<<endl;
    }
    for(int i=1;i<=n;i++) jump[i][0]=tar[i];
    for(int k=1;k<20;k++) for(int i=1;i<=n;i++) jump[i][k]=jump[jump[i][k-1]][k-1];
    for(int i=1;i<=q;i++){
        int a,b;
        cin>>a>>b;
        int res=0;
        if(co[a]!=co[b]) cout<<-1<<endl;
        else if(dep[a]==0&&dep[b]==0) cout<<(ord[a]-ord[b]+si[co[a]])%si[co[a]]<<endl;
        else if(dep[b]==0){
            for(int k=19;k>=0;k--){
                if(dep[a]-(1<<k)>=0){
                    a=jump[a][k];
                    res+=(1<<k);
                }   
            }
            res+=(ord[a]-ord[b]+si[co[a]])%si[co[a]];
            cout<<res<<endl;
        }
        else{
            for(int k=19;k>=0;k--){
                if(dep[a]-(1<<k)>=dep[b]){
                    a=jump[a][k];
                    res+=(1<<k);
                }
            }
            if(a==b) cout<<res<<endl;
            else cout<<-1<<endl;
        }
        
    }
}