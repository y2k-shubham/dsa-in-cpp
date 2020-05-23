#include <stdio.h>
#include <math.h>

#define check(P1x, P1y, P2x, P2y, R) ((pow((P1x - P2x), 2) + pow((P1y - P2y), 2)) <= (pow(R, 2)))

void output(int [], int);

int main() {
    int T;
    int R;
    int P1x;
    int P2x;
    int P3x;
    int P1y;
    int P2y;
    int P3y;
    int i;

    scanf("%d", &T);
    int answer[T];

    for (i = 0; i < T; i++) {
        scanf("%d %d %d %d %d %d %d", &R, &P1x, &P1y, &P2x, &P2y, &P3x, &P3y);
        if (check(P1x, P1y, P2x, P2y, R) && check(P2x, P2y, P3x, P3y, R)) {
            answer[i] = 1;
        } else if (check(P2x, P2y, P3x, P3y, R) && check(P3x, P3y, P1x, P1y, R)) {
            answer[i] = 1;
        } else if (check(P3x, P3y, P1x, P1y, R) && check(P1x, P1y, P2x, P2y, R)) {
            answer[i] = 1;
        } else {
            answer[i] = 0;
        }
    }
    output(answer, T);

    return 0;
}

void output(int answer[], int T) {
    char * result[] = {"no\n", "yes\n"};
    int i;

    for (i = 0; i < T; i++) {
        printf("%s", result[answer[i]]);
    }
}
