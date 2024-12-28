#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define ll long long
#define pb push_back
const ll MOD = 1e9 + 7;
ll inverse(ll x) { return x <= 1ll ? x : MOD - MOD / x * inverse(MOD % x) % MOD; }
ll n,k,a[2000000],cnt[2000000],ans[2000000];
ll eval(ll a,ll b) {
    ll n=0,d=0;
    for (int i=1;i<=20;i++) {
        n+=(a&b&1);
        d+=((a|b)&1);
        a>>=1;
        b>>=1;
    }
    return (n*inverse(d))%MOD;
}
int main() {
    cin>>n>>k;
    for (int i=1;i<=n;i++) {
        cin>>a[i];
        cnt[a[i]]++;
    }
    for (int i=0;i<(1<<k);i++) {
        for (int j=0;j<(1<<k);j++) {
            ans[i]+=eval(i,j)*cnt[j];
            ans[i]%=MOD;
        }
    }
    for (int i=1;i<=n;i++) {
        cout<<ans[a[i]]<<endl;
    }
}
