#include<iostream>
#include<algorithm>
using namespace std;
int n,x,c[105],mod = 1000000007,dp[105][1000005];
int main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=min(x,c[i]-1);j++){
            dp[i][j]=dp[i-1][j];
            //cout<<dp[i][j]<<" ";
        }
        for(int j=c[i];j<=x;j++){
            dp[i][j]=dp[i-1][j]+dp[i][j-c[i]];
            dp[i][j]%=mod;
            //cout<<dp[i][j]<<" ";
        }
        //cout<<endl;
    }
    cout<<dp[n][x];
}  