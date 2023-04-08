#include<iostream>
using namespace std;
long long n,v[5005],dp[5005][5005],p[5005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        p[i]=p[i-1]+v[i];
    }
    for(int l=1;l<=n;l++){
        for(int i=1;i+l-1<=n;i++){
            int j=i+l-1;
            dp[i][j]=p[j]-p[i-1]-min(dp[i+1][j],dp[i][j-1]);
            //cout<<dp[i][j]<<" ";
        }//cout<<endl;
    }
    cout<<dp[1][n];
}