#include<iostream>
using namespace std;
int n,m,p[1005][1005],v[1005][1005],ans;
void floodfill(int x,int y){
    v[x][y]=1;
    if(p[x-1][y]&&!v[x-1][y])floodfill(x-1,y);
    if(p[x+1][y]&&!v[x+1][y])floodfill(x+1,y);
    if(p[x][y-1]&&!v[x][y-1])floodfill(x,y-1);
    if(p[x][y+1]&&!v[x][y+1])floodfill(x,y+1);
}
int main(){
    cin>>n>>m;
    char temp;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>temp;
            p[i][j]=(temp=='.');
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(p[i][j]&&!v[i][j]){
                floodfill(i,j);
                ans++;
            }
        }
    }
    cout<<ans;
}