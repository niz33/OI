#include<iostream>
#include<set>
#include<vector>
#include<cstdio>
using namespace std;
#define int long long
vector<int> adj[100005];
set<int> s[100005];
set<int> cs[100005];
int st[100005],en[100005],in[200005],top=0;
int n,q;
int t[400000],lazy[400000];
void euler(int x,int f){
    st[x]=++top;
    in[top]=x;
    for(int i=0;i<adj[x].size();i++)if(adj[x][i]!=f)euler(adj[x][i],x);
    en[x]=top;
}
void unlazy(int x,int l,int r){
    if(l!=r){
        int m=(l+r)/2;
        t[x*2]+=lazy[x]*(m-l+1);
        t[x*2+1]+=lazy[x]*(r-m);
        lazy[x*2]+=lazy[x];
        lazy[x*2+1]+=lazy[x];
        lazy[x]=0;
    }
}
void update(int l,int r,int x,int xl,int xr,int v){
    if(l<=xl&&xr<=r){
        t[x]+=v*(xr-xl+1);
        lazy[x]+=v;
        return;
    }
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    if(l<=m)update(l,r,x*2,xl,m,v);
    if(r>m)update(l,r,x*2+1,m+1,xr,v);
    t[x]=t[x*2]+t[x*2+1];
}
int query(int l,int r,int x,int xl,int xr){
    if(l<=xl&&xr<=r)return t[x];
    unlazy(x,xl,xr);
    int m=(xl+xr)/2;
    int res=0;
    if(l<=m)res+=query(l,r,x*2,xl,m);
    if(r>m)res+=query(l,r,x*2+1,m+1,xr);
    return res;
}
signed main(){
    freopen("snowcow.in","r",stdin);
    freopen("snowcow.out","w",stdout);
    cin>>n>>q;
    int u,v,c;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    euler(1,0);
    int ty;
    for(int i=1;i<=q;i++){
        cin>>ty;
        
        if(ty==2){
            cin>>u;
            cout<<query(st[u],en[u],1,1,n)<<endl;
        }
        else{
            cin>>u>>c;
            int tu=u,b=1;
            auto x=s[c].lower_bound(st[u]);
            if(x!=s[c].begin()){
                x--;
                if(en[in[*x]]>=en[u])b=0;
            }
            //cout<<endl;
            if(b){
                cs[u].insert(c);
                x=s[c].lower_bound(st[u]);
                vector<int> rem;
                while(x!=s[c].end()){
                    if(*x>en[u])break;
                    //cout<<"removed "<<*x<<" "<<in[*x]<<endl;
                    update(*x,en[in[*x]],1,1,n,-1);
                    rem.push_back(*x);
                    x++;
                }
                for(int j=0;j<rem.size();j++)s[c].erase(rem[j]);
                s[c].insert(st[u]);
                //cout<<"added "<<u<<endl;
                update(st[u],en[u],1,1,n,1);
            }
        }
    }
}