#include<iostream>
using namespace std;
long long n,dp[505][200000],mod=1000000007;
int main(){
    dp[0][0]=1;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i*(i+1)/2;j++){
            dp[i][j]=dp[i-1][j]+dp[i-1][max(j-i,0)];
            dp[i][j]%=mod;
        }
    }
    if(n*(n+1)/2%2==0){
        cout<<dp[n][n*(n+1)/4];
    }
    else{
        cout<<0;
    }
}