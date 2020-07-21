// https://leetcode.com/problems/combination-sum/

#include<bits/stdc++.h>
using namespace std;

void printoutput(vector<int>vec) {
	cout<<"(";
	for(int i = 0; i < vec.size(); i++) {
		cout<<vec[i];
		if(i != (vec.size() - 1)) {
			cout<<" ";
		}
	}
	cout<<")";
}

void fncutil(int a[],int ind, int n, int cursum, int sum,vector<int>vec, int *flag) {
	if(cursum > sum || ind == n)
		return;
	else if(cursum == sum) {
		printoutput(vec);
		(*flag) = 1;
		return;
	} else {
		for(int i = ind; i < n; i++) {
			vec.push_back(a[i]);
			fncutil(a,i,n,cursum+a[i],sum,vec,flag);
			vec.pop_back();
//			fncutil(a, i+1, n, cursum, sum, vec, flag);
		}
	}
}

void fnc(int a[], int n, int sum, int *flag) {
	vector<int>vec;
	fncutil(a,0,n,0,sum,vec,flag);
}

int main() {
	int t;
	cin>>t;

	while(t--) {
		int n;
		cin>>n;

		int a[n];
		for(int i = 0; i < n; i++)
			cin>>a[i];
		sort(a,a+n);

		int sum;
		cin>>sum;

		int flag = 0;
		fnc(a,n,sum,&flag);

		if(flag == 0) {
			cout<<"Empty";
		}
		cout<<endl;
	}
	return 0;
}

