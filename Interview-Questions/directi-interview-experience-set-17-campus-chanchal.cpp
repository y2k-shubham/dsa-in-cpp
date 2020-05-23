/*
12
5 10 0 1 2 8 1 3 7 4 2 9
5
9 5 2 8 2

8
9 0 4 5 1 2 6 3
6
2 1 3 7 4 8

5
1 9 0 4 5
2
2 9
*/

#include<bits/stdc++.h>
using namespace std;

//bool compare(const pair<int,int>&p1, const pair<int,int>&p2) {
//	return p1.first < p2.first;
//}

int main() {
	int t;

	cin>>t;
	while(t--) {
		int n;
		int m;

		cin>>n;
		int a[n];
		priority_queue<pair<int,int> >pq;

		for(int i = 0; i < n ; i++) {
			cin>>a[i];
			printf("(%d, %d) pushed in que\n", a[i], i);
			pq.push(make_pair(a[i],i));
		}

		cin>>m;
		int b[m];
		for(int i = 0; i < m; i++) {
			cin>>b[i];
		}

		int ctr = 0;
		vector<pair<int,int> >vec;

		while(ctr < m) {
			pair<int,int>temp;

			temp = pq.top();
			pq.pop();

			printf("(%d, %d) pushed in vec\n", temp.second, temp.first);
			vec.push_back(make_pair(temp.second,temp.first));
			ctr++;
		}

		//vec.sort(vec.begin(),vec.end(),compare);
		int res = 0;
		sort(vec.begin(),vec.end());

		for(int i = 0; i < m; i++) {
			res = res + b[i]*vec[i].second;
			printf("multiplying vec[%d] = %d and b[%d] = %d\tres = %d\n", vec[i].first, vec[i].second, i, b[i], res);
		}

		cout<<res<<endl;
	}

	return 0;
}

