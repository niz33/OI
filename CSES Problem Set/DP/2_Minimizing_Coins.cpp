#include<iostream>
using namespace std;
int dp[1000005],n,x,c[105];
int main(){
    cin>>x>>n;
    for(int i=1;i<=x;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        dp[i]=100000000;
        for(int j=1;j<=x;j++){
            if(i-c[j]>=0){
                dp[i]=min(dp[i],dp[i-c[j]]+1);
            }
        }
    }
    if(dp[n]==100000000){
        cout<<-1;
        return 0;
    }
    cout<<dp[n];
}