#include<iostream>
using namespace std;
int a,b,dp[505][505];
int main(){
    cin>>a>>b;
    if(b>a){
        a+=b;
        b=a-b;
        a=a-b;
    }
    for(int i=1;i<=a;i++){
        dp[i][i]=0;
    }
    for(int i=1;i<=a;i++){
        for(int j=1;j<i;j++){
            dp[max(i,j)][min(i,j)]=1000000;
            for(int k=1;k<i;k++){
                dp[max(i,j)][min(i,j)]=min(dp[max(i,j)][min(i,j)],dp[max(k,j)][min(k,j)]+dp[max(i-k,j)][min(i-k,j)]+1);
            }
            for(int k=1;k<j;k++){
                dp[max(i,j)][min(i,j)]=min(dp[max(i,j)][min(i,j)],dp[max(i,k)][min(i,k)]+dp[max(i,j-k)][min(i,j-k)]+1);
            }
        }
    }
    cout<<dp[a][b];
}