#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#pragma GCC optimize("O2")
using namespace std;
#define ll long long
#define pb push_back
template<typename T1,typename T2> struct cpair{T1 x;T2 y;};
template<typename T1,typename T2> struct rpair{T1 l;T2 r;};
template<typename T1,typename T2> struct epair{T1 u;T2 v;};
ll n,g[2005][2005],dp[2][2005][2005],mod=1e9+7,ex[4000005],ans[2][2005][2005];
int main(){
    freopen("sprinklers2.in","r",stdin);
    freopen("sprinklers2.out","w",stdout);
    int num=0;
    char temp;
    cin>>n;
    ex[0]=1;
    for(int i=1;i<=n*n;i++)ex[i]=(ex[i-1]<<1)%mod;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>temp;
            g[i][j]=temp=='W'?1ll:0ll;
            if(!g[i][j])num++;
        }
    }
    for(int i=n;i>=1;i--)for(int j=n;j>=1;j--){
        if(!g[i-1][j]){
        dp[0][i][j]=dp[1][i][j+1]*(500000004)%mod;
        if(!g[i][n])dp[0][i][j]+=ex[num-1];
        if(dp[0][i][j]>=mod)dp[0][i][j]-=mod;
        }
        if(!g[i][j-1]){
        dp[1][i][j]=dp[0][i+1][j]*(500000004)%mod;
        if(!g[n][j])dp[1][i][j]+=ex[num-1];
        if(dp[1][i][j]>=mod)dp[1][i][j]-=mod;
        }
        ans[0][i][j]=dp[0][i][j];
        ans[1][i][j]=dp[1][i][j];
        dp[0][i][j]+=dp[0][i+1][j];
        dp[1][i][j]+=dp[1][i][j+1];
        if(dp[0][i][j]>=mod)dp[0][i][j]-=mod;
        if(dp[1][i][j]>=mod)dp[1][i][j]-=mod;
        
    }
    cout<<(ans[0][1][1]+ans[1][1][1])%mod<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<ans[0][i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<ans[1][i][j]<<" "; 
    //     }
    //     cout<<endl;
    // }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<dp[0][i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<dp[1][i][j]<<" "; 
    //     }
    //     cout<<endl;
    // }

    return 0;
}