#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

int n,q;
int a[250005];
struct query{
    int i,l,r,ans;
};
vector<query> qs;

int t1[1000005],t[1000005],tn=1,lazy[1000005];

stack<pair<int,int>> st;

void init1(int l,int r,int x){
    if(l==r){
        t1[x]=l;
        return;
    }
    int m=(l+r)/2;
    init1(l,m,2*x);
    init1(m+1,r,2*x+1);
    if(a[t1[2*x]]>a[t1[2*x+1]]) t1[x]=t1[2*x];
    else t1[x]=t1[2*x+1];
}

int maxq(int ql,int qr,int l,int r,int x){
    if(ql<=l&&r<=qr) return t1[x];
    int m=(l+r)/2;
    if(ql<=m&&qr>m){
        int aa=maxq(ql,qr,l,m,2*x);
        int ab=maxq(ql,qr,m+1,r,2*x+1);
        if(a[aa]>a[ab]) return aa;
        return ab;
    }
    if(ql<=m) return maxq(ql,qr,l,m,2*x);
    return maxq(ql,qr,m+1,r,2*x+1);
}

void init2(int l,int r,int x){
    if(l!=r){
        int m=(l+r)/2;
        init2(l,m,2*x);
        init2(m+1,r,2*x+1);
    }
    t[x]=0;
    lazy[x]=0;
}

void unlazy(int l,int r,int x){
    if(lazy[x]&&l!=r){
        t[2*x]+=lazy[x];
        t[2*x+1]+=lazy[x];
        lazy[2*x]+=lazy[x];
        lazy[2*x+1]+=lazy[x];
        lazy[x]=0;
    }
}

void add(int al,int ar, int l,int r,int x, int v){
    if(al<=l&&r<=ar){
        lazy[x]+=v;
        t[x]+=v;
        return;
    }
    int m=(l+r)/2;
    unlazy(l,r,x);
    if(al<=m) add(al,ar,l,m,2*x,v);
    if(ar>m) add(al,ar,m+1,r,2*x+1,v);
    t[x]=std::min(t[2*x],t[2*x+1]);
}

int minq(int ql,int qr,int l,int r,int x){
    if(ql<=l&&r<=qr) return t[x];
    int m=(l+r)/2;
    unlazy(l,r,x);
    if(ql<=m&&qr>m) return std::min(minq(ql,qr,l,m,2*x),minq(ql,qr,m+1,r,2*x+1));
    if(ql<=m) return minq(ql,qr,l,m,2*x);
    return minq(ql,qr,m+1,r,2*x+1);
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    init1(1,n,1);
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        qs.push_back({i,l,r,a[l]+a[r]+a[maxq(l+1,r-1,1,n,1)]});
    }
    //sort(qs.begin(),qs.end(),[](query a,query b){return a.i<b.i;});
    //for(int i=0;i<q;i++) cout<<qs[i].ans<<' ';
    //cout<<endl;
    sort(qs.begin(),qs.end(),[](query a,query b){return a.r<b.r;});
    init2(1,n,1);
    st.push({1000000000,1});
    st.push({0,2});
    int j=0;
    add(1,1,1,n,1,a[1]);
    for(int i=2;i<=n;i++){
        add(i,i,1,n,1,a[i]);
        while(a[i]>st.top().first){
            pair<int,int> t=st.top();
            st.pop();
            add(st.top().second,t.second-1,1,n,1,a[i]-t.first);
        }
        st.push({a[i],i});
        st.push({0,i+1});
        
        while(j<q&&qs[j].r==i){
            int m=maxq(qs[j].l,qs[j].r-2,1,n,1);
            qs[j].ans=std::min(qs[j].ans,a[m]+minq(m+1,i-1,1,n,1));
            j++;
        }
    }
    //sort(qs.begin(),qs.end(),[](query a,query b){return a.i<b.i;});
    //for(int i=0;i<q;i++) cout<<qs[i].ans<<' ';
    //cout<<endl;
    sort(qs.begin(),qs.end(),[](query a,query b){return b.l<a.l;});
    init2(1,n,1);
    st.push({1000000000,n});
    st.push({0,n-1});
    j=0;
    add(n,n,1,n,1,a[n]);
    for(int i=n-1;i>=1;i--){
        add(i,i,1,n,1,a[i]);
        while(a[i]>st.top().first){
            pair<int,int> t=st.top();
            st.pop();
            add(t.second+1,st.top().second,1,n,1,a[i]-t.first);
        }
        st.push({a[i],i});
        st.push({0,i-1});
        while(j<q&&qs[j].l==i){
            int m=maxq(qs[j].l+2,qs[j].r,1,n,1);
            qs[j].ans=std::min(qs[j].ans,a[m]+minq(i+1,m-1,1,n,1));
            j++;
        }
    }
    sort(qs.begin(),qs.end(),[](query a,query b){return a.i<b.i;});
    for(int i=0;i<q;i++) cout<<qs[i].ans<<' ';
    cout<<endl;
}