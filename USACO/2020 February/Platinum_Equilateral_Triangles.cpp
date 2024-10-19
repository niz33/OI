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
int n,g[305][305],down[1000][305],up[1000][305];
ll ans;
int get_down(int d,int i,int j){
    if(d>=n*2||d<1) return 0;
    i=max(i,max(n-d+1,1));
    j=min(j,min(n,2*n-d));
    return down[d][j]-down[d][i-1];
}
int get_up(int d,int i,int j){
    if(d>=n*2||d<1) return 0;
    if(i==j){
        if (i<max(d-n+1,1)||i>min(d,n)) return 0;
        return up[d][i]-up[d][i-1];
    }
    i=max(i,max(d-n+1,1));
    j=min(j,min(d,n));
    return up[d][j]-up[d][i-1];
}
int main() {
    freopen("triangles.in","r",stdin);
    freopen("triangles.out","w",stdout);
    cin>>n;
    char c;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
        cin>>c;
        down[j-i+n][i]=up[i+j-1][i]=g[i][j]=(c=='.')?0:1;
        down[j-i+n][i]+=down[j-i+n][i-1];
        up[i+j-1][i]+=up[i+j-1][i-1];
    }
    for(int d=1;d<=2*n-1;d++){
        for(int i=max(n-d+1,1);i<=min(n,2*n-d);i++)for(int j=i+1;j<=min(n,2*n-d);j++)if(g[i][d-n+i]&&g[j][d-n+j]){
            int di=j-i;
            ans+=get_down(d-2*di,j,j+di)+get_down(d+2*di,i-di,i);
        }
        for(int i=max(d-n+1,1);i<=min(d,n);i++)for(int j=i+1;j<=min(d,n);j++)if(g[i][d-i+1]&&g[j][d-j+1]){
            int di=j-i;
            ans+=get_up(d-2*di,i-di,i)+get_up(d+2*di,j,j+di);
            ans-=get_up(d-2*di,i-di,i-di)+get_up(d-2*di,i,i)+get_up(d+2*di,j,j)+get_up(d+2*di,j+di,j+di);
        }
    }
    cout<<ans<<endl;
    return 0;
}
