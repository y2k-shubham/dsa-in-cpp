#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
#define MAX 100

int main() {
	string strCPP = "my name is Khan. I'm not a terrorist";
	char strC[MAX] = "my name is Khan. I'm not a terrorist";

	int lo = -20;
	int hi = strlen(strC) + 20;

	for (int i = lo; i <= hi; i++) {
		putc(strC[i], stdout);
	}
	printf("\n");

	for (int i = lo; i <= hi; i++) {
		putchar(strCPP[i]);
	}
	printf("\n");

	return 0;
}

