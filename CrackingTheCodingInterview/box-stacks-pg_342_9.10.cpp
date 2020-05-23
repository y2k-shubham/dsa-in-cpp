#include <cstdio>
#include <iostream>
#include <stack>
#include <map>
#include <vector>

using namespace std;
#define MAX 100

int main() {
	map <int, vector <int> > intToDim;
	map <int, stack <int> > intToStack;
	stack <int> maxStack;
	bool included;
	int maxStackHeight;
	int n;

	printf("Enter no of boxes:\t");
	scanf("%d", &n);
	maxStackHeight = 0;

	input(n, intToDim);

	memset(included, false, sizeof(included));
	included[0] = true;
	for (int i = 0; i < n; i++) {
		maxStackHeight = findStack(n, intToDim, intToStack, i, included, maxStack);
	}

	return 0;
}

int findStack(int n, map <int, vector <int> > intToDim, map <int, stack <int> >& intToStack, int bottom, bool included[MAX], stack <int>& maxStack) {

}
