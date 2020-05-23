//Author <ftw>Retaliation
#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define MOD 1000000007
#define infi (long long)1e9
#define FOR(i,a,b) for(i = a; i < b; i++)
#define FORD(i,a,b) for(i = a; i >= b; i--)
#define REP(i,a) for(i = 0;i <= a; i++)
#define REPD(i,a) for(i = a; i >= 0; i--)
#define s(n)  scanf("%d", &n)
#define sc(n)  scanf("%c", &n)
#define sl(n) scanf("%I64d", &n)
#define sf(n) scanf("%lf", &n)
#define ss(n) scanf("%s", n);
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define p(x) prlong longf("%d", x)
#define pl(x) prlong longf("%I64d", x)
#define pd(x) prlong longf("%.10lf",x)
#define pe() prlong longf("\n")
#define fill(a, v) memset(a, v, sizeof(a))
#define PI 3.1415926535897932384626
#define mem(x) memset(x, -1, sizeof(x))
#define memz(x) memset(x, 0, sizeof(x))

long long dp[1000];

long long fnc(long long n, long long m) {
	if(n == 1) {
		return 1;
	}
	if(n == 2) {
		return 2;
	}
	if(dp[n] != -1)
		return dp[n];

	long long sum = 0;
	for(long long i = 1; i <= m; i++) {
		sum += fnc(n-i,m);
	}

	dp[n] = sum;
	return dp[n];
}

int main() {
	long long t;

	cin >> t;
	while(t-- > 0) {
		long long res;
		long long n;

		cin >> n;
		for(long long i = 0; i <= n; i++)
			dp[i] = -1;

		res = fnc(n,2);
		cout << n << "\t" << res << endl;
	}

	return 0;
}

