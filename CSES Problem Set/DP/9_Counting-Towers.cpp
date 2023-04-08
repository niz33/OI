#include<iostream>
using namespace std;
long long t,n,mod=1000000007,dp[1000005][2];
int main(){
    dp[1][0]=1;
    dp[1][1]=1;
    for(int i=2;i<=1000000;i++){
        dp[i][0]=(dp[i-1][0]*4+dp[i-1][1])%mod;
        dp[i][1]=(dp[i-1][0]+dp[i-1][1]*2)%mod;
    }
    cin>>t;
    while(t){
        cin>>n;
        cout<<(dp[n][0]+dp[n][1])%mod<<endl;
        t--;
    }
}