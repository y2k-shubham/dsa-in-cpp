/*
Input
6 9
0 1
0 2
1 2
1 3
3 1
3 2
4 0
4 2
4 5
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void input(vector <list <int> > &, vector <list <int> > &, list <int> *, int);
void init(vector <list <int> > &, int);
void output(vector <list <int> >, int);
void output(vector <list <int> >);
void output(list <int> *, int);

int main() {
	int V, E;

	cout << "Enter (V, E):\t";
	cin >> V >> E;

	vector <list <int> > vec_1 (V);
	vector <list <int> > vec_2;
	list <int> arr[V];

	init(vec_2, V);
	input(vec_1, vec_2, arr, E);

	output(vec_1, V);
	output(vec_2);
	output(arr, V);

	return 0;
}

void init(vector <list <int> > &vec, int V) {
	for (int i = 1; i <= V; i++) {
		list <int> emptyList;
		vec.push_back(emptyList);
	}
}

void input(vector <list <int> > &vec_1, vector <list <int> > &vec_2, list <int> * arr, int E) {
	printf("Enter edges as (src, dest):-\n");
	for (int i = 1; i <= E; i++) {
		int src, dest;
		cin >> src >> dest;

		vec_1[src].push_back(dest);
		vec_2[src].push_back(dest);
		arr[src].push_back(dest);
	}
}

void output(vector <list <int> > vec, int V) {
	printf("\nAdjacency list is:-\n");

	for (int i = 0; i < V; i++) {
		printf("%d\t", i);

		for (list <int>::iterator it = vec[i].begin(); it != vec[i].end(); it++) {
			printf("%d ", *it);
		}
		cout << endl;
	}
	cout << endl;
}

void output(vector <list <int> > vec) {
	printf("\nAdjacency list is:-\n");
	int vertNo = 0;

	for (vector <list <int> >::iterator i = vec.begin(); i != vec.end(); i++) {
		printf("%d\t", vertNo++);

		for (list <int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
			printf("%d ", *j);
		}
		cout << endl;
	}
	cout << endl;
}

void output(list <int> *arr, int V) {
	printf("\nAdjacency list is:-\n");

	for (int i = 0; i < V; i++) {
		printf("%d\t", i);

		for (list <int>::iterator it = arr[i].begin(); it != arr[i].end(); it++) {
			printf("%d ", *it);
		}
		cout << endl;
	}
	cout << endl;
}

