// TusharRoy: https://www.youtube.com/watch?v=-JjA4BLQyqE
// Saurabh School: https://www.youtube.com/watch?v=aQB_Y9D5pdw&t=1072s
// Happy Learning: https://www.youtube.com/watch?v=vNqE_LDTsa0

/*
TusharRoy's example
4
0 1 15 6
2 0 7 3
9 6 0 12
10 4 8 0

Saurabh School's example
4
0 10 15 20
5 0 9 10
6 13 0 12
8 8 9 0

Happy Learning's example
5
0 7 6 8 4
7 0 8 5 6
6 8 0 9 7
8 5 9 0 8
4 6 7 8 0

*/

// basic I/O
#include <cstdio>
#include <iostream>
// mathematical operations
#include <climits>
#include <cmath>
// STL utilities
#include <functional>
#include <utility>
#include <algorithm>
// STL containers
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <stack>

using namespace std;

// input
void inputTerm(vector <vector <int> > &, int &);
void inputFile(vector <vector <int> > &, int &, const char *);
// output
void showAdj(vector <vector <int> >, int);
void showSet(set <int>);
void showQue(priority_queue <pair <int, set <int> > >);
void showMap(map <pair <int, set <int> >, pair <int, int> >);
void showAns(vector <vector <int> >, map <pair <int, set <int> >, pair <int, int> >);
// subset generation
set <int> genSet(int, int);
priority_queue <pair <int, set <int> > > genQue(int);
// computation
void fillMap(vector <vector <int> >, int, priority_queue <pair <int, set <int> > >, map <pair <int, set <int> >, pair <int, int> > &);
void findAns(vector <vector <int> >, int, map <pair <int, set <int> >, pair <int, int> > &);

int main() {
	vector <vector <int> > adj;
	int V;
	priority_queue <pair <int, set <int> > > que;
	map <pair <int, set <int> >, pair <int, int> > pLen;

	// Console input
//	inputTerm(adj, V);
//	showAdj(adj, V);

	// File input
	inputFile(adj, V, "tsp_3");
	showAdj(adj, V);

	// generate priority que of subsets
	que = genQue(V);
	showQue(que);

	// compute the answer
	fillMap(adj, V, que, pLen);
	findAns(adj, V, pLen);

	// show calculated map and final solution
	showMap(pLen);
	showAns(adj, pLen);

	return 0;
}

// input
void inputTerm(vector <vector <int> > &adj, int &V) {
	cout << "Enter no of vertices:\t";
	cin >> V;

	cout << "Enter adjacency matrix:-\n";
	for (int i = 0; i < V; i++) {
		vector <int> vec(V);

		for (int j = 0; j < V; j++) {
			int wgt;
			cin >> wgt;

			vec[j] = wgt;
		}

		adj.push_back(vec);
	}
}

void inputFile(vector <vector <int> > &adj, int &V, const char * fileName) {
	FILE * f = fopen(fileName, "r");

	cout << "Enter no of vertices:\t";
	fscanf(f, "%d", &V);
	printf("%d\n", V);

	cout << "Enter adjacency matrix:-\n";
	for (int i = 0; i < V; i++) {
		vector <int> vec(V);

		for (int j = 0; j < V; j++) {
			int wgt;
			fscanf(f, "%d", &wgt);
			printf("%d\t", wgt);

			vec[j] = wgt;
		}
		cout << endl;

		adj.push_back(vec);
	}

	fclose(f);
}

// output
void showAdj(vector <vector <int> > adj, int V) {
	printf("\nAdjacency Matrix is:-\n");

	cout << "\t";
	for (int j = 0; j < V; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < V; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < V; j++) {
			cout << adj[i][j] << "\t";
		}
		cout << endl;
	}
}

void showSet(set <int> vSet) {
	if (vSet.size() > 0) {
		set <int>::iterator i = vSet.begin();
		printf("{%d", *i);

		for (i++; i != vSet.end(); i++) {
			printf(", %d", *i);
		}
		cout << "}";
	} else {
		printf("{}");
	}
}

void showQue(priority_queue <pair <int, set <int> > > que) {
	printf("\nPriority Que is:-\n");
	while (!que.empty()) {
		showSet((que.top()).second);
		que.pop();

		cout << endl;
	}
}

void showMap(map <pair <int, set <int> >, pair <int, int> > pLen) {
	printf("\nThe map is:-\n");
	for (map <pair <int, set <int> >, pair <int, int> >::iterator i = pLen.begin(); i != pLen.end(); i++) {
		int v = ((*i).first).first;
		set <int> vSet = ((*i).first).second;
		int crrPLen = ((*i).second).first;
		int crrPLenV = ((*i).second).second;

		printf("(%d, ", v);
		showSet(vSet);
		printf(")\t->\t(%d, %d)\n", crrPLen, crrPLenV);
	}
}

