#include<iostream>
using namespace std;
int n,k,m[2000000],l[2000000],v[2000000],p[21],w[21];
void dp(int x){
    l[x]=100;
    m[x]=2000000000;
    //cout<<x<<":";
    for(int i=0;i<n;i++){
        v[x]=1;
        int y=x-p[i];
        
        if ((p[i]&x)>0)
        {
            //cout<<y<<" ";
            if(!v[y]){
                dp(y);
            }
            int ln,mn;
        if(m[y]+w[i]<=k){
            mn=m[y]+w[i];
            ln=l[y];
        }
        else{
            mn=w[i];
            ln=l[y]+1;
        }
        if(ln<=l[x]){
            l[x]=ln;
            if(mn<m[x]){
                m[x]=mn;
            }
        }
        }
        
    }
    //cout<<endl;
}
int main(){
    cin>>n>>k;
    l[0]=1;
    v[0]=1;
    m[0]=0;
    p[0]=1;
    for(int i=0;i<n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=20;i++){
        p[i]=p[i-1]*2;
    }
    dp(p[n]-1);
    for(int i=0;i<=p[n]-1;i++){
        //cout<<i<<" "<<l[i]<<" "<<m[i]<<endl;
    }
    cout<<l[p[n]-1];
}