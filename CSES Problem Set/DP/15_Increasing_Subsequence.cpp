#include<iostream>
#include<algorithm>
using namespace std;
int n,a[200005],dp[200005],ans=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        dp[i]=2000000000;
        cin>>a[i];
    }
    dp[0]=0;
    for(int i=1;i<=n;i++){
        int l=lower_bound(dp,dp+n+1,a[i])-dp;
        if(dp[l]==2000000000){
            dp[l]=a[i];
            ans=l;
        }
        else{
            dp[l]=a[i];
        }
        //for(int j=0;j<=n;j++){
        //    cout<<dp[j]<<" ";
        //}cout<<endl;
    }
    cout<<ans;
}