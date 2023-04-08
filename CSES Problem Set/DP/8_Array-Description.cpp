#include<iostream>
#include<algorithm>
using namespace std;
long long n,m,c[100005],dp[100005][105],mod=1000000007;
int main(){
    cin>>n>>m;
    for(int i=0;i<=m+1;i++){
        dp[0][i]=333333336;
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        if(c[i]){
            dp[i][c[i]]=dp[i-1][c[i]-1]+dp[i-1][c[i]]+dp[i-1][c[i]+1];
            dp[i][c[i]]%=1000000007;
        }
        else{
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j-1]+dp[i-1][j]+dp[i-1][j+1];
                dp[i][j]%=1000000007;
            }
        }
    }
    long long ans=0;
    for(int i=1;i<=m;i++){
        ans+=dp[n][i];
    }
    cout<<ans%mod;
}