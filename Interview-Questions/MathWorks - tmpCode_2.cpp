#include <bits/stdc++.h>

void func() {
static int x= 0;
printf("%d\n",x);
x = x + 1;
}

int main(int argc, char * argv[]) {
	func();
	func();
	func();
	return 0;
}

