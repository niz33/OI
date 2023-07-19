#include<iostream>
#include<vector>
using namespace std;
long long n,m,ans;
class Dinic{
public:
    bool exist[505][505];
    long long cap[505][505];
    long long flow[505][505];
    struct vertex{
        vector<int>edges;
        long long cur,level;
    }ver[505];
    
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
        long long queue[505],l=1,r=1;
        queue[1]=1;
        ver[1].level=1;
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
        return ver[n].level;
    }

    long long dfs(int u,long long curFlow){
        //cout<<u<<endl;
        if((curFlow==0)||(u==n)){
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
            ans+=dfs(1,100000000000000);
            for(int i=1;i<=n;i++){
                ver[i].cur=0;
                ver[i].level=0;
            }
        }
    }
}d;
int main(){

    cin>>n>>m;
    long long u,v,c;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>c;
        d.add_edge(u,v,c); 
    }
    d.run();
    cout<<ans;
}