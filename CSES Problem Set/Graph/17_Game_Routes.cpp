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
        s[a].push_back(b);
        v[b]++;
    }
    dp[1]=1;
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
            dp[y]+=dp[x];
            dp[y]%=1000000007;
            v[y]--;
            if(!v[y]){
                qt++;
                q[qt]=y;
            }
        }
    }
    cout<<dp[n];
}