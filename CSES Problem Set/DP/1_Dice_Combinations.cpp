#include<iostream>
using namespace std;
long long n,dp[1000005];
const long long mod=1000000007;
int main(){
    int n;
    cin>>n;
    dp[0]=1;
    int sum=1;
    for(int i=1;i<=n;i++){
        dp[i]=sum%mod;
        sum+=dp[i];
        sum%=mod;
        if(i>=6){
            sum+=mod-dp[i-6];
            sum%=mod;
        }
    }
    cout<<dp[n];
}