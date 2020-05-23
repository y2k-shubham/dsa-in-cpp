// http://www.geeksforgeeks.org/find-first-natural-number-whose-factorial-divisible-x/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1601

#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;

void findPrimeFactors(int, map <int, int>&);
int findAns(int, map <int, int>);
int findMinNum(int, int);
void showMap(int, map <int, int>);

int main() {
	int n;
	map <int, int> fact;

	cout << "Enter the number:\t";
	cin >> n;

	findPrimeFactors(n, fact);
	showMap(n, fact);

	printf("Smallest number who's factorial is divisible by %d is %d\n", n, findAns(n, fact));

	return 0;
}

void findPrimeFactors(int n, map <int, int>& factors) {
	for (int i = 2; i <= n; i++) {
		while (n % i == 0) {
			n /= i;
			factors[i]++;
		}
	}
}

int findAns(int n, map <int, int> fact) {
	int ans = 0;

	if (fact.size() == 1 && (*(fact.begin())).first == n) {
		ans = n;
	} else {
		for (map <int, int>::iterator i = fact.begin(); i != fact.end(); i++) {
			ans = max(ans, findMinNum((*i).first, (*i).second));
		}
	}

	return ans;
}

int findMinNum(int p, int e) {
	int count = 0;

//	printf("findMinNum(%d, %d)\n", p, e);
	for (int i = p; i <= (p * e); i += p) {
		int iCopy = i;
		while ((iCopy % p) == 0) {
			iCopy /= p;
			count++;
		}
		//		printf("at i = %d\tcount = %d\n", i, count);

		if (count >= e) {
			return i;
		}
	}

	return -1;
}

void showMap(int n, map <int, int> fact) {
	printf("\nFactors of %d are:-\n", n);

	printf("Fact\tPower\n");
	for (map <int, int>::iterator i = fact.begin(); i != fact.end(); i++) {
		printf("%d\t%d\n", ((*i).first), ((*i).second));
	}
}

