#include <cstdio>
#include <iostream>

int main() {
	double a;
	double b;

	scanf("%lf%lf", &a, &b);
	while ((a > 0.0) && (b > 0.0)) {
		printf("%f / %f = %f\n", a, b, (a / b));
		scanf("%lf%lf", &a, &b);
	}

	return 0;
}
