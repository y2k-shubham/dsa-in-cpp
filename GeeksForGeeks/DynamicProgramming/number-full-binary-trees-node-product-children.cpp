// http://www.geeksforgeeks.org/number-full-binary-trees-node-product-children/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1565

/*
4
2 3 4 6
Ans: 7

3
1 2 4
Ans: 4

16
107 13 10 62 3 68 51 20 84 47 61 67 53 17 12 9
Ans: 19
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>

using namespace std;

void input(map <int, int>&);
void showMap(map <int, int>, const char *);
int calcCount(map <int, int>&);

int main() {
	map <int, int> noOfTrees;

	input(noOfTrees);
	showMap(noOfTrees, "before computing");

	int noOfWays = calcCount(noOfTrees);
	showMap(noOfTrees, "after computing");

	printf("\nTotal no of trees is %d\n", noOfWays);

	return 0;
}

void input(map <int, int>& noOfTrees) {
	int n;

	printf("Enter no of elements:\t");
	cin >> n;

	printf("Enter elements:-\n");
	for (int i = 1; i <= n; i++) {
		int ele;
		cin >> ele;

		noOfTrees.insert(make_pair(ele, 1));
	}
}

void showMap(map <int, int> noOfTrees, const char * when) {
	printf("\n%s, no of trees possible for various roots is:-\n", when);
	for (map <int, int>::iterator i = noOfTrees.begin(); i != noOfTrees.end(); i++) {
		printf("%d\t->\t%d\n", (*i).first, (*i).second);
	}
}

int calcCount(map <int, int>& noOfTrees) {
	int noOfWays = 0;

	for (map <int, int>::iterator i = noOfTrees.begin(); i != noOfTrees.end(); i++) {
		int crrNum = (*i).first;
//		printf("\n---------------\nCalculating tree-count for %d\n", crrNum);

		for (map <int, int>::iterator j = noOfTrees.begin(); (*j).first <= crrNum / 2; j++) {
			int crrFact = (*j).first;
			if (crrFact == 1) {
				continue;
			}

//			printf("For node %d\t", crrFact);
			if (((int) pow(crrFact, 2)) == crrNum) {
//				printf("added (c[%d] = %d) ^ 2 = %d\n", crrFact, noOfTrees[crrFact], ((int) pow(noOfTrees[crrFact], 2)));
				noOfTrees[crrNum] += (int) pow(noOfTrees[crrFact], 2);
			} else if ((crrNum % crrFact == 0) && (noOfTrees.find(crrNum / crrFact) != noOfTrees.end())) {
//				printf("added (c[%d] = %d) * (c[%d] = %d) = %d\n", crrFact, noOfTrees[crrFact], (crrNum / crrFact), noOfTrees[crrNum / crrFact], (noOfTrees[crrFact] * noOfTrees[crrNum / crrFact]));
				noOfTrees[crrNum] += noOfTrees[crrFact] * noOfTrees[crrNum / crrFact];
			} else {
//				printf("skipped\n");
			}
		}

		noOfWays += noOfTrees[crrNum];
//		showMap(noOfTrees, "\nafter update");
	}

	return noOfWays;
}