void showAns(vector <vector <int> > adj, map <pair <int, set <int> >, pair <int, int> > pLen) {
	set <int> vSet1, vSet2;
	stack <pair <int, int> > stk;
	int par, newPar;

	int V = adj.size();
	for (int i = 1; i < V; i++) {
		vSet1.insert(i);
		vSet2.insert(i);
	}

	par = pLen[make_pair(0, vSet1)].second;
	vSet1.erase(par);
	stk.push(make_pair(0, adj[par][0]));

	while (vSet1.empty() == false) {
		newPar = pLen[make_pair(par, vSet1)].second;
		vSet1.erase(newPar);
		stk.push(make_pair(par, adj[newPar][par]));

		par = newPar;
	}
	newPar = pLen[make_pair(par, vSet1)].second;
	stk.push(make_pair(par, adj[newPar][par]));

	printf("\nLength of shortest hamiltonian cycle is %d\n", pLen[make_pair(0, vSet2)].first);
	printf("Shortest hamiltonian cycle is:-\n");

	printf("0  ");
	while (!stk.empty()) {
		printf("  ->  %d (%d)", (stk.top()).first, (stk.top()).second);
		stk.pop();
	}
	cout << endl;
}

// subset generation
set <int> genSet(int V, int mask) {
	set <int> vSet;
	int lim = (int) powf(2, ceil(log2(mask)));

	for (int i = 0; i <= mask; i++) {
		if ((mask & (1 << i)) != 0) {
			vSet.insert(i + 1);
		}
	}

	return vSet;
}

priority_queue <pair <int, set <int> > > genQue(int V) {
	priority_queue <pair <int, set <int> > > que;
	int lim = ((int) powf(2, V - 1)) - 1;

	for (int i = 0; i <= lim; i++) {
		set <int> vSet = genSet(V, i);
		que.push(make_pair(-vSet.size(), vSet));
	}

	return que;
}

// computation
void fillMap(vector <vector <int> > adj, int V, priority_queue <pair <int, set <int> > > que, map <pair <int, set <int> >, pair <int, int> > &pLen) {
	while (!que.empty()) {
		set <int> vSet = (que.top()).second;
		que.pop();

		//		printf("\n===================\n");
//		printf("got set ");
//		showSet(vSet);
//		printf(" from que\n\n");

		for (int i = 1; i < V; i++) {
			if (vSet.empty() == true) {
//				printf("inserting (%d, {}) = (%d, %d) in map\n", i, adj[0][i], 0);
				pLen.insert(make_pair(make_pair(i, vSet), make_pair(adj[0][i], 0)));
			} else if (vSet.find(i) == vSet.end()) {
				if (vSet.size() == 1) {
					set <int> empSet;
					int v = *(vSet.begin());

					pLen.insert(make_pair(make_pair(i, vSet), make_pair(adj[v][i] + pLen[make_pair(v, empSet)].first, v)));

//					printf("inserting pLen[%d, ", i);
//					showSet(vSet);
//					printf("] = (%d, %d)\n", pLen[make_pair(i, vSet)].first, pLen[make_pair(i, vSet)].second);
				} else {
					int crrPLen, minPLen, minPLenV;
					set <int> tmpSet;

					minPLen = INT_MAX;
					for (set <int>::iterator j = vSet.begin(); j != vSet.end(); j++) {
						tmpSet.insert(vSet.begin(), vSet.end());
						tmpSet.erase(*j);

//						printf("tmpSet = ");
//						showSet(tmpSet);
//						printf("\tpLen[%d, ", *j);
//						showSet(tmpSet);
//						printf("] = (%d, %d)\t", pLen[make_pair(*j, tmpSet)].first, pLen[make_pair(*j, tmpSet)].second);
//						printf("adj[%d][%d] = %d\tcrrPLen = %d", *j, i, adj[*j][i], pLen[make_pair(*j, tmpSet)].first + adj[*j][i]);

						if ((crrPLen = pLen[make_pair(*j, tmpSet)].first + adj[*j][i]) < minPLen) {
//							printf(" updated\n");
							minPLen = crrPLen;
							minPLenV = *j;
						} else {
//							printf(" unchanged\n");
						}
					}

//					printf("inserting pLen[%d, ", i);
//					showSet(vSet);
//					printf("] = (%d, %d)\n\n", minPLen, minPLenV);

					pLen.insert(make_pair(make_pair(i, vSet), make_pair(minPLen, minPLenV)));
				}
			}
		}
	}
}

void findAns(vector <vector <int> > adj, int V, map <pair <int, set <int> >, pair <int, int> > &pLen) {
	set <int> vSet, tmpSet;
	int crrPLen, minPLen, minPLenV;

	for (int i = 1; i < V; i++) {
		vSet.insert(i);
	}

	minPLen = INT_MAX;
	for (set <int>::iterator j = vSet.begin(); j != vSet.end(); j++) {
		tmpSet.insert(vSet.begin(), vSet.end());
		tmpSet.erase(*j);

//						printf("tmpSet = ");
//						showSet(tmpSet);
//						printf("\tpLen[%d, ", *j);
//						showSet(tmpSet);
//						printf("] = (%d, %d)\t", pLen[make_pair(*j, tmpSet)].first, pLen[make_pair(*j, tmpSet)].second);
//						printf("adj[%d][%d] = %d\tcrrPLen = %d", *j, i, adj[*j][i], pLen[make_pair(*j, tmpSet)].first + adj[*j][i]);

		if ((crrPLen = pLen[make_pair(*j, tmpSet)].first + adj[*j][0]) < minPLen) {
//							printf(" updated\n");
			minPLen = crrPLen;
			minPLenV = *j;
		} else {
//							printf(" unchanged\n");
		}
	}

//					printf("inserting pLen[%d, ", i);
//					showSet(vSet);
//					printf("] = (%d, %d)\n\n", minPLen, minPLenV);

	pLen.insert(make_pair(make_pair(0, vSet), make_pair(minPLen, minPLenV)));
}

