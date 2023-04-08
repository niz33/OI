#include<iostream>
using namespace std;
int n,v[105],dp[105][100005];
int main(){
    int sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    dp[0][0]=1;
    int ans;
    for(int i=1;i<=n;i++){
        sum+=v[i];
        ans=-1;
        for(int j=0;j<v[i];j++){
            dp[i][j]=dp[i-1][j];
            ans+=dp[i][j];
        }
        for(int j=v[i];j<=sum;j++){
            dp[i][j]=(dp[i-1][j]||dp[i-1][j-v[i]]);
            ans+=dp[i][j];
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=sum;i++){
        if(dp[n][i]){
            cout<<i<<" ";
        }
    }
}