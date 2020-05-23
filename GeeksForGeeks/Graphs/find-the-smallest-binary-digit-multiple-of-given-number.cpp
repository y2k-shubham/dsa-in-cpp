// http://www.geeksforgeeks.org/find-the-smallest-binary-digit-multiple-of-given-number/

#include <cstdio>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

void findBinDigMult_1(int);
void findBinDigMult_2(int);
int convert(int);

int main() {
	int n;

	cout << "Enter n:\t";
	cin >> n;

	findBinDigMult_1(n);
	findBinDigMult_2(n);

	return 0;
}

void findBinDigMult_1(int n) {
	queue <int> que;

	if (n > 0) {
		que.push(1);

		while (true) {

			int tmp = que.front();
			que.pop();

			int init = (int) ceil(log2(tmp));
			int rem = 0;

//			printf("\n===========\npopped %d from que\n", tmp);
			for (int i = init; i >= 0; i--) {
				int div;

				if ((tmp & (1 << i)) == 0) {
					div = rem * 10;
//					printf("for tmp = %d\tat posn %d\tfound 0 (%d)\tso div = rem * 10 = %d\n", tmp, i, (tmp & (1 << i)), div);
				} else {
					div = (rem * 10) + 1;
//					printf("for tmp = %d\tat posn %d\tfound 1 (%d)\tso div = rem * 10 + 1= %d\n", tmp, i, (tmp & (1 << i)), div);
				}

				rem = div % n;
//				printf("div = %d\trem = %d\n\n", div, rem);
			}
//			cout << endl;

			if (rem == 0) {
				printf("smallest binary digit multiple of %d is %d\n", n, convert(tmp));
				break;
			} else {
				que.push(tmp << 1);
				que.push((tmp << 1) | 1);
			}
		}
	}
}

void findBinDigMult_2(int n) {
	if (n > 0) {
		for (int mult = 1; mult < INT_MAX; mult++) {
			int init = (int) ceil(log2(mult));
			int rem = 0;

			for (int i = init; i >= 0; i--) {
				int div;

				if ((mult & (1 << i)) == 0) {
					div = rem * 10;
				} else {
					div = (rem * 10) + 1;
				}

				rem = div % n;
			}

			if (rem == 0) {
				printf("smallest binary digit multiple of %d is %d\n", n, convert(mult));
				break;
			}
		}
	} else {
		printf("smallest binary digit multiplier of 0 is 0\n");
	}
}

int convert(int bin) {
	int init = (int) ceil(log2(bin));
	int dec = 0;

	for (int i = init; i >= 0; i--) {
		dec *= 10;
		if ((bin & (1 << i)) != 0) {
			dec += 1;
		}
	}

	return dec;
}

