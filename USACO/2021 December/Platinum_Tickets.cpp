#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define ll long long
#define pb push_back

int n,m;
struct ticket{
    ll a,b,c,p,ind;
}no={0,0,0,0,0};
bool cmpticket(ticket a,ticket b) {
    return a.b<b.b;
}
vector<ticket> ti[100005],tis;
ll t[500000],dist1[200005],distn[200005],distans[200005];
void init(int x,int xl,int xr){
    if(xl==xr){
        if(ti[xl].size()==0){
            t[x]=0;
        }else{
            t[x]=ti[xl][ti[xl].size()-1].b;
        }
        return;
    }
    int xm=(xl+xr)/2;
    init(x<<1,xl,xm);
    init((x<<1)+1,xm+1,xr);
    t[x]=max(t[2*x],t[2*x+1]);
}
ticket get(int x,int xl,int xr, int p){
    //cout<<"call "<<t[x]<<" "<<x<<" "<<xl<<" "<<xr<<" "<<p<<endl;
    if(xl==xr){
        ticket ans=ti[xl][ti[xl].size()-1];
        ti[xl].pop_back();
        if(ti[xl].size()==0){
            t[x]=0;
        }else{
            t[x]=ti[xl][ti[xl].size()-1].b;
        }
        return ans;
    }
    int xm=(xl+xr)/2;
    ticket ans;
    if(t[x<<1]>=p){

        ans=get(2*x,xl,xm,p);
    }
    else if(t[(x<<1)+1]>=p&&p>xm){
        ans=get(2*x+1,xm+1,xr,p);
    }
    else return no;
    t[x]=max(t[x<<1],t[(x<<1)+1]);
    return ans;
}
struct node{
    ll v,d;
    bool operator>(const node &a)const{
        return d>a.d;
    }
    bool operator<(const node &a)const{
        return d<a.d;
    }
};
priority_queue<node, vector<node>, greater<node> > dij1,dijn,dijans;
int vis1[200005],visn[200005],visans[200005];
int main() {
    cin>>n>>m;
    int a,b,c,p;
    tis.pb(no);
    for(int i=1;i<=m;i++){
        cin>>p>>c>>a>>b;
        tis.pb((ticket){a,b,c,p,i+n});
        ti[a].pb((ticket){a,b,c,p,i+n});
    }
    for (int i=1;i<=n+m;i++) dist1[i]=distn[i]=distans[i]=1e18;
    for(int i=1;i<=n;i++) sort(ti[i].begin(),ti[i].end(),cmpticket);

    init(1,1,n);
    dij1.push((node){1,0});
    dist1[1]=distn[n]=0;
    while(!dij1.empty()){
        node x=dij1.top();
        dij1.pop();
        if(vis1[x.v]) continue;
        vis1[x.v]=1;
        //cout<<"-------------------"<<endl;
        //cout<<x.v<<" "<<x.d<<endl;

        if (x.v<=n) {

            ticket y;
            while(1){
                y=get(1,1,n,x.v);

                if(y.ind==0){
                    break;
                }
                //cout<<y.ind<<" "<<y.c<<" "<<y.a<<" "<<y.b<<endl;
                if (x.d>=dist1[y.ind]) continue;
                dist1[y.ind]=x.d;
                dij1.push((node){y.ind,dist1[y.ind]});
            }
        }
        else {
            if (x.d+tis[x.v-n].c>=dist1[tis[x.v-n].p]) continue;
            dist1[tis[x.v-n].p]=x.d+tis[x.v-n].c;
            dij1.push((node){tis[x.v-n].p,x.d+tis[x.v-n].c});
        }
    }

    for (int i=1;i<=n;i++) ti[i].clear();
    for (ticket t:tis)ti[t.a].pb(t);
    for (int i=1;i<=n;i++) sort(ti[i].begin(),ti[i].end(),cmpticket);

    init(1,1,n);
    dijn.push((node){n,0});
    while(!dijn.empty()){
        node x=dijn.top();
        dijn.pop();
        if(visn[x.v]) continue;
        visn[x.v]=1;
        //cout<<"-------------------"<<endl;
        //cout<<x.v<<" "<<x.d<<endl;
        if (x.v<=n) {
            ticket y;
            while(1){
                y=get(1,1,n,x.v);
                //cout<<y.ind<<" "<<y.c<<" "<<y.a<<" "<<y.b<<endl;
                if(y.ind==0){
                    break;
                }
                if (x.d>=distn[y.ind]) continue;
                distn[y.ind]=x.d;
                dijn.push((node){y.ind,distn[y.ind]});
            }
        }
        else {
            if (x.d+tis[x.v-n].c>=distn[tis[x.v-n].p]) continue;
            distn[tis[x.v-n].p]=x.d+tis[x.v-n].c;
            dijn.push((node){tis[x.v-n].p,x.d+tis[x.v-n].c});
        }

    }
    for (int i=1;i<=n+m;i++){
        // if(vis1[i]==0){
        //     cout<<-1<<" ";
        // }else{
        //     cout<<dist1[i]<<" ";
        // }
        // if (visn[i]==0) {
        //     cout<<-1<<endl;
        // }else{
        //     cout<<distn[i]<<endl;
        // }
        if (vis1[i]>0&&visn[i]>0) {
            dijans.push((node){i,dist1[i]+distn[i]});
            distans[i]=dist1[i]+distn[i];
        }
    }

    for (int i=1;i<=n;i++) ti[i].clear();
    for (ticket t:tis)ti[t.a].pb(t);
    for (int i=1;i<=n;i++) sort(ti[i].begin(),ti[i].end(),cmpticket);
    init(1,1,n);

    while(!dijans.empty()){
        node x=dijans.top();
        dijans.pop();
        if(visans[x.v]) continue;
        //cout<<"-------------------"<<endl;
        //cout<<x.v<<" "<<x.d<<endl;
        visans[x.v]=1;
        if (x.v<=n) {
            ticket y;
            while(1){
                y=get(1,1,n,x.v);
                //cout<<y.ind<<" "<<y.c<<" "<<y.a<<" "<<y.b<<endl;
                if(y.ind==0){
                    break;
                }

                if (x.d>=distans[y.ind]) continue;
                distans[y.ind]=x.d;
                dijans.push((node){y.ind,distans[y.ind]});
            }
        }
        else {
            if (x.d+tis[x.v-n].c>=distans[tis[x.v-n].p]) continue;
            distans[tis[x.v-n].p]=x.d+tis[x.v-n].c;
            dijans.push((node){tis[x.v-n].p,x.d+tis[x.v-n].c});
        }
    }
    for (int i=1;i<=n;i++){
        if(visans[i]==0){
            cout<<-1<<endl;
        }else{
            cout<<distans[i]<<endl;
        }
    }
    return 0;
}