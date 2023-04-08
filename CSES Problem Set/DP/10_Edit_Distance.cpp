#include<iostream>
using namespace std;
char a[5005],b[5005];
int dp[5005][5005];
int main(){
    string sa,sb;
    cin>>sa>>sb;
    for(int i=1;i<=5000;i++){
        dp[i][0]=i;
        dp[0][i]=i;
    }
    for(int i=0;i<sa.length();i++){
        a[i+1]=sa[i];
    }
    for(int i=0;i<sb.length();i++){
        b[i+1]=sb[i];
    }
    for(int i=1;i<=sa.length();i++){
        for(int j=1;j<=sb.length();j++){
            dp[i][j]=min(dp[i-1][j-1]+(a[i]!=b[j]),min(dp[i-1][j],dp[i][j-1])+1);
            //cout<<dp[i][j]<<" ";
        }//cout<<endl;
    }
    cout<<dp[sa.length()][sb.length()];
}