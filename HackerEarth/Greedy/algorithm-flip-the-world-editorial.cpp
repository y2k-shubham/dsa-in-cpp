#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<vector>
#include<cassert>
#include<sstream>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define clr(x) x.clear()
#define sz(x) ((int)(x).size())
#define F first
#define S second
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,b) for(i=0;i<b;i++)
#define rep1(i,b) for(i=1;i<=b;i++)
#define pdn(n) printf("%d\n",n)
#define sl(n) scanf("%lld",&n)
#define sd(n) scanf("%d",&n)
#define pn printf("\n")
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
#define MOD 1000000007
LL mpow(LL a, LL n) {
	LL ret=1;
	LL b=a;
	while(n) {
		if(n&1)
			ret=(ret*b)%MOD;
		b=(b*b)%MOD;
		n>>=1;
	}
	return (LL)ret;
}
int main() {
	int t;
	t= 1;
	while(t--) {
		int n,m,i,j,a[60][60]= {};
		vector <string> board;
		sd(n),sd(m);
		board.resize(n);
		for(i=0; i<n; i++)
			cin >> board[i];
		for(i=n-1; i>=0; --i)
			for(j=m-1; j>=0; --j) {
				if(i==n-1&&j==m-1)
					a[i][j]=0;
				else if(i==n-1)
					a[i][j]=a[i][j+1];
				else if(j==m-1)
					a[i][j]=a[i+1][j];
				else
					a[i][j]=a[i+1][j]+a[i][j+1]-a[i+1][j+1];
				if((a[i][j]%2==1&&board[i][j]=='1')||(a[i][j]%2==0&&board[i][j]=='0'))
					a[i][j]++;
			}
		pdn(a[0][0]);
	}
	return 0;
}
