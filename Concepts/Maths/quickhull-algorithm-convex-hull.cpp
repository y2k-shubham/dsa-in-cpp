// http://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/

/*
8
0 3		1 1		2 2		4 4
0 0		1 2		3 1 	3 3

6
0 0		0 4		-4 0
5 0		0 -6	1 0
*/

#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <cmath>
#include <limits>
#include <cstdlib>

using namespace std;

void input(vector <pair <float, float> >&);
void showList(vector <pair <float, float> >);
void showSet(set <pair <float, float> >, const char *);
float pointDist(pair <float, float>, pair <float, float>);
float lineDist(pair <float, float>, pair <float, float>, pair <float, float>);
int getSide(pair <float, float>, pair <float, float>, pair <float, float>);
void findHull(set <pair <float, float> >, pair <float, float>, pair <float, float>, int, set <pair <float, float> >&);
pair <float, float> getLeftMostPoint(vector <pair <float, float> >);
pair <float, float> getRightMostPoint(vector <pair <float, float> >);
set <pair <float, float> > getPointSet(vector <pair <float, float> >, pair <float, float>, pair <float, float>, int);

int main() {
	vector <pair <float, float> > pList;
	set <pair <float, float> > cHull;

	input(pList);
	showList(pList);

	pair <float, float> pLeftMost = getLeftMostPoint(pList);
	pair <float, float> pRightMost = getRightMostPoint(pList);

	findHull(getPointSet(pList, pLeftMost, pRightMost, 1), pLeftMost, pRightMost, 1, cHull);
	findHull(getPointSet(pList, pLeftMost, pRightMost, -1), pLeftMost, pRightMost, -1, cHull);

	showSet(cHull, "cHull");

	return 0;
}

void input(vector <pair <float, float> >& pList) {
	int n;

	printf("Enter number of points:\t");
	scanf("%d", &n);

	if (n < 3) {
		printf("\nConvex Hull contains at least 3 points\n");
		exit(1);
	}

	printf("Enter coordinates of %d points:-\n", n);
	for (int i = 0; i < n; i++) {
		float x, y;
		scanf("%f%f", &x, &y);
		pList.push_back(make_pair(x, y));
	}
}

void showList(vector <pair <float, float> > pList) {
	printf("\nList of points is:-\n");
	for (int i = 0; i < pList.size(); i++) {
		printf("pList[%d]\t=\t(%3.1f,%3.1f)\n", i, pList[i].first, pList[i].second);
	}
}

void showSet(set <pair <float, float> > pSet, const char * name) {
	printf("\n%s set is:-\n", name);
	for (set <pair <float, float> >::iterator i = pSet.begin(); i != pSet.end(); i++) {
		printf("(%3.1f, %3.1f)\n", i -> first, i -> second);
	}
	cout << endl;
}

float pointDist(pair <float, float> p1, pair <float, float> p2) {
	return sqrtf(powf(p1.first - p2.first, 2.0f) + powf(p1.second - p2.second, 2.0f));
}

float lineDist(pair <float, float> p1, pair <float, float> p2, pair <float, float> p) {
	float nr = ((p2.second - p1.second) * p.first) - ((p2.first - p1.first) * p.second) + (p2.first * p1.second) - (p2.second * p1.first);
	float dr = sqrtf(powf(p1.first - p2.first, 2.0f) + powf(p1.second - p2.second, 2.0f));
	return abs(nr / dr);
}

int getSide(pair <float, float> p1, pair <float, float> p2, pair <float, float> p) {
	float nr = ((p2.second - p1.second) * p.first) - ((p2.first - p1.first) * p.second) + (p2.first * p1.second) - (p2.second * p1.first);
	if (nr > 0) {
		return 1;
	} else if (nr < 0) {
		return -1;
	} else {
		return 0;
	}
}

void findHull(set <pair <float, float> > cSet, pair <float, float> p1, pair <float, float> p2, int side, set <pair <float, float> >& cHull) {
	set <pair <float, float> > nSet;
	pair <float, float> mDistPoint;
	float mDist = -1.0f;

	// find farthest Point farthest to line p1-p2 which lies on 'side' side of the line
	for (set <pair <float, float> >::iterator i = cSet.begin(); i != cSet.end(); i++) {
		pair <float, float> p = *i;

		if (getSide(p1, p2, p) == side) {
			nSet.insert(p);
			float cDist = lineDist(p1, p2, p);

			if (cDist > mDist) {
				mDist = cDist;
				mDistPoint = p;
			}
		}
	}

	// if there were no points lying on 'side' side of line p1-p2, then add them to convex hull
	if (mDist < 0) {
		cHull.insert(p1);
		cHull.insert(p2);
	} else {
		findHull(nSet, p1, mDistPoint, -getSide(p1, mDistPoint, p2), cHull);
		findHull(nSet, p2, mDistPoint, -getSide(p2, mDistPoint, p1), cHull);
	}
}

pair <float, float> getLeftMostPoint(vector <pair <float, float> > pList) {
	pair <float, float> p;
	float mX = numeric_limits <float>::max();

	for (int i = 0; i < pList.size(); i++) {
		if (pList[i].first < mX) {
			mX = pList[i].first;
			p = pList[i];
		}
	}

	return p;
}

pair <float, float> getRightMostPoint(vector <pair <float, float> > pList) {
	pair <float, float> p;
	float mX = numeric_limits <float>::min();

	for (int i = 0; i < pList.size(); i++) {
		if (pList[i].first > mX) {
			mX = pList[i].first;
			p = pList[i];
		}
	}

	return p;
}

set <pair <float, float> > getPointSet(vector <pair <float, float> > pList, pair <float, float> p1, pair <float, float> p2, int side) {
	set <pair <float, float> > pSet;

	for (int i = 0; i < pList.size(); i++) {
		if (getSide(p1, p2, pList[i]) == side) {
			pSet.insert(pList[i]);
		}
	}

	return pSet;
}

