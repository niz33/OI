#include<iostream>
#include<vector>
using namespace std;
int n,m,vis[200005],low[200005],scc[200005],viscnt,inst[200005],st[200005],stt,scccnt,top[200005],ord[20005],to[200005],q[200005],ql=1,qr=0,ordcnt;
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
            stt--;
        }
        scc[x]=scccnt;
        inst[x]=0;
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
        ordcnt++;
        int x=q[ql];
        ql++;
        ord[x]=ordcnt;
        for(int y: sh[x]){
            to[y]--;
            if(!to[y]){
                qr++;
                q[qr]=y;
            }
        }
    }

}
int main(){
    cin>>n>>m;
    int a,b;
    char ac,bc;
    for(int i=1;i<=n;i++){
        cin>>ac>>a>>bc>>b;
        ac=(ac=='+');
        bc=(bc=='+');
        a--;
        b--;
        s[(!ac)*m+a].push_back(bc*m+b);
        s[(!bc)*m+b].push_back(ac*m+a);
    }
    for(int i=0;i<m*2;i++){
        if(!vis[i]){
            tarjan(i);
        }
        //cout<<i<<" "<<vis[i]<<" "<<low[i]<<endl;
        //cout<<i<<":"<<scc[i]<<endl;
    }
    for(int i=0;i<m*2;i++){
        for(int j: s[i]){
            if(scc[i]!=scc[j]){
                sh[scc[i]].push_back(scc[j]);
                to[scc[j]]++;
            }
        }
    }
    topo();
    for(int i=0;i<m;i++){
        if(scc[i]==scc[i+m]){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    for(int i=0;i<m;i++){
        if(ord[scc[i+m]]>ord[scc[i]]){
            cout<<"+ ";
        }
        else{
            cout<<"- ";
        }
    }
}