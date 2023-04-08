#include<iostream>
#include<vector>
using namespace std;
int n,m,v[100005],p=1;
vector<int> s[100005];
void floodfill(int x){
    for(int y:s[x]){
        if(!v[y]){
            v[y]=3-v[x];
            floodfill(y);
        }
        else if(v[y]!=3-v[x]){
            p=0;
        }
    }
}
int main(){
    cin>>n>>m;
    int u,vv;
    for(int i=1;i<=m;i++){
        cin>>u>>vv;
        s[u].push_back(vv);
        s[vv].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!v[i]){
            v[i]=1;
            floodfill(i);
        }
    }
    if(!p){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        cout<<v[i]<<" ";
    }
}