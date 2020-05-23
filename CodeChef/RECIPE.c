#include <stdio.h>

#define len 50

void input(int [], int [][len], int [], int);
int hcf(int, int);
void reduce(int [], int [][len], int [], int);
void output(int [], int quantity[][len], int);

int main() {
    int T;

    scanf("%d", &T);
    int HCF[T];
    int N[T];
    int quantity[T][len];

    input(N, quantity, HCF, T);
    reduce(N, quantity, HCF, T);
    output(N, quantity, T);

    return 0;
}

void input(int N[], int quantity[][len], int HCF[], int T) {
    int i;
    int j;
    int crrN;
    int crrQuant;
    int crrHCF;
    int crrBig;
    int crrSmall;

    for (i = 0; i < T; i++) {
        //printf("Executed\n");
        scanf("%d", &crrN);

        // 1st input
        scanf("%d", &crrQuant);
        quantity[i][0] = crrQuant;
        crrHCF = crrQuant;

        // subsequent inputs
        for (j = 1; j < crrN; j++) {
            scanf("%d", &crrQuant);
            quantity[i][j] = crrQuant;

            crrBig = (crrHCF > crrQuant) ? crrHCF : crrQuant;
            crrSmall = (crrHCF < crrQuant) ? crrHCF : crrQuant;
            crrHCF = hcf(crrBig, crrSmall);

            //printf("\nhcf(%d, %d) = %d\n", crrBig, crrSmall, crrHCF);
        }

        N[i] = crrN;
        HCF[i] = crrHCF;

        /*
        printf("%d", (quantity[i][0] / crrHCF));
        for (j = 1; j < crrN; j++) {
            printf(" %d", (quantity[i][j] / crrHCF));
        }
        printf("\n");
        */
    }
}

int hcf(int big, int small) {
    if (!(big % small)) {
        return small;
    } else {
        return (small, (big % small));
    }
}

void reduce(int N[], int quantity[][len], int HCF[], int T) {
    int i;
    int j;
    int crrHCF;
    int crrN;

    for (i = 0; i < T; i++) {
        crrHCF = HCF[i];
        crrN = N[i];

        for (j = 0; j < crrN; j++) {
            quantity[i][j] /= crrHCF;
        }
    }
}

void output(int N[], int quantity[][len], int T) {
    int i;
    int j;
    int crrN;

    for (i = 0; i < T; i++) {
        crrN = N[i];
        printf("%d", quantity[i][0]);

        for (j = 1; j < crrN; j++) {
            printf(" %d", quantity[i][j]);
        }
        printf("\n");
    }
}
