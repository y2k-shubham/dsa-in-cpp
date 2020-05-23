/*
ZenDrive question

Given n items (products or categories) in an e-commerce company in a certain hierarchy and
q queries of updating discount of an item (product or category) and telling discount of an item,
write a program to do this

each item (product or category) is denoted by an ID ranging from 1 .. n but ID's are not in
any specific order
*/

/*
18
1 2		1 3		1 4		1 5
2 6		2 7
3 8		3 9
4 10
5 11	5 12
6 13
7 14	7 15	7 16
11 17
12 18

5
Q 13
Q 17
U 2 20
Q 15
Q 18
*/

#include <bits/stdc++.h>

using namespace std;

void input(map <int, pair <int, int> >& tree, int& root) {
	int n;
	cin >> n;

	bool isChild[n + 1];
	memset(isChild, false, (n + 1) * sizeof(bool));

	for (int i = 1; i < n; i++) {
		int parent, child;
		cin >> parent >> child;

		tree[child] = make_pair(parent, 0);
		isChild[child] = true;
	}

	for (int i = 1; i <= n; i++) {
		if (isChild[i] == false) {
			root = i;
			break;
		}
	}
}

void output(map <int, pair <int, int> > tree, int root) {
	int q;
	int id, qType;

	cin >> q;
	for (int i = 1; i <= q; i++) {
		getc(stdin);

		qType = getc(stdin);
		cin >> id;

		if (qType == 'U') {
			int disc;
			cin >> disc;

			tree[id].second = disc;
		} else {
			int sum = 0;
			int crrNode = id;

			while (crrNode != root) {
				sum += tree[crrNode].second;
				crrNode = tree[crrNode].first;
			}
			sum += tree[root].second;

			cout << sum << endl;
		}
	}
}

int main() {
	map <int, pair <int, int> > tree;
	int root;

	input(tree, root);
	output(tree, root);

	return 0;
}

