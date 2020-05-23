
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	int n;
	char c;
	int i;

	cin >> n;
	while (n--) {
		cin >> c >> i;
		printf("Entered c = %c\ti = %d\n", c, i);
	}

	return 0;
}

