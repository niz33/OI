#include<iostream>
using namespace std;
int dp[1000005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int d=i;
        dp[i]=10000000;
        while(d){
            dp[i]=min(dp[i],dp[i-d%10]+1);
            d/=10;
        }
    }
    cout<<dp[n];
}