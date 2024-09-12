#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
template<typename T1,typename T2> struct cpair{T1 x;T2 y;};
template<typename T1,typename T2> struct rpair{T1 l;T2 r;};
template<typename T1,typename T2> struct epair{T1 u;T2 v;};
int n,m,l[50000],r[50000],w[50000],mm[302][302][302],dp[302][302];

signed main() {
    freopen("pieaters.in","r",stdin);
    freopen("pieaters.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>w[i]>>l[i]>>r[i];
        for(int k=l[i];k<=r[i];k++){
            mm[l[i]][r[i]][k]=max(mm[l[i]][r[i]][k],w[i]);
        }
    }
    for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=i;k<=j;k++){
                mm[i][j][k]=max(mm[i][j][k],max(mm[i][j-1][k],mm[i+1][j][k]));
            }
        }
    }
    for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=i;k<=j;k++){
                dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j]+mm[i][j][k]);
            }
        }
    }
    cout<<dp[1][n];
    return 0;
}