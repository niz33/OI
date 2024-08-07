#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb push_back
int n,c[100005],p[100005];

int main() {
    freopen("greedy.in","r",stdin);
    freopen("greedy.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i],c[i]=n-c[i];
    int l=1,r=n;
    while(l!=r){
        for(int i=1;i<=n;i++) p[i]=0;
        int m=(l+r)/2;
        //cout<<l<<" "<<r<<" "<<m<<endl;
        for(int i=1;i<m;i++) p[c[i]]++;
        for(int i=1;i<=n;i++) p[i]+=p[i-1];
        bool b=false;
        // for(int i=1;i<=n;i++){
        //     cout<<p[i]<<" ";
        // }cout<<endl;
        for(int i=1;i<=n;i++) if(p[i]>=i) b=true;
        if(b) r=m;
        else l=m+1;
    }
    cout<<n-l+1;
    return 0;
}