#include<iostream>
#include<vector>
using namespace std;
vector<int> ans,s[200005];
int n,m,v[200005];
int search(int x){
    v[x]=1;
     for(int y:s[x]){
        if(v[y]==1){
            ans.push_back(x);
            return y;
        }
        else if(v[y]==0){
            int temp;
            if((temp=search(y))!=0){
                if(temp==-1){
                    return -1;
                }
                ans.push_back(x);
                if(temp==x){
                    return -1;
                }
                return temp;
            }
        }
    }
    v[x]=2;
    return 0;
}
int main(){
    int u,vv;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>vv;
        s[vv].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(v[i]==0){
            if(search(i)!=0){
                cout<<ans.size()+1<<endl;
                for(int i:ans){
                    cout<<i<<" ";
                }
                cout<<ans[0];
                return 0;
            }
        }
    }
    cout<<"IMPOSSIBLE";
    return 0;
}