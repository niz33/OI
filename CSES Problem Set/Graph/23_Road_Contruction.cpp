#include<iostream>
using namespace std;
int f[1000005],s[1000005],n,m,maxx=1,cnt;
int findd(int x){
    if(f[x]==x){
        return x;
    }
    f[x]=findd(f[x]);
    return f[x];
}
void unionn(int x,int y){
    int fx=findd(x),fy=findd(y);
    if(fx!=fy){
        f[fy]=fx;
        s[fx]+=s[fy];
        maxx=max(s[fx],maxx);
        cnt--;
    }
}

int main(){
    cin>>n>>m;
    cnt=n;
    for(int i=1;i<=n;i++){
        f[i]=i;
        s[i]=1;
    }
    int x,y;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        unionn(x,y);
        cout<<cnt<<" "<<maxx<<endl;
    }
}