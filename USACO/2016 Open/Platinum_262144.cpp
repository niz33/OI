#include<iostream>
#include<cstdio>
using namespace std;
int n,a[300000],dp[300000][65];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],dp[i][a[i]]=i+1;
    for(int k=1;k<=60;k++) for(int i=1;i<=n;i++) if(k>a[i]) dp[i][k]=dp[dp[i][k-1]][k-1];
    for(int k=60;k>=1;k--) for(int i=1;i<=n;i++) if(dp[i][k]!=0){
        cout<<k<<endl;
        return 0;
    }
}