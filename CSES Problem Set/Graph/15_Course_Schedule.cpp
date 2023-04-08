#include<iostream>
#include<vector>
using namespace std;
int n,m,q[200005],qs=1,qt=0,v[200005];
vector<int> s[200005];
int main(){
    cin>>n>>m;
    int a,b;
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        s[a].push_back(b);
        v[b]++;
    }
    for(int i=1;i<=n;i++){
        if(!v[i]){
            qt++;
            q[qt]=i;
        }
    }
    while(qs<=qt){
        int x=q[qs];
        qs++;
        for(int y:s[x]){
            v[y]--;
            if(!v[y]){
                qt++;
                q[qt]=y;
            }
        }
    }
    if(qt!=n){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    for(int i=1;i<=qt;i++){
        cout<<q[i]<<" ";
    }
}