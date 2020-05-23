#include <stdio.h>
#include <string.h>

#define MAX 100001
#define maxVal(a, b) ((a > b) ? a : b)

void inputInitialAssignment(int [MAX], int [MAX], int [MAX], int, int);
void updateAssignment(int [MAX], int [MAX], int [MAX], int, int);
int findSum(int [MAX], int);
void showArray(const char *, int [MAX], int, int);

int main() {
	int N;
	int M;
	int Q;
	int A;
	int P;
	int actNo;
	int scnNo;
	int actNo_scnNo[MAX];
	int scnNo_noOfAct[MAX];
	int noOfAct_noOfScn[MAX];

    memset(actNo_scnNo, -1, MAX * sizeof(int));
    memset(scnNo_noOfAct, 0, MAX * sizeof(int));
    memset(noOfAct_noOfScn, 0, MAX * sizeof(int));

    /*
	showArray("actNo_ScnNo", actNo_scnNo, 0, MAX - 1);
	showArray("scnNo_noOfAct", scnNo_noOfAct, 0, MAX - 1);
	showArray("noOfAct_noOfScn", noOfAct_noOfScn, 0, MAX - 1);
	*/

	scanf("%d%d%d", &M, &N, &Q);
	noOfAct_noOfScn[0] = M;
	inputInitialAssignment(actNo_scnNo, scnNo_noOfAct, noOfAct_noOfScn, M, N);

    /*
    showArray("actNo_ScnNo", actNo_scnNo, 0, N - 1);
	showArray("scnNo_noOfAct", scnNo_noOfAct, 0, M - 1);
	showArray("noOfAct_noOfScn", noOfAct_noOfScn, 0, N);
    */

	while (Q-- > 0) {
		scanf("%d", &A);

		switch (A) {
		case 1:
			scanf("%d%d", &actNo, &scnNo);
			updateAssignment(actNo_scnNo, scnNo_noOfAct, noOfAct_noOfScn, actNo, scnNo);
            /*
			showArray("actNo_ScnNo", actNo_scnNo, 0, N - 1);
	        showArray("scnNo_noOfAct", scnNo_noOfAct, 0, M - 1);
	        showArray("noOfAct_noOfScn", noOfAct_noOfScn, 0, N);
            */
			break;

		case 2:
			scanf("%d", &P);
			//printf("no of scenes having less than %d actions are:\t", P);
			printf("%d\n", findSum(noOfAct_noOfScn, P));
			break;

		default:
			printf("invalid action\n");
		}
	}

	return 0;
}

void inputInitialAssignment(int actNo_scnNo[MAX], int scnNo_noOfAct[MAX], int noOfAct_noOfScn[MAX], int M, int N) {
	int i;
	int scnNo;

	for (i = 0; i < N; i++) {
		scanf("%d", &scnNo);

        /*
		actNo_scnNo[i] = scnNo;
		noOfAct_noOfScn[scnNo_noOfAct[scnNo]] = maxVal(0, noOfAct_noOfScn[scnNo_noOfAct[scnNo]] - 1);
		scnNo_noOfAct[scnNo]++;
		noOfAct_noOfScn[scnNo_noOfAct[scnNo]]++;
		*/
		updateAssignment(actNo_scnNo, scnNo_noOfAct, noOfAct_noOfScn, i, scnNo);

        /*
		showArray("actNo_ScnNo", actNo_scnNo, 0, N - 1);
	    showArray("scnNo_noOfAct", scnNo_noOfAct, 0, M - 1);
        showArray("noOfAct_noOfScn", noOfAct_noOfScn, 0, N);
        */
	}
}

void updateAssignment(int actNo_scnNo[MAX], int scnNo_noOfAct[MAX], int noOfAct_noOfScn[MAX], int actNo, int newScnNo) {
	int oldScnNo;

	// update actor's assigned scene no and extract the previous scene no to which actor was assigned
	oldScnNo = actNo_scnNo[actNo];
	actNo_scnNo[actNo] = newScnNo;

    /*
    printf("Actor No:\t%d\n", actNo);
    printf("Old Scn No:\t%d\n", oldScnNo);
    printf("New Scn No:\t%d\n", newScnNo);
    */

	// decrement no of scenes assigned to that no of actions, which the old scene no had
	if (oldScnNo >= 0) {
	    noOfAct_noOfScn[scnNo_noOfAct[oldScnNo]]--;
	}
	noOfAct_noOfScn[scnNo_noOfAct[newScnNo]]--;

	// decrement no of actions that old scene no had and increment no of actions that new scene no has
	if (oldScnNo >= 0) {
	    scnNo_noOfAct[oldScnNo]--;
	}
	scnNo_noOfAct[newScnNo]++;

	// increment no of scenes assigned to that no of actions which new scene no has
	if (oldScnNo >= 0) {
	    noOfAct_noOfScn[scnNo_noOfAct[oldScnNo]]++;
	}
	noOfAct_noOfScn[scnNo_noOfAct[newScnNo]]++;
}

int findSum(int noOfAct_noOfScn[MAX], int P) {
	int i;
	int sum;

	sum = 0;
	for (i = 0; i < P; i++) {
		sum += noOfAct_noOfScn[i];
	}

	return sum;
}

void showArray(const char * arrName, int arr[MAX], int lo, int hi) {
    int i;

    printf("\nThe array %s is:-\n", arrName);
    for (i = lo; i <= hi; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}
