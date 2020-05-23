// http://www.geeksforgeeks.org/find-excel-column-name-given-number/
// http://www.practice.geeksforgeeks.org/editorial.php?pid=430
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=430

#include <cstdio>
#include <iostream>

using namespace std;
#define LEN 27
#define MAX 26

void createCharMap(char [LEN]);

int main() {
	char alphaMap[LEN];
	int T;

	createCharMap(alphaMap);
	cin >> T;

	while (T-- > 0) {
		long long int N;
		string colName;

		scanf("%lld", &N);
		while (N > 0) {
			int rem = N % MAX;
			N /= MAX;
			if (rem == 0) {
				N--;
			}

			colName = alphaMap[rem] + colName;
		}
		cout << colName << endl;
	}

	return 0;
}

void createCharMap(char alphaMap[LEN]) {
	char c = 'A';
	for (int i = 1; i < LEN; i++) {
		alphaMap[i] = c++;
	}
	alphaMap[0] = 'Z';
}

