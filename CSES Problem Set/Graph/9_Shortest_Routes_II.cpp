
#include<iostream>
#include<vector>
using namespace std;
long long dis[505][505],n,m,q;
void floyd(){
	for (int k=1;k<=n;k++){
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				if (dis[i][k]+dis[k][j]<dis[i][j])
					dis[i][j]=dis[i][k]+dis[k][j];
			}
		}
	}
}
int main(){
	cin>>n>>m>>q;
    long long u,v,w;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=100000000000000000;
        }
        dis[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=min(dis[v][u],w);
    }
    floyd();
    for(int i=1;i<=q;i++){
        cin>>u>>v;
        if(dis[u][v]==100000000000000000){
            printf("-1\n");
            continue;
        }
        printf("%lld\n",dis[u][v]);
    }
	
	return 0;
}
