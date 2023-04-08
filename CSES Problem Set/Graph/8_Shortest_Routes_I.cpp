#include<iostream>
#include<queue>
#include<vector>
using namespace std;
priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> q;
vector<pair<long long,long long>> s[200005];
long long n,m,dis[200005],v[200005];
void dij(){
    for(int i=1;i<=n;i++){
        dis[i]=100000000000000000;
    }
    dis[1]=0;
    q.push({0,1});
    
    while(q.size()){
        long long x=q.top().second; 
        long long d=q.top().first;
        q.pop();
        if(d>dis[x]){
            continue;
        }
        for(pair<long long,long long> y:s[x]){
            if(d+y.second<dis[y.first]){
                q.push({d+y.second,y.first});
                dis[y.first]=d+y.second;
            }
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
    dij();
    for(int i=1;i<=n;i++){
        printf("%lld ",dis[i]);
    }
}