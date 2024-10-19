#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define MOD 1000000007
 
int N;
long long p = 500000004LL;
char A[2005][2005];
char B[2005][2005];
int r[2005][2005];
int b[2005][2005];
int psr[2005][2005];
int psb[2005][2005];
 
int main()
{
	cin >> N;
	for(int i=0;i<N;i++)
		cin >> (A[i+1]+1);
	for(int i=2;i<=N+1;i++)
		if(A[i-1][1] == '.')
			b[i][0] = psb[i][0] = p;
	for(int j=1;j<=N;j++)
		if(A[1][j] == '.')
			r[1][j] = psr[1][j] = p;
	for(int i=2;i<=N+1;i++)
		for(int j=1;j<=N;j++)
		{
			if(A[i][j] == '.')
			{
				r[i][j] = (p*psb[i][j-1])%MOD;
			}
			if(A[i-1][j+1] == '.')
			{
				b[i][j] = (p*psr[i-1][j])%MOD;
			}
			psr[i][j] = (psr[i-1][j] + r[i][j])%MOD;
			psb[i][j] = (psb[i][j-1] + b[i][j])%MOD;
		}
	int ans = (psr[N][N] + psb[N+1][N])%MOD;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			if(A[i][j]=='.')
				ans = (2LL*ans)%MOD;
	cout << ans << '\n';
}