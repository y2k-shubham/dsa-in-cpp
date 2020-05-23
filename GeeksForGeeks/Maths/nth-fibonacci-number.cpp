#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void findPow(vector <int> &, int);
void multiply(vector <int> &, vector <int> &);
void multiply(vector <int> &, const int [4]);
void showVecAsMat(vector <int> &, int);

int main() {
	int n;

	printf("Enter n to find nth fibonacci number:\t");
	scanf("%d", &n);

	if (n < 2) {
		printf("%dth fibonacci number is %d\n", n, n);
	} else {
		static const int arr[] = {1, 1, 1, 0};
		vector <int> mat(arr, arr + 4);

		findPow(mat, n - 1);

		printf("%dth fibonacci number is %d\n", n, mat[0]);
	}

	return 0;
}

void findPow(vector <int> &mat, int exp) {
	if (exp == 1) {
//		showVecAsMat(mat, exp);
	} else {
		static const int tmp[] = {1, 1, 1, 0};

		findPow(mat, exp / 2);
		multiply(mat, mat);

		if (exp % 2 == 1) {
			multiply(mat, tmp);
		}

//		showVecAsMat(mat, exp);
	}
}

void multiply(vector <int> &v1, vector <int> &v2) {
	int e00 = v1[0] * v2[0] + v1[1] * v2[2];
	int e01 = v1[0] * v2[1] + v1[1] * v2[3];
	int e10 = v1[2] * v2[0] + v1[3] * v2[2];
	int e11 = v1[2] * v2[1] + v1[3] * v2[3];

	v1[0] = e00;
	v1[1] = e01;
	v1[2] = e10;
	v1[3] = e11;
}

void multiply(vector <int> &v1, const int v2[4]) {
	int e00 = v1[0] * v2[0] + v1[1] * v2[2];
	int e01 = v1[0] * v2[1] + v1[1] * v2[3];
	int e10 = v1[2] * v2[0] + v1[3] * v2[2];
	int e11 = v1[2] * v2[1] + v1[3] * v2[3];

	v1[0] = e00;
	v1[1] = e01;
	v1[2] = e10;
	v1[3] = e11;
}

void showVecAsMat(vector <int> &vec, int exp) {
	printf("\nFor exp = %d, matrix is:-\n", exp);
	printf("%d\t%d\n%d\t%d\n", vec[0], vec[1], vec[2], vec[3]);
}

