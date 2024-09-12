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
const int N=200005;
int n,a[N],q[N],stt=0,r[N],st[N];
struct frac{
    ll n,d;
    bool operator>=(frac x){
        if(d*x.d<0) return n*x.d<=x.n*d;
        return n*x.d>=x.n*d;
    }
}ans[N];
struct line{
    ll a,q;
    int ind;
}l[N];
frac intersect(line x,line y){
    return {x.a-y.a,x.ind-y.ind};
}
bool geq_zero(frac x){
    return (x.n>=0&&x.d>=0)||(x.n<=0&&x.d<=0);
}
bool compare(line x,line y){
    return x.a>y.a;
}
int binary_search(int i,int lll,int rrr){
    int mid=(lll+rrr)/2;
    if()

}
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>q[i];
    for(int i=1;i<=n;i++){
        l[i].a=a[i];
        l[i].q=q[i];
        l[i].ind=i;
    }
    sort(l+1, l+n+1, compare);
    for(int i=1;i<=n;i++) r[l[i].ind]=i;
    st[++stt]=1;
    frac temp=intersect(l[1],l[r[l[1].q]]);
    ans[l[1].ind]=geq_zero(temp)?temp:(frac){-1,1};
    for(int i=2;i<=n;i++){
        while(stt>0){
            if(l[i].ind>l[st[stt]].ind){
                stt--;
                continue;
            }
            if(stt>1){
                if(intersect(l[i],l[st[stt]])>=intersect(l[st[stt]],l[st[stt-1]])){
                    stt--;
                    continue;
                }
            }
            break;
        }
        st[++stt]=i;
        temp=intersect(l[i],l[r[l[i].q]]);

        ans[l[i].ind]=geq_zero(temp)?temp:(frac){-1,1};
    }
    for(int i=1;i<=n;i++) cout<<ans[i].n<<'/'<<ans[i].d<<'\n';
    return 0;
}