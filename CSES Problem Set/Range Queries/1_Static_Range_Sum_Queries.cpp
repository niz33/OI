#include<iostream>
using namespace std;
long long sum[200005];
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>sum[i];
        sum[i]+=sum[i-1];
    }
    int l,r;
    for(int i=1;i<=q;i++){
        cin>>l>>r;
        cout<<sum[r]-sum[l-1]<<endl;
    }
}