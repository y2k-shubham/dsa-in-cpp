#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a > b) ? a : b)
#define max 500000

unsigned int findMaxExchange(unsigned int, unsigned int []);
void generate_table(unsigned int []);

int main() {
    unsigned int count[max + 1];
    unsigned int amount;

    generate_table(count);
    while (scanf("%u", &amount) != EOF) {
        printf("%u\n", findMaxExchange(amount, count));
    }

    return 0;
}

unsigned int findMaxExchange(unsigned int n, unsigned int count[]) {
    if (n <= max) {
        return count[n];
    } else {
        return (findMaxExchange((n >> 1), count) + findMaxExchange((n / 3), count) + findMaxExchange((n >> 2), count));
    }
}

void generate_table(unsigned int count[]) {
    unsigned int n_by_2;
    unsigned int n_by_3;
    unsigned int n_by_4;
    unsigned int i;

    count[0] = 0;
    for (i = 1; i <= max; i++) {
        n_by_2 = i >> 1;
        n_by_3 = i / 3;
        n_by_4 = i >> 2;

        count[i] = MAX((count[n_by_2] + count[n_by_3] + count[n_by_4]), i);
    }
}
