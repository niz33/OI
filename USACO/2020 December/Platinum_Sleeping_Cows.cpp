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
int n,dp[3005][3005],a[3005],b[3005],f[3005];

int main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    sort(a+1,a+n+1,greater<int>());
    sort(b+1,b+n+1,greater<int>());
    int l=n+1;
    for(int i=1;i<=n;i++) {
        while(b[l+1]>=a[i]&&l+1<=n) l++;
        f[i]=l;
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=f[i];j++) {
            dp[i][j]=max(dp[i-1][j-1]+a[i]*b[j],dp[i][j-1]);
        }
    }
    return 0;
}