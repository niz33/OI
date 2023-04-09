#include<iostream>
#include<vector>
using namespace std;
vector<int> s[100005],b[100005];
int n,m,cnt=0,v1s[100005],v2s[100005];
void dfs1(int x){
    cnt++;
    v1s[x]=1;
    for(int y:s[x]){
        if(!v1s[y]){
            dfs1(y);
        }
    }
}
void dfs2(int x){
    cnt++;
    v2s[x]=1;
    for(int y:b[x]){
        if(!v2s[y]){
            dfs2(y);
        }
    }
}
int main(){
 cin>>n>>m;
 for(int i=1;i<=m;i++){
    int u,v;
    cin>>u>>v;
    b[v].push_back(u);
    s[u].push_back(v);
 }
dfs1(1);
dfs2(1);
for(int i=1;i<=n;i++){
    if(!v1s[i]){
        cout<<"NO"<<endl;
        cout<<1<<" "<<i;
        return 0;
    }
    if(!v2s[i]){
        cout<<"NO"<<endl;
        cout<<i<<" "<<1;
        return 0;
    }
}
cout<<"YES";
}