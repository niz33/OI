#include<iostream>
#include<vector>
using namespace std;
int n,m,q[200005],qs=1,qt=0,v[200005],dp[200005],p[200005];
vector<int> s[200005];
int main(){
    cin>>n>>m;
    int a,b;
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        s[b].push_back(a);
        v[a]++;
    }
    for(int i=1;i<=n;i++){
        dp[i]=-100000000;
        if(i==n){
            dp[i]=1;
        }
        if(!v[i]){
            qt++;
            q[qt]=i;
        }
    }
    while(qs<=qt){
        int x=q[qs];
        qs++;
        for(int y:s[x]){
            if(dp[x]+1>dp[y]){
                dp[y]=dp[x]+1;
                p[y]=x;
            }
            v[y]--;
            if(!v[y]){
                qt++;
                q[qt]=y;
            }
        }
    }
    if(dp[1]<0){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    cout<<dp[1]<<endl;
    int x=1;
    while(x!=n){
        cout<<x<<" ";
        x=p[x];
    }
    cout<<n;
}