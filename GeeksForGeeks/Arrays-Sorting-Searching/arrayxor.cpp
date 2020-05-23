
/*
5
4 2 4 5 2 3 1
*/

#include <bits/stdc++.h>

using namespace std;
int main()
{
	int n;
	cin >> n;
	int a[n+2];
	int res1 = 0, res2 = 0;
	cin >> a[0];
	res2 = a[0];
	res1 ^= a[0];
	for (int i = 1; i < n + 2; i++) {
		cin >> a[i];
		res2 ^= a[i];
		res1 ^= a[i];
	}

	cout << res2 << " \t :  " << res1 << endl;
	int res3 = 0;
	for (int i = 0; i <= 150; i++) {
		res3 ^= i;
	}
	cout << res3 << "\t" << (res3^res1);

}
