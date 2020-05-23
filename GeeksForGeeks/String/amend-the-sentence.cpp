// http://www.practice.geeksforgeeks.org/problem-page.php?pid=350
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	int delta = 'a' - 'A';
	string sen;

	scanf("%d", &T);
	while (T-- > 0) {
		cin >> sen;

		printf("%c", (char) (sen[0] + delta));
		for (int i = 1; i < sen.length(); i++) {
			if (sen[i] < 'a') {
				printf(" %c", (char) (sen[i] + delta));
			} else {
				printf("%c", (char) (sen[i]));
			}
		}
		printf("\n");
	}

	return 0;
}
