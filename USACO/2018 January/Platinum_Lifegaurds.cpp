#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
template<typename T1, typename T2>
struct cpair {T1 r;T2 l;};
int n,k,dp[100005][105],pre[100005],cu[100005];
cpair<int,int> ra[100005];
vector<cpair<int,int>> sra;
int main() { 
    freopen("lifeguards.in","r",stdin);
    freopen("lifeguards.out","w",stdout);   
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>ra[i].l>>ra[i].r;
    sort(ra+1,ra+n+1,[](cpair<int,int> a,cpair<int,int> b){return a.l<b.l;});
    int mr=0;
    // cout<<"-------------"<<endl;
    // for(int i=1;i<=n;i++) cout<<ra[i].l<<" "<<ra[i].r<<endl;
    // cout<<"-------------"<<endl;
    sra.pb({0,0});
    for(int i=1;i<=n;i++){
        if(ra[i].r<=mr){
            k--;
            continue;
        }
        mr=ra[i].r;
        sra.pb(ra[i]);
    }
    k+=0;
    pre[0]=0;
    for(int i=1;i<sra.size();i++){
        pre[i]=pre[i-1];
        while(pre[i]<i&&sra[pre[i]].r<sra[i].l)pre[i]++;
        pre[i]--;
        //cout<<pre[i]<<" ";
    }
    // cout<<"-------------"<<endl;
    // for(auto i:sra) cout<<i.l<<" "<<i.r<<endl;
    // cout<<"-------------"<<endl;
    int cuc=0;
    for(int i=1;i<sra.size();i++){
        while(cuc<pre[i]){
            cuc++;
            for(int j=min(cuc,k);j>=1;j--){
                cu[j]=max(dp[cuc][j],cu[j-1]);
            }
            cu[0]=dp[cuc][0];
        }
        // cout<<i<<" "<<pre[i]<<endl;
        // for(int j=0;j<=min(i-1,k);j++) cout<<cu[j]<<" ";
        // cout<<endl;
        for(int j=0;j<=min(i-1,k);j++){
            dp[i][j]=sra[i].r-sra[i].l;
            if(pre[i]==i-1) dp[i][j]+=cu[j];
            else dp[i][j]+=max(dp[pre[i]+1][max(0,j-i+pre[i]+2)]+sra[i].l-sra[pre[i]+1].r,cu[max(0,j-i+pre[i]+1)]);
           //cout<<dp[i][j]<<" ";
        }//cout<<endl;
    }
    int ans=0;
    for(int i=0;i<sra.size();i++) ans=max(ans,dp[i][max(0,k-(int)sra.size()+i+1)]);
    cout<<ans;
    return 0;
}