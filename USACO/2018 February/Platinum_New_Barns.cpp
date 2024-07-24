#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
int q,co[100005],bl[100005][20],dep[100005],dp[100005],cot=0,vert=0,dial[100005];
pair<int,int> dia[100005];
int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[x]-(1<<i)>=dep[y]) x=bl[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(bl[x][i]!=bl[y][i]) x=bl[x][i],y=bl[y][i];
    return bl[x][0];
}
int dist(int x, int y){
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int main() {
    freopen("newbarn.in","r",stdin);
    freopen("newbarn.out","w",stdout);
    cin>>q;
    char c;
    int x;
    for(int i=0;i<q;i++){
        cin>>c>>x;
        if(c=='B'){
            if(x==-1){
                co[++vert]=++cot;
                bl[vert][0]=0;
                dep[vert]=1;
                dia[cot]={vert,vert};
                dial[cot]=0;
            }
            else{
                co[++vert]=co[x];
                bl[vert][0]=x;
                dep[vert]=dep[x]+1;
                for(int j=1;j<20;j++) bl[vert][j]=bl[bl[vert][j-1]][j-1];
                int l1=dist(vert,dia[co[vert]].first),l2=dist(vert,dia[co[vert]].second);
                if(l1>dial[co[vert]]||l2>dial[co[vert]]){
                    if(l1>l2) dia[co[vert]].second=vert;
                    else dia[co[vert]].first=vert;
                    dial[co[vert]]=max(l1,l2);
                }
            }
            //cout<<vert<<" "<<co[vert]<<" "<<dia[co[vert]].first<<" "<<dia[co[vert]].second<<" "<<dial[co[vert]]<<endl;
        }
        else{
            //cout<<lca(x,dia[co[x]].first)<<" "<<lca(x,dia[co[x]].second)<<endl;
            cout<<max(dist(x,dia[co[x]].first),dist(x,dia[co[x]].second))<<endl;
        }
    }

    return 0;
}