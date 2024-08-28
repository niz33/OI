#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
ll n;

int main() {
    freopen("gymnasts.in","r",stdin);
    freopen("gymnasts.out","w",stdout);
    cin>>n;
    ll ans=0;
    for(ll d=2;d*d<=n;d++){
        if(n%d)continue;
        ans+=d;
        if(d*d<n)ans+=n/d;
        ans%=1000000007;
    }
    cout<<(ans+n)%1000000007;
    return 0;
}