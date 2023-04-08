#include<iostream>
using namespace std;
int n,q,a,b,s[200005],g[200005],l[200005],d[200005],gc=0,v[200005],f[200005][30],br[200005];
int group(int x){
    cout<<x<<endl;
    v[x]=1;
    int t=0;
    if(v[s[x]]){
        gc++;
        g[x]=gc;
        br[s[x]]=1;
        l[x]=0;
        t=1;
    }
    else{
        if(!g[s[x]]){
            t=group(s[x]);
        }
        if(!t){
            d[x]=d[s[x]]+1;
        }
        else{
            l[x]=l[s[x]]+1;
        }
        g[x]=g[s[x]];
    }
    v[x]=0;
    if(t&&(!br[x])){
        return 1;
    }
    return 0;
}
int go(int x,int k){
    int pc=0;
    int ans=x;
    while(k){
        if((k&1)==1){
            ans=f[ans][pc];
        }
        pc++;
        k=(k>>1);
    }
    return ans;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        l[i]=-1;
        cin>>s[i];
        f[i][0]=s[i];
    }
    for(int i=1;i<=n;i++){
        if(!g[i]){
            cout<<"------\n";
            group(i);
        }
    }
    for(int i=1;i<=n;i++){
        cout<<g[i]<<" "<<d[i]<<" "<<l[i]<<endl;
    }
    int p=2,pc=1;
    while(p<=n){
        for(int i=1;i<=n;i++){
            f[i][pc]=f[f[i][pc-1]][pc-1];
        }
        p=(p<<1);
        pc++;
    }
}