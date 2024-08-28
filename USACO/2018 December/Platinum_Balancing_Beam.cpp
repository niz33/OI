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
ll n,h[100005];
vector<int> st;

ll cross_p(cpair<ll,ll> a,cpair<ll,ll> b){
    return a.x*b.y-a.y*b.x;
}
ll wrap_p(cpair<ll,ll> a,cpair<ll,ll> b,cpair<ll,ll> c){
    return cross_p({b.x-a.x,b.y-a.y},{c.x-b.x,c.y-b.y});
}
int main() {
    freopen("balance.in","r",stdin);
    freopen("balance.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    st.pb(0);
    st.pb(1);
    for(int i=2;i<=n+1;i++){
        while(st.size()>1&&wrap_p({st[st.size()-2],h[st[st.size()-2]]},{st[st.size()-1],h[st[st.size()-1]]},{i,h[i]})>=1){
            st.pop_back();
        }
        st.pb(i);
    }
    for(int i=1;i<st.size();i++){
        //cout<<h[st[i]]<<" ";
        for(int j=st[i-1]+1;j<st[i];j++){
            h[j]=(h[st[i-1]]*(st[i]-j)+h[st[i]]*(j-st[i-1]))*100000/(st[i]-st[i-1]);
        }
    }
    for(int i: st){
        h[i]*=100000;
    }
    for(int i=1;i<=n;i++){
        cout<<h[i]<<endl;
    }
    return 0;
}