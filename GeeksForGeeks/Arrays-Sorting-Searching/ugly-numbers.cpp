// http://www.practice.geeksforgeeks.org/problem-page.php?pid=553
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int main() {
	int T;

	scanf("%d", &T);

	while (T-- > 0) {
		int N;
		int ele;
		queue <int> mult_2;
		queue <int> mult_3;
		queue <int> mult_5;

		scanf("%d", &N);

		if (N == 1) {
			printf("1\n");
			continue;
		}

		mult_2.push(2);
		mult_3.push(3);
		mult_5.push(5);

		for (int k = 2; k <= N; k++) {
			if (mult_2.front() < mult_3.front() && mult_2.front() < mult_5.front()) {
				ele = mult_2.front();
				mult_2.pop();
				mult_2.push(ele * 2);
				mult_3.push(ele * 3);
				mult_5.push(ele * 5);
			} else if (mult_3.front() < mult_2.front() && mult_3.front() < mult_5.front()) {
				ele = mult_3.front();
				mult_3.pop();
				mult_3.push(ele * 3);
				mult_5.push(ele * 5);
			} else {
				ele = mult_5.front();
				mult_5.pop();
				mult_5.push(ele * 5);
			}
//			printf("iter = %d\tpopped = %d\n", k, ele);
		}

		printf("%d\n", ele);
	}

	return 0;
}
