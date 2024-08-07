#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<string>
using namespace std;
#define ll long long
#define pb push_back
int n,ran[20][200005],ind[200005],b[200005],bt=0,in[200005],ans[200005];
char a[200005];
string s[200005];
vector<int> rad1[200005];
vector<int> rad2[200005];
int main() {
    //freopen("standingout.in","r",stdin);
    //freopen("standingout.out","w",stdout);
    cin>>n;
    int tbt=n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        b[i]=bt+1;
        for(int j=0;j<s[i].size();j++) ran[0][++bt]=s[i][j]-'a'+2,in[bt]=i,a[bt]=s[i][j];
        ran[0][++bt]=1;
        a[bt]='%';
    }
    b[n+1]=bt+1;
    //for(int i=1;i<=bt;i++) cout<<a[i];cout<<endl;
    for(int i=1;i<20;i++) ran[i][bt]=1;
    for(int i=1;i<20;i++){
        //for(int j=1;j<=bt;j++) cout<<ran[i-1][j]<<" ";cout<<endl;
        for(int j=1;j<=max(bt,30);j++) rad1[j].clear(), rad2[j].clear();
        for(int j=1;j<bt;j++) rad1[ran[i-1][j+1]].pb(j);
        for(int j=1;j<=max(bt,30);j++) for(int k:rad1[j]) rad2[ran[i-1][k]].pb(k);
        int ra=1;
        int la1=0,la2=0;
        for(int j=1;j<=max(bt,30);j++) for(int k:rad2[j]){
            if (ran[i-1][k]!=la1||ran[i-1][k+1]!=la2) ra++;
            ran[i][k]=ra;
            la1=ran[i-1][k];
            la2=ran[i-1][k+1];
        } 
    }
    for(int i=1;i<=bt;i++) ind[ran[19][i]]=i;//cout<<ran[19][i]<<" ";cout<<endl;
    //for(int i=1;i<=bt;i++) {for(int j=ind[i];a[j]!='%';j++)cout<<a[j];cout<<endl;}
    for(int i=1;i<=bt;i++){
        if(a[i]=='%') continue;
        int l=0,r=0,rp=1;
        if(ran[19][i]>1) for(int j=0;a[i+j]!='%'&&a[ind[ran[19][i]-1]+j]!='%'&&a[i+j]==a[ind[ran[19][i]-1]+j];j++) l++;
        while(in[ind[ran[19][i]+rp]]==in[i]) rp++;
        if(ran[19][i]+rp<=bt) for(int j=0;a[i+j]!='%'&&a[ind[ran[19][i]+rp]+j]!='%'&&a[i+j]==a[ind[ran[19][i]+rp]+j];j++) r++;
        //cout<<l<<" "<<r<<" "<<b[in[i]+1]-i-1<<endl;
        ans[in[i]]+=b[in[i]+1]-max(l,r)-1-i;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}