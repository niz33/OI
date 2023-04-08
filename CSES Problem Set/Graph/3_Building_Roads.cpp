#include<iostream>
#include<vector>
using namespace std;
int n,m,v[100005];
vector<int> s[100005],l;
void floodfill(int x){
    v[x]=1;
    for(int y:s[x]){
        if(!v[y]){
            floodfill(y);
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
    floodfill(1);
    for(int i=2;i<=n;i++){
        if(!v[i]){
            l.push_back(i);
            floodfill(i);
        }
    }
    cout<<l.size()<<endl;
    for(int i:l){
        cout<<1<<" "<<i<<endl;
    }
}