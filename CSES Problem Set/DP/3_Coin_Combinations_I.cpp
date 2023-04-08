#include<iostream>
#include<algorithm>
using namespace std;
long long dp[1000005],n,x,c[105],mod=1000000007;
int main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    sort(c+1,c+n+1);
    dp[0]=1;
    for(int i=1;i<=x;i++){
        int j=1;
        while(i-c[j]>=0&&j<=n){
            dp[i]+=dp[i-c[j]];
            j++;
        }
        dp[i]%=mod;
    }
    cout<<dp[x];
}