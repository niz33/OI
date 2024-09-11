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
int n,m,g[1005][1005],f[1000000],nt=0,c[1005][1005],uf[1000000],vis[1000000];
ll dp[1000000],ans=1;
vector<int> chil[1000000],le[1005];
int findd(int x){
    return uf[x]==x?x:uf[x]=findd(uf[x]);
}
void merge(int x,int y){
    uf[findd(x)]=findd(y);
}
ll dfs(int x){
    //cout<<x<<endl;
    ll t=1;
    for(int y:chil[x]){
        if(y==x) continue;
        t*=dfs(y);
        t%=1000000007;
    }
    return (t+1);
}
int main() {
    freopen("cave.in","r",stdin);
    freopen("cave.out","w",stdout);
    cin>>n>>m;
    char cc;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>cc;
            g[i][j]=cc=='#'?1:0;
        }
    }
    for(int i=n;i>=2;i--){
        //cout<<i<<endl;
        int l=1,r;
        while(1){
            while(g[i][l]&&l<=m)l++;
            if(l>m) break;
            c[i][l]=++nt;
            uf[nt]=nt;
            r=l;
            while((!g[i][r])&&r<=m){
                c[i][r]=nt;
                if(!g[i+1][r]){
                    merge(c[i+1][r],c[i][r]);
                }
                r++;
            }
            l=r;
        }
        for(int j=1;j<=m;j++){
            //cout<<uf[c[i][j]]<<' ';
            if(!vis[findd(c[i][j])]){
                vis[findd(c[i][j])]=1;
                le[i].pb(findd(c[i][j]));
            }
        }//cout<<endl;
        if(i<n)for(int j:le[i+1]){
            f[j]=findd(j);
            chil[f[j]].pb(j);
        }
    }
    for(int i=1;i<=nt;i++){
        // cout<<i<<endl;
        // for(int j:chil[i]){
        //  cout<<j<<' ';
        // }cout<<endl;
        if(uf[i]==i){
            ans*=dfs(i);
            ans%=1000000007;
        }
    }
    cout<<ans<<endl;
    return 0;

}


