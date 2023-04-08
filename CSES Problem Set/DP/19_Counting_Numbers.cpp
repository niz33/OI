#include<iostream>
using namespace std;
long long count(long long x,long long b){
    if(x==0){
        return 1;
    }
    long long f,c=0;
    long long xc=x;
    long long ans=1,p=1;
    while(xc>0){
        f=xc%10;
        xc/=10;
        c++;
        p*=10;
    }
    p/=10;
    if(b<f){
        ans=f-1;
    }
    else{
        ans=f;
    }
    for(int i=1;i<c;i++){
        ans*=9;
    }
    if(b!=f){
        ans+=count(x%p,f);
    }
    return ans;
}
int main(){
    long long a,b,ans=0;
    cin>>a>>b;
    a--;
    ans+=count(b,0);
    b/=10;
    long long p=1;
    while(b){
        p*=10;
        ans+=count(p-1,0);
        b/=10;
    }
    if(!(a+1)){
        cout<<ans<<endl;
        return 0;
    }
    ans-=count(a,0);
    a/=10;
    p=1;
    while(a){
        p*=10;
        ans-=count(p-1,0);
        a/=10;
    }
    cout<<ans<<endl;
}