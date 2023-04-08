#include<iostream>
#include<queue>
#include<vector>
using namespace std;
vector<pair<long long,long long>> s[200005];
long long n,m,dis[200005],v[200005],qs=1,qt=1,q[100000000],p[200005],st;
void ford(){
    for(int i=2;i<=n;i++){
        dis[i]=100000000000000000;
    } 
    for(int i=1;i<=n+1;i++){
        for(int x=1;x<=n;x++){
            for(pair<long long,long long> y:s[x]){
                if(dis[x]+y.second<dis[y.first]){
                    dis[y.first]=dis[x]+y.second;
                    p[y.first]=x;
                    st=x;
                }
            }
        }
        //for(int j=1;j<=n;j++){
        //    cout<<dis[j]<<" ";
        //}cout<<endl;
    }
    for(int x=1;x<=n;x++){
        for(pair<long long,long long> y:s[x]){
            if(dis[x]+y.second<dis[y.first]){
                return;
            }
        }
    }
    cout<<"NO";
    exit(0);
}
int main(){
    cin>>n>>m;
    long long u,vv,w;
    //for(int i=1;i<=n;i++){
    //    s[0].push_back({i,0});
    //}
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&u,&vv,&w);
        if(u==vv&&w<0){
            cout<<"YES"<<endl<<u<<" "<<u;
            exit(0);
        }
        s[u].push_back({vv,w});
    }
    ford();
    vector<int>ans;
    int cu=st;
    while(1){
        //cout<<cu<<" "<<v[cu]<<endl;
        
        ans.push_back(cu);
        if(v[cu]==1){
            st=cu;
            break;
        }
        v[cu]=1;
        cu=p[cu];
        
    }
    cout<<"YES"<<endl;
    //for(int i=1;i<=n;i++){
    //    cout<<p[i]<<" ";
    //}
    cout<<st<<" ";
    for(int i=ans.size()-2;i>=0;i--){
        cout<<ans[i]<<" ";
        if(ans[i]==st){
            //cout<<endl<<ans[i]<<"dsgdf";
            break;
        }
    }
    
}