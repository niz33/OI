#include<iostream>
#include<vector>
using namespace std;
long long n,m,k,ans;
class Dinic{
public:
    bool exist[1005][1005];
    long long cap[1005][1005];
    long long flow[1005][1005];
    struct vertex{
        vector<int>edges;
        long long cur,level;
    }ver[1005];
    
    void add_edge(long long u,long long v,long long c){
        if(!exist[u][v]){
            ver[u].edges.push_back(v);
            ver[v].edges.push_back(u);
            exist[u][v]=1;
            exist[v][u]=1;
        }
        cap[u][v]+=c;
    }

    int bfs(){
        long long queue[1005],l=1,r=1;
        queue[1]=n+m+1;
        ver[n+m+1].level=1;
        while(l<=r){
            long long u=queue[l];
            for(int v:ver[u].edges){
                if((!ver[v].level)&&(cap[u][v]-flow[u][v]>0)){
                    r++;
                    queue[r]=v;
                    ver[v].level=ver[u].level+1;
                }
            }
            l++;
        }
        return ver[n+m+2].level;
    }

    long long dfs(int u,long long curFlow){
        //cout<<u<<endl;
        if((curFlow==0)||(u==n+m+2)){
            return curFlow;
        }
        long long res=0;
        for(;ver[u].cur<ver[u].edges.size();ver[u].cur++){
            int v=ver[u].edges[ver[u].cur];
            //cout<<ver[u].cur<<endl;
            if((ver[v].level!=ver[u].level+1)){
                continue;
            }
            //cout<<"good"<<endl;
            long long tryy=dfs(v,min(curFlow-res,cap[u][v]-flow[u][v]));
            res+=tryy;
            flow[u][v]+=tryy;
            flow[v][u]-=tryy;
            if(res==curFlow){
                return res;
            }
        }
        return res;
    }

    void run(){
        while(bfs()>0){
            ans+=dfs(n+m+1,100000000000000);
            for(int i=1;i<=n+m+2;i++){
                ver[i].cur=0;
                ver[i].level=0;
            }
        }
    }
}d;
int main(){

    cin>>n>>m>>k;
    long long u,v,c;
    for(int i=1;i<=n;i++){
        d.add_edge(n+m+1,i,1);
    }
    for(int i=n+1;i<=n+m;i++){
        d.add_edge(i,n+m+2,1);
    }
    for(int i=1;i<=k;i++){
        cin>>u>>v;
        d.add_edge(u,v+n,1);
    }
    d.run();
    
    
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        for(int j=n+1;j<=n+m;j++){
            if(d.flow[i][j]==1){
                cout<<i<<" "<<j-n<<endl;
            }
        }
    }
}