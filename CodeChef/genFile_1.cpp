#include <cstdio>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
	int ctr = 15000;
	int max_len = 20;
	int alpha_size = 26;

	srand(time(NULL));

	string str;
	str.reserve(max_len + 5);

	cout << ctr << endl;
	for (int i = 1; i <= ctr; i++) {
		int len = 0;
		while (len == 0) {
			len = rand() % 20;
		}

		printf("%c ", ((rand() % 2 < 0) ? '+' : '-'));

		for (int j = 0; j < len; j++) {
			char c = (char) ('a' + (rand() % alpha_size));
			printf("%c", c);
		}
		printf("\n");
	}

	return 0;
}

