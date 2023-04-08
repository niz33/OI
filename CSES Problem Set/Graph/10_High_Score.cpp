#include<iostream>
#include<queue>
#include<vector>
using namespace std;
vector<pair<long long,long long>> s[200005];
long long n,m,dis[200005],v[200005],qs=1,qt=1,q[100000000],ca[200005];
void ford(){
    ca[n]=1;
    for(int i=2;i<=n;i++){
        dis[i]=-100000000000000000;
    } 
    q[1]=1;
    int c=0,cn=0;
    while(qt>=qs){
        long long x=q[qs];
        v[x]=0;
        //cout<<x<<":"<<dis[x]<<endl;
        qs++;
        for(pair<long long,long long> y:s[x]){
            //cout<<y.first<<" ";
            
            if(ca[y.first]==1){
                ca[x]=1;
            }
            if(ca[x]){
                c=0;
                cn++;
            }
            if(dis[x]+y.second>dis[y.first]){
                dis[y.first]=dis[x]+y.second;
                if(!v[y.first]){
                    qt++;
                    q[qt]=y.first;
                    v[y.first]=1;
                    
                }
            }
        }
        c++;
        //cout<<x<<":"<<c<<" "<<cn<<endl; 
        if(cn>n*n+n){
            cout<<-1;
            exit(0);
        }
        if(c>n*n+n){
            return;
        }
    }

}
int main(){
    cin>>n>>m;
    long long u,v,w;
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        s[u].push_back({v,w});
    }
    ford();
    //for(int i=1;i<=n;i++){
    //    printf("%lld ",dis[i]);
    //}
    cout<<dis[n];
}