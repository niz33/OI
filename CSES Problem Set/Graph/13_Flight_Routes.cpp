#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> q;
vector<pair<long long,long long>> s[200005];
long long n,m,v[200005],k;
priority_queue<long long,vector<long long>,greater<long long>> ans;
void dijk(){
    q.push({0,1});
    while(q.size()){
        long long x=q.top().second; 
        //cout<<x<<" "<<s[x].size()<<endl;
        long long d=q.top().first;
        q.pop();
        if(v[x]>=k){
            continue;
        }
        v[x]++;
        if(x==n){
            ans.push(d);
        }
        //cout<<"asdg"<<endl;
        for(pair<long long,long long> y:s[x]){
            //cout<<y.first<<" ";
            //if(d+y.second<dis[y.first]){
            
            q.push({d+y.second,y.first});
            
            //}
        }//cout<<endl;
    }
}
int main(){
    cin>>n>>m>>k;
    long long u,v,w;
    
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        s[u].push_back({v,w});
    }
    dijk();
    while(ans.size()){
        cout<<ans.top()<<" ";
        ans.pop();
    }
}