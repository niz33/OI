#include<iostream>
using namespace std;
char s[300000];
int main(){
    int n;
    cin>>n;
    long long ans=1;
    long long p=2;
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=2;i<=n;i++){
        if(s[i]==s[i-1]){
            ans*=(long long)p/2;
            ans%=1000000007;
            p=2;
        }
        else p++;
    }
    ans*=(long long)p/2;
    ans%=1000000007;
    cout<<ans;
}