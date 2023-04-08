#include <iostream>
#include <vector>
using namespace std;
int n,m,v[100005];
vector<int> s[100005],ans;
void dfs(int x,int pre){
    for(int i:s[x]){
        if (i!=pre){
            if(v[i]){
                ans.push_back(x);
                while(ans.back()!=i){
                    ans.push_back(v[ans.back()]);
                }
                ans.push_back(x);
                cout<<ans.size()<<endl;
                for(int i:ans){
                    cout<<i<<" ";
                }
                exit(0);
            }
            v[i]=x;
            dfs(i,x);
        } 
        
    }
}
int main(){
    cin>>n>>m;
    int u,vv;
    for(int i=0;i<m;i++){
        cin>>u>>vv;
        s[u].push_back(vv);
        s[vv].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!v[i]){
            v[i]=i;
            dfs(i,0);
        }
    }
    cout<<"IMPOSSIBLE";
}