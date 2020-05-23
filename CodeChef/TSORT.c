#include <stdio.h>
#include <limits.h>
#define len 1000001

void inputAndCount(unsigned short [], int);
void output(unsigned short []);

int main() {
    int n;
    unsigned short freq[len] = {0};
    //bool mod[len / 8] = {false};

    scanf("%d", &n);

    inputAndCount(freq, n);
    output(freq);

    return 0;
}

void inputAndCount(unsigned short freq[], int n) {
    int i;
    int temp;

    for (i = 1; i <= n; i++) {
        scanf("%d", &temp);
        freq[temp]++;
    }
}

void output(unsigned short freq[]) {
    int i;
    short j;
    short temp;

    for (i = 0; i < len; i++) {
        temp = freq[i];
        for (j = 1; j <= temp; j++) {
            printf("%d\n", i);
        }
    }
}
