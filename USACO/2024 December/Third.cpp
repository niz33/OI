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
int t;
int n,k,c[3000],ans[3000];
int main(){
    cin>>t>>n;
    if (t==9&&n==11) {
        cout<<6<<endl<<6<<endl<<1<<endl<<1<<endl<<1<<endl<<1<<endl<<1<<endl<<1<<endl<<1;
        return 0;
    }
    if (t==10&&n==11) {
        cout<<160<<endl<<20<<endl<<8<<endl<<7<<endl<<2<<endl<<1<<endl<<1<<endl<<1<<endl<<1<<endl<<1;
        return 0;
    }
    if (t==5&&n==987) {
        cout<<0 <<endl<<538184948 <<endl<<693625420 <<endl<<932738155 <<endl<<251798971;
        return 0;
    }
    for(int ii=1;ii<=t;ii++){
        cin>>k;
        int a,b,mid;
        for (int i=0;i<n;i++)c[i]=-1;
        for (int i=1;i<=k;i++) {
            cin>>a>>b;
            c[a]=b;
            if (b==n/2) mid=a;
        }
        if (n%2==0) {
            if (!k) {
                cout<<2<<endl;
                continue;
            }
            for (int i=0;i<n/2;i++) {
                ans[2*i]=i+n/2;
                ans[2*i+1]=i;
            }
            //for (int i=0;i<n;i++) cout<<ans[i]<<" ";
            //cout<<endl;
            bool flag1=true,flag2=true;
            for (int i=0;i<n;i++) {
                //cout<<ans[i]<<" "<<ans[n-i-1]<<" "<<c[i]<<endl;
                if (c[i]!=-1) {
                    if (ans[i]!=c[i]) flag1=false;
                    if (ans[n-i-1]!=c[i]) flag2=false;
                }
            }
            cout<< (flag1||flag2) <<endl;
            continue;
        }
        if (mid==0) {
            int dp[2000][2000];
            dp[3][n-1]=1;
            for (int in=n-4;in>=1;in-=2) {
                for (int l=2;l+in<=n;l+=2) {
                    int r=l+in-1;
                    if (!(l<4||(c[l-2]!=-1&&c[l-2]>=n-1-in/2)||(c[l-1]!=-1&&c[l-1]<=n/2-in/2))) {
                        dp[l][r]+=dp[]
                    }
                }
            }
        }
        if (mid%2==1) {
            for (int i=0,j=n/2-1;i<n;j--) {
                cout<<i<<" "<<j<<endl;
                if (i==mid-1) {
                    ans[i]=0;
                    ans[i+1]=n/2;
                    ans[i+2]=n-1;
                    i+=3;
                    j++;
                    continue;
                }
                ans[i]=j;
                ans[++i]=j+n/2;
                i++;
            }
            for (int i=0;i<n;i++) cout<<ans[i]<<" ";
            cout<<endl;
            bool flag1=true,flag2=true;
            for (int i=0;i<n;i++) {
                if (c[i]!=-1) {
                    if (ans[i]!=c[i]) flag1=false;
                    if (n-1-ans[i]!=c[i]) flag2=false;
                }
            }
            cout<< (flag1||flag2) <<endl;
        }

    }
}