#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<numeric>
#pragma GCC optimize("Ofast")
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
    ll ind;
}l[N];
frac intersect(line x,line y){
    return {x.a-y.a,x.ind-y.ind};
}
bool geq_zero(frac x){
    return (x.n>=0&&x.d>=0)||(x.n<=0&&x.d<=0);
}
bool compare1(line &x,line &y){
    return x.a>y.a;
}
bool compare2(line &x,line &y){
    return x.a<y.a;
}
frac binary_search1(int r,int lll,int rrr){
    //cout<<r<<" "<<lll<<" "<<rrr<<endl;
    int mid=(lll+rrr)/2;
    if(l[r].ind>l[st[1]].ind){
        //cout<<"cant "<<l[r].ind<<" "<<l[st[1]].ind<<endl;
        return {1,-1};
    }
    if(l[r].ind>l[st[mid]].ind) return binary_search1(r,lll,mid-1);
    frac in=intersect(l[st[mid]],l[r]);
    if(lll==rrr) return in;
    if(intersect(l[st[mid]],l[st[mid+1]])>=in) return binary_search1(r,mid+1,rrr);
    if(mid==1) return in;
    if(in>=intersect(l[st[mid]],l[st[mid-1]])) return binary_search1(r,lll,mid-1);
    return in;
}
frac binary_search2(int r,int lll,int rrr){
    int mid=(lll+rrr)/2;
    // if(l[r].ind==90){
    //     cout<<"good"<<r<<" "<<lll<<" "<<rrr<<endl;
    //     for(int j=1;j<=stt;j++) cout<<l[st[j]].ind<<" ";cout<<endl;
    // }
    if(l[r].ind<l[st[1]].ind){
        return {1,-1};
    }
    if(l[r].ind<l[st[mid]].ind) return binary_search2(r,lll,mid-1);
    frac in=intersect(l[st[mid]],l[r]);
    // if(l[r].ind==90){
    //     cout<<in.n<<" "<<in.d<<endl;
    // }
    if(lll==rrr) return in;

    
    if(intersect(l[st[mid]],l[st[mid+1]])>=in) return binary_search2(r,mid+1,rrr);

    if(mid==1) return in;

    if(in>=intersect(l[st[mid]],l[st[mid-1]])) return binary_search2(r,lll,mid-1);

    return in;
}
ll gcd(ll a,ll b){
    return b==0?a:gcd(b,a%b);
}
frac simplify(frac x){
    ll g=gcd(x.n,x.d);
    return {x.n/g,x.d/g};
}
int main() {
    freopen("falling.in","r",stdin);
    freopen("falling.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>q[i];
    for(int i=1;i<=n;i++){
        l[i].a=a[i];
        l[i].q=q[i];
        l[i].ind=i;
    }
    sort(l+1, l+n+1, compare1);
    for(int i=1;i<=n;i++) r[l[i].ind]=i;
    //st[++stt]=1;
    //frac temp=intersect(l[1],l[r[l[1].q]]);
    //ans[l[1].ind]=geq_zero(temp)?temp:(frac){-1,1};
    for(int i=1;i<=n;i++){
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
        if(l[r[l[i].q]].a<l[i].a){//cout<<l[i].ind<<" "<<r[l[i].q]<<" "<<stt<<" ";
        //for(int j=1;j<=stt;j++) cout<<l[st[j]].ind<<" ";cout<<endl;
        ans[l[i].ind]=binary_search1(r[l[i].q],1,stt);}
    }
    sort(l+1, l+n+1, compare2);
    for(int i=1;i<=n;i++) r[l[i].ind]=i;
    stt=0;
    //cout<<"asdasdasdsa"<<endl;
    //st[stt=1]=1;
    //temp=intersect(l[1],l[r[l[1].q]]);
    //ans[l[1].ind]=geq_zero(temp)?temp:(frac){-1,1};
    for(int i=1;i<=n;i++){
        while(stt>0){
            if(l[i].ind<l[st[stt]].ind){
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
        if(l[r[l[i].q]].a>l[i].a){//cout<<l[i].ind<<" "<<r[l[i].q]<<" "<<stt<<" ";
        //for(int j=1;j<=stt;j++) cout<<l[st[j]].ind<<" ";cout<<endl;
        ans[l[i].ind]=binary_search2(r[l[i].q],1,stt);}
        // if(l[i].ind==4){
        //     cout<<ans[l[i].ind].n<<" "<<ans[l[i].ind].d<<endl;
        // }
    }
    for(int i=1;i<=n;i++) ans[i]=simplify(ans[i]);
    for(int i=1;i<=n;i++) if(ans[i].n==-1) cout<<"-1\n"; else cout<<ans[i].n<<'/'<<ans[i].d<<'\n';
    return 0;
}

