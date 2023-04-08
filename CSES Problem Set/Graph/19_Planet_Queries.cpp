#include<iostream>
using namespace std;
int n,q,f[200005][30],x,k;
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        scanf("%d",&f[i][0]);
    }
    int p=2,pc=1;
    while(p<=1000000000){
        for(int i=1;i<=n;i++){
            f[i][pc]=f[f[i][pc-1]][pc-1];
        }
        p=(p<<1);
        pc++;
    }
    for(int i=1;i<=q;i++){
        scanf("%d%d",&x,&k);
        pc=0;
        int ans=x;
        while(k){
            if((k&1)==1){
                ans=f[ans][pc];
            }
            pc++;
            k=(k>>1);
        }
        printf("%d\n",ans);
    }
}