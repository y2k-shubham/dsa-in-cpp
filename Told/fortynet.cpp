#include <bits/stdc++.h>
using namespace std;
long long cenergy[1001], capples[1001], en[1001], ap[1001], n;

int recurse (int ind, long long e, int apples) {
	if (ind == n+1) {
		return apples;
	}
	if (e > 0)
		return max (recurse (ind+1, e-1, apples+ap[ind]), recurse (ind + 1, e + en[ind], apples));

	else {
		if (e + en[ind] > 0)
			return recurse (ind + 1, e+en[ind], apples);

	}
}

int main() {
	int t,i;
	cin>>t;
	while(t--) {

		memset(cenergy, -1, sizeof(cenergy));
		memset(capples, -1, sizeof(capples));
		int e;
		cin>>n>>e;
		ap[0] = en[0] = 0;
		for (int i=1; i <= n; i++) cin>>en[i];
		for (int i=1; i <= n; i++) cin>>ap[i];
		cenergy[0] = e;
		capples[0] =0 ;

		cout<<recurse(0, e, 0)<<endl;
	}
	return 0;
}

