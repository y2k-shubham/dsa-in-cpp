#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	int T;
	int N;
	int R;
	double a;
	double prod;

	scanf("%d", &T);
	prod = 1.0;

	while (T-- > 0) {
		scanf("%d%d", &N, &R);
		a = R * R * 6 / (double) (N * (N + 1) * (2 * N + 1));
		prod *= a * ((double) pow(N, 2) * pow(N + 1, 2)) / (4 * pow(R, 3));
	}

	//printf("%f\n", prod);
	//prod = floor(prod * 10000) / 10000;
	printf("%.4f\n", prod);

	return 0;
}
