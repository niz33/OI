#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,a,b) for ( int i=(a);i>=(b);i-- )
#define FOR(i,t) for ( int i=head[t];i;i=e[i].nex )
#define int long long
#define db double
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define lowbit(x) x&(-x)
using namespace std;

namespace IO {
	#define gc getchar
	#define pt putchar
	inline int read() {
		int sum=0,ff=1; char ch=gc();
		while(!isdigit(ch)) {
			if(ch=='-') ff=-1;
			ch=gc();
		}
		while(isdigit(ch))
			sum=sum*10+(ch^48),ch=gc();
		return sum*ff;
	}

	inline void write(int x) {
		if(x<0) pt('-'),x=-x;
		if(x>9) write(x/10);
		pt(x%10|48);
	}

	inline void wln(int x) {
		write(x); pt('\n');
	}

	inline void wrn(int x) {
		write(x); pt(' ');
	}
}

using namespace IO;

const int N=1000005;

int n,m,c[N*2],bo[N],ans;

struct number {
	int x,y,z;
};
number a[N],tmp[N];

inline bool cmpy(number a,number b) {
	if(a.y==b.y) return a.z<b.z;
	return a.y>b.y;
}

inline bool cmpx(number a,number b) {
	if(a.x==b.x) {
		if(a.y==b.y) return a.z<b.z;
		return a.y>b.y;
	}
	return a.x<b.x;
}
//三维排序

inline void add(int x,int val) {
	while(x<=n) {
		c[x]+=val;
		x+=lowbit(x);
	}
}

inline int query(int x) {
	int ret=0;
	x=min(x,n);
	x=max(x,0ll);
    //注意边界,被坑了好久
	while(x) {
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}

inline void cdq(int l,int r) {
//cdq模板
	if(l==r) return;
	int mid=(l+r)/2;
	cdq(l,mid);
	cdq(mid+1,r);
	sort(a+l,a+mid+1,cmpy);
	sort(a+mid+1,a+r+1,cmpy);
	int i=mid+1,j=l;
	for (;i<=r;i++) {
		while(j<=mid&&a[j].y>a[i].y) {
			add(a[j].z,1);
			j++;
		}
		ans+=query(a[i].z-m-1)+query(n)-query(a[i].z+m);
       //计算单次贡献
	}
	For(i,l,j-1) add(a[i].z,-1);//清空树状数组
}
	
signed main() {
	n=read();
	m=read();
	For(i,1,n) bo[read()]=i;
    //映射数组
	For(i,1,n) {
		int x=read();
		a[i]=(number){bo[x],i,x};
        //建立三元组
	}
	sort(a+1,a+n+1,cmpx);
	cdq(1,n);
	wln(ans);
	return 0;
}