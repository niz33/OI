#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define int long long
#define ll long long
#define pb push_back
int n;
pair<int,int> ps[200005];
vector<int> st;
set<pair<int,int>> s;
signed main() {
    cin>>n;
    ps[0]={2e9,2e9};
    for(int i=1;i<=n;i++){
        cin>>ps[i].first>>ps[i].second;
    }
    sort(ps+1,ps+n+1,[&](pair<int,int> a,pair<int,int> b){
        return (a.first<b.first)||(a.first==b.first&&a.second<b.second);
    });
    st.pb(1);
    st.pb(2);
    for(int i=3;i<=n;i++){
        while(st.size()>1){
            int x1=ps[st[st.size()-1]].first-ps[st[st.size()-2]].first;
            int y1=ps[st[st.size()-1]].second-ps[st[st.size()-2]].second;
            int x2=ps[i].first-ps[st[st.size()-1]].first;
            int y2=ps[i].second-ps[st[st.size()-1]].second;
            if(x1*y2-x2*y1<=0) break;
            st.pop_back();
        }
        st.pb(i);
    }
    for(int i=n-1;i>=1;i--){
        while(st.size()>1){
            int x1=ps[st[st.size()-1]].first-ps[st[st.size()-2]].first;
            int y1=ps[st[st.size()-1]].second-ps[st[st.size()-2]].second;
            int x2=ps[i].first-ps[st[st.size()-1]].first;
            int y2=ps[i].second-ps[st[st.size()-1]].second;
            if(x1*y2-x2*y1<=0) break;
            st.pop_back();
        }
        st.pb(i);
    }
    cout<<st.size()-1<<endl;
    for(int i=0;i<st.size()-1;i++) cout<<ps[st[i]].first<<" "<<ps[st[i]].second<<endl;
    return 0;
}