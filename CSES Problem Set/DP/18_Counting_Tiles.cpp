#include<iostream>
#include<algorithm>
using namespace std;
int dp[2000][2],mod=1000000007,n,m;
int main() {
	cin>>n>>m;
	dp[0][0]=1;
	for (int j=0;j<m;j++){
        for (int i=0;i<n;i++) {
		    for (int mask=0;mask<(1<<n);mask++) {
			    dp[mask][1]=dp[mask^(1<<i)][0];
			    if (i&&!(mask&(1<<i))&&!(mask&(1<<i-1))){
                    dp[mask][1]+=dp[mask^(1<<i-1)][0];
                }
			    if (dp[mask][1]>=mod){
                    dp[mask][1]-=mod;
		        }
            }
		    for (int mask=0;mask<(1<<n);mask++){
                dp[mask][0]=dp[mask][1];
            } 
	    }
    } 
	cout<<dp[0][0];
	return 0;
}