#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
ll n,m[100005],ans;
pair<ll,ll> a[100005];
int main() {
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].second,a[i].first=i;
    sort(a+1,a+n+1,[](pair<ll,ll> a,pair<ll,ll> b){return a.second==b.second?a.first<b.first:a.second<b.second;});
    ll r=0;
    for(int i=1;i<=n;i++){
        r=max(r,a[i].first);
        m[i]=r-i;
    }
    m[0]=0;
    m[n]=0;
    for(int i=1;i<=n;i++) ans+=max(1ll,max(m[i],m[i-1]));
    cout<<ans;
    return 0;
}