#include<iostream>
using namespace std;
char b[1005][1005];
long long dp[1005][1005],mod=1000000007;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>b[i][j];
        }
    }
    if(b[1][1]=='.'){
        dp[1][1]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(b[i][j]=='.'){
                dp[i][j]+=dp[i-1][j]+dp[i][j-1];
                dp[i][j]%=mod;
            }
        }
    }
    cout<<dp[n][n];
}