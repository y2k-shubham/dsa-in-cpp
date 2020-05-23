// TERNARY SEARCH (divide-and-conquer) + basic geometry
// http://www.geeksforgeeks.org/optimum-location-point-minimize-total-distance/
// Ternary Search: https://en.wikipedia.org/wiki/Ternary_search
// Note: This program works only when given line is NOT parallel to y-axis (it should have some x-expanse)
// Reflection of a point across a line: http://stackoverflow.com/questions/3306838/algorithm-for-reflecting-a-point-across-a-line
// After finding reflection across the line, use mid-point formula to obtain foot of perpendicular from point of line

/*
1 -1 -3
5
-3 -2		-1 0		-1 2		1 2			3 4

1 -2 -1
3
2 2		4 1		7 5
*/

#include <cstdio>
#include <iostream>
#include <utility>
#include <list>
#include <cmath>

struct line {
	float a;
	float b;
	float c;
};

using namespace std;

// input and initialization
void input(line &, list <pair <float, float> > &);
void findXRange(line, list <pair <float, float> >, float &, float &);
// output
void showPoints(list <pair <float, float> >);
void showLine(line);
void showXRange(float, float);
// calculation
float sumOfDist(list <pair <float, float> >, float, float);
void ternarySearch(list <pair <float, float> >, line, float, float);

int main() {
	list <pair <float, float> > points;
	line l;
	float xLo, xHi;

	input(l, points);
	showPoints(points);
	showLine(l);

	findXRange(l, points, xLo, xHi);
	showXRange(xLo, xHi);

	ternarySearch(points, l, xLo, xHi);

	return 0;
}

// input and initialization
void input(line &l, list <pair <float, float> > &points) {
	int n;

	printf("Enter a, b, c for line:\t");
	cin >> l.a;
	cin >> l.b;
	cin >> l.c;

	cout << "Enter no of points:\t";
	cin >> n;

	printf("Enter coordinates of points:-\n");
	for (int i = 1; i <= n; i++) {
		float x, y;

		cin >> x >> y;
		points.push_back(make_pair(x, y));
	}
}

void findXRange(line l, list <pair <float, float> > points, float &xLo, float &xHi) {
	xLo = 99999.0f;
	xHi = -99999.0f;

	float m = -(l.a / l.b);
	float c = -(l.c / l.b);
	for (list <pair <float, float> >::iterator i = points.begin(); i != points.end(); i++) {
		float xO = (*i).first;
		float yO = (*i).second;

		float d = (xO + (yO - c) * m) / (1 + powf(m, 2.0));

		float xR = (2 * d) - xO;
		float yR = (2 * m * d) - yO + (2 * c);

		float xM = (xO + xR) / 2;
		float yM = (yO + yR) / 2;

		xLo = min(xLo, xM);
		xHi = max(xHi, xM);

//		printf("\n(xO, yO) = (%f, %f)\n", xO, yO);
//		printf("d = %f\n", d);
//		printf("(xR, yR) = (%f, %f)\n", xR, yR);
//		printf("(xM, yM) = (%f, %f)\n", xM, yM);
	}
}

// output
void showLine(line l) {
	printf("\nParameters of line are:-\n");
	printf("a = %f\t\tb = %f\t\tc = %f\n", l.a, l.b, l.c);

	float m = -(l.a / l.b);
	float c = -(l.c / l.b);
	printf("m = %f\t\tc = %f\n\n", m, c);
}

void showPoints(list <pair <float, float> > points) {
	printf("\nList of points is:-\n");
	for (list <pair <float, float> >::iterator i = points.begin(); i != points.end(); i++) {
		printf("(%f, %f)\n", (*i).first, (*i).second);
	}
	cout << endl;
}

void showXRange(float xLo, float xHi) {
	printf("\nX-Range is:-\n");
	printf("xLo = %f\n", xLo);
	printf("xHi = %f\n\n", xHi);
}

float sumOfDist(list <pair <float, float> > points, float x1, float y1) {
	float sum = 0.0f;

	for (list <pair <float, float> >::iterator i = points.begin(); i != points.end(); i++) {
		float x2 = (*i).first;
		float y2 = (*i).second;

		sum += sqrtf(powf((x1 - x2), 2.0f) + powf((y1 - y2), 2.0f));
	}

	return sum;
}

// calculation
void ternarySearch(list <pair <float, float> > points, line l, float xLo, float xHi) {
	float threshDelta = 0.01f;

	while (abs(xHi - xLo) > threshDelta) {
		float delta = xHi - xLo;

		float xM1 = xLo + (delta / 3);
		float yM1 = ((l.a * xM1) + l.c) / (-l.b);

		float xM2 = xHi - (delta / 3);
		float yM2 = ((l.a * xM2) + l.c) / (-l.b);

		float s1 = sumOfDist(points, xM1, yM1);
		float s2 = sumOfDist(points, xM2, yM2);

		if (s1 < s2) {
			xHi = xM2;
		} else if (s1 > s2) {
			xLo = xM1;
		} else {
			xLo = xM1;
			xHi = xM2;
		}
	}

	float xReq = (xLo + xHi) / 2;
	float yReq = ((l.a * xReq) + l.c) / (-l.b);

	printf("\nRequired point is (%f, %f) with sum-of-distances %f\n", xReq, yReq, sumOfDist(points, xReq, yReq));
}

