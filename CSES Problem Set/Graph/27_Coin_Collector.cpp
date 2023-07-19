#include<iostream>
#include<vector>
using namespace std;
long long n,m,v[200005],vis[200005],low[200005],scc[200005],sum[200005],viscnt,inst[200005],st[200005],stt,scccnt,top[200005],to[200005],q[200005],ql=1,qr=0,dp[200005];
vector<int> s[200005],sh[200005];
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
            sum[scccnt]+=v[st[stt]];
            stt--;
        }
        scc[x]=scccnt;
        inst[x]=0;
        sum[scccnt]+=v[x];
        stt--;
    }
}
void topo(){
    for(int i=1;i<=scccnt;i++){
        if(!to[i]){
            qr++;
            q[qr]=i;
        }
    }
    while(qr>=ql){
        int x=q[ql];
        ql++;
        dp[x]+=sum[x];
        for(int y: sh[x]){
            to[y]--;
            dp[y]=max(dp[y],dp[x]);
            if(!to[y]){
                qr++;
                q[qr]=y;
            }
        }
    }

}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    int a,b;
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        s[a].push_back(b);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j: s[i]){
            if(scc[i]!=scc[j]){
                sh[scc[i]].push_back(scc[j]);
                to[scc[j]]++;
            }
        }
    }
    topo();
    long long ma=0;
    for(int i=1;i<=n;i++){
        ma=max(ma,dp[i]);
    }
    cout<<ma;
}
