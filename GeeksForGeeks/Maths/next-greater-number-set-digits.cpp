// http://www.practice.geeksforgeeks.org/problem-page.php?pid=384
// http://www.geeksforgeeks.org/find-next-greater-number-set-digits/

/* Problem: Given a number n, find that number just bigger than n which contains the same
			digits as n
*/

#include <cstdio>
#include <iostream>
#include <list>

using namespace std;

int findNum(int);
void showList(list <int>);

int main() {
	int T;
	int n;
	int nxtGrtSamDig;

	scanf("%d", &T);

	while (T-- > 0) {
		//printf("Enter the integer:\t\t\t");
		scanf("%d", &n);

		nxtGrtSamDig = findNum(n);
		//printf("The required integer is:\t%d\n", nxtGrtSamDig);

		if (nxtGrtSamDig != n) {
			printf("%d\n", nxtGrtSamDig);
		} else {
			printf("not possible\n");
		}
	}

	return 0;
}

int findNum(int n) {
	int digCrr, digPrev, nCopy;
	list <int> digList;
	bool broken;

	digPrev = 0;
	nCopy = n;
	broken = false;

	while (n > 0) {
		//printf("removed %d from %d\n", n % 10, n);
		digCrr = n % 10;
		n /= 10;

		if (digCrr >= digPrev) {
			digList.push_back(digCrr);
			//showList(digList);
			digPrev = digCrr;
		} else {
			broken = true;
			break;
		}
	}

	if (!broken) {
		return nCopy;
	} else {
		// declare iterator to list
		list <int>::iterator it;

		// sort extracted digits in ascending order
		// this is NOT required actually because the digList will already be sorted initially
		digList.sort();
		//printf("\nAfter sorting");
		//showList(digList);

		// find first (smallest) non-zero digit in list
		for (it = digList.begin(); it != digList.end(); it++) {
			if (*it != 0 && *it > digCrr) {
				break;
			}
		}

		if (it != digList.end()) {
			//printf("\nfound %d as smallest non-zero digit in list\n", *it);
			//printf("appended %d in %d to make %d\n", *it, n, n * 10 + *it);
			// append first non-zero digit found above to n
			n = n * 10 + *it;

			// replace first non-zero digit above with last found digit
			digList.insert(it, digCrr);

			//printf("\nAfter inserting %d", digCrr);
			//showList(digList);

			digList.erase(it);

			//printf("After removing %d", *it);
			//showList(digList);

			// sort the list of digits again
			digList.sort();

			//printf("\nAfter sorting");
			//showList(digList);

			// now append all remaining digits in list to n
			while (digList.size() > 0) {
				n = n * 10 + digList.front();
				digList.pop_front();
			}

			return n;
		} else {
			return nCopy;
		}
	}
}

void showList(list <int> digList) {
	printf("\nThe digList is:-\n");
	for (list <int>::iterator it = digList.begin(); it != digList.end(); it++) {
		printf("%d\t", *it);
	}
	printf("\n");
}

