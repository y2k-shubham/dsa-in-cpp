
/*
7 10		3 4
4
9 1		2 1		3
7 2		4 4		0
1 2		6 9		4
1 6		8 11	7

7 10		3 4
4
9 1		2 1		3
7 2		4 4		0
1 2		6 9		4
1 6		8 11	22


*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <cmath>

using namespace std;
//#define absVal(x) ((x >= 0) ? x : (-x))

void input(pair <int, int>&, pair <int, int>&, int&, map <pair <int, int>, int>&, map <int, pair <int, int> >&, map <int, list <pair <int, int> > >&, bool);
int absVal(int);
int sum(int, int);
void init(map <int, list <pair <int, int> > >&, int);
void init(map <int, pair <int, int> >&, int);
void fillList(int, map <int, pair <int, int> >, map <int, list <pair <int, int> > >&);
void showMap(map <int, pair <int, int> >, const char *);
void showMap(map <int, pair <int, int> >, map <int, pair <int, int> >, const char *);
void showGraph(map <int, list <pair <int, int> > >, map <int, pair <int, int> >, const char *);
void dfs(map <int, list <pair <int, int> > >, int, map <int, pair <int, int> >&, int, int, int);

int main() {
	pair <int, int> src, dst;
	map <pair <int, int>, int> idMap;
	map <int, pair <int, int> > revIdMap;
	map <int, list <pair <int, int> > > adjList;
	map <int, pair <int, int> > reachCost;
	int n;
	bool usePortal = true;

	input(src, dst, n, idMap, revIdMap, adjList, usePortal);
	showMap(revIdMap, "revId map");
	showGraph(adjList, revIdMap, "before filling");

	fillList(n, revIdMap, adjList);
	showGraph(adjList, revIdMap, "after filling");

	init(reachCost, n);
	reachCost[idMap[src]].first = idMap[src];
	showMap(revIdMap, reachCost, "before dfs, reachCost map");

	dfs(adjList, n, reachCost, idMap[src], idMap[src], 0);
	showMap(revIdMap, reachCost, "after dfs, reachCost map");

	return 0;
}

void input(pair <int, int>& src, pair <int, int>& dst, int& n, map <pair <int, int>, int>& idMap, map <int, pair <int, int> >& revIdMap, map <int, list <pair <int, int> > >& adjList, bool usePortal) {
	printf("Enter src coordinates:\t");
	cin >> src.first >> src.second;

	printf("Enter dst coordinates:\t");
	cin >> dst.first >> dst.second;

	printf("Enter no of portals:\t");
	cin >> n;

	init(adjList, n);
	idMap[src] = (2 * n) + 1;
	idMap[dst] = (2 * n) + 2;
	revIdMap[(2 * n) + 1] = src;
	revIdMap[(2 * n) + 2] = dst;
	adjList[(2 * n) + 1].push_back(make_pair((2 * n) + 2, absVal(src.first - dst.first) + absVal(src.second - dst.second)));
	adjList[(2 * n) + 2].push_back(make_pair((2 * n) + 1, absVal(src.first - dst.first) + absVal(src.second - dst.second)));

	printf("Enter portal data:-\n");
	for (int i = 1; i <= (2 * n); i += 2) {
		pair <int, int> p1, p2;
		int cost;

		cin >> p1.first >> p1.second;
		cin >> p2.first >> p2.second;
		cin >> cost;

		int id1 = i;
		int id2 = i + 1;

		idMap.insert(make_pair(p1, id1));
		idMap.insert(make_pair(p2, id2));
		revIdMap.insert(make_pair(id1, p1));
		revIdMap.insert(make_pair(id2, p2));

		if (usePortal == false) {
			cost = min(cost, absVal(p1.first - p2.first) + absVal(p1.second - p2.second));
		}
		adjList[id1].push_back(make_pair(id2, cost));
		adjList[id2].push_back(make_pair(id1, cost));
	}
}

int absVal(int x) {
	if (x >= 0) {
		return x;
	} else {
		return ((-1) * x);
	}
}

int sum(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return (a + b);
	}
}

void init(map <int, list <pair <int, int> > >& adjList, int n) {
	for (int i = 1; i <= ((2 * n) + 2); i++) {
		list <pair <int, int> > empList;
		adjList[i] = empList;
	}
}

void init(map <int, pair <int, int> >& reachCost, int n) {
	for (int i = 1; i <= ((2 * n) + 2); i++) {
		reachCost[i] = make_pair(-1, INT_MAX);
	}
}

void fillList(int n, map <int, pair <int, int> > revIdMap, map <int, list <pair <int, int> > >& adjList) {
	for (int i1 = 1; i1 <= (2 * n); i1++) {
		pair <int, int> p1 = revIdMap[i1];

		int i2 = ((i1 % 2) == 0) ? (i1 + 1) : (i1 + 2);
		for (; i2 <= ((2 * n) + 2); i2++) {
			pair <int, int> p2 = revIdMap[i2];

			adjList[i1].push_back(make_pair(i2, absVal(p1.first - p2.first) + absVal(p1.second - p2.second)));
			adjList[i2].push_back(make_pair(i1, absVal(p1.first - p2.first) + absVal(p1.second - p2.second)));
		}
	}
}

void showMap(map <int, pair <int, int> > idMap, const char * msg) {
	printf("\n%s is:-\n", msg);
	for (map <int, pair <int, int>>::iterator i = idMap.begin(); i != idMap.end(); i++) {
		pair <int, int> p = i -> second;
		if (p.second == INT_MAX) {
			printf("%d\t->\t(%d, _)\n", i -> first, p.first);
		} else {
			printf("%d\t->\t(%d, %d)\n", i -> first, p.first, p.second);
		}
	}
}

void showMap(map <int, pair <int, int> > revIdMap, map <int, pair <int, int> > reachCost, const char * msg) {
	printf("\n%s is:-\n", msg);
	for (map <int, pair <int, int> >::iterator i = reachCost.begin(); i != reachCost.end(); i++) {
		pair <int, int> p1 = revIdMap[i -> first];
		pair <int, int> p2 = revIdMap[(i -> second).first];
		int cost = (i -> second).second;

		if (cost == INT_MAX) {
			printf("%d = (%d, %d)\t\t->\t\t[%d,\t_]\n", i -> first, p1.first, p1.second, (i -> second).first);
		} else {
			printf("%d = (%d, %d)\t\t->\t\t[%d = (%d, %d),\t%d (%d)]\n", i -> first, p1.first, p1.second, (i -> second).first, p2.first, p2.second, cost, cost - reachCost[(i -> second).first].second);
		}
	}
}

void showGraph(map <int, list <pair <int, int> > > adjList, map <int, pair <int, int> > revIdMap, const char * when) {
	pair <int, int> v;

	printf("\n%s adjList is:-\n", when);
	for (map <int, list <pair <int, int> > >::iterator i = adjList.begin(); i != adjList.end(); i++) {
		list <pair <int, int> > tmpList = i -> second;
		v = revIdMap[i -> first];

		printf("%d = (%d, %d)\t->\t", i -> first, v.first, v.second);
		for (list <pair <int, int> >::iterator j = tmpList.begin(); j != tmpList.end(); j++) {
			//v = revIdMap[j -> first];
			//printf("[(%d, %d), %d]\t", v.first, v.second, j -> second);
			printf("[%d, %d]\t", j -> first, j -> second);
		}
		cout << endl;
	}
}

void dfs(map <int, list <pair <int, int> > > adjList, int n, map <int, pair <int, int> >& reachCost, int crrVert, int crrPar, int crrCost) {
	if (reachCost[crrVert].second > crrCost) {
		reachCost[crrVert] = make_pair(crrPar, crrCost);

		list <pair <int, int> > tmpList = adjList[crrVert];
		for (list <pair <int, int> >::iterator i = tmpList.begin(); i != tmpList.end(); i++) {
			dfs(adjList, n, reachCost, i -> first, crrVert, sum(crrCost, i -> second));
		}
	}
}

