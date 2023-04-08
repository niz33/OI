#include<iostream>
#include<algorithm>
using namespace std;
int n,x,c[1005],p[1005],dp[1005][100005];
int main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<c[i];j++){
            dp[i][j]=dp[i-1][j];
        }
        for(int j=c[i];j<=x;j++){
            dp[i][j]=max(dp[i-1][j],dp[i-1][j-c[i]]+p[i]);
        }
    }
    cout<<dp[n][x];
}