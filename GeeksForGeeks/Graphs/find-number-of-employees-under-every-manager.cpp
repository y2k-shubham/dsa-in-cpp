// Question URL: http://www.geeksforgeeks.org/find-number-of-employees-under-every-manager/

/*
Note -	in this program, arrays have been preferred over vectors / lists / maps
		wherever possible for speedup considerations. Otherwise, the code would have looked
		much more neat and easy-to-understand by the use of STL containers
*/

/*
Construct tree diagram of the hierarchy to confirm answer

Input
10
H D
I D
A A
J G
G C
D B
E B
F B
B A
C A

Input
6
A C
B C
C F
D E
E F
F F

Input
6
A A
C A
B C
D C
E C
F C
*/

#include <cstdio>
#include <list>
#include <cstring>

using namespace std;
// assuming that only A-Z characters are used (ASCII value of Z is 91)
#define MIN 65
#define MAX 92

// method declarations
void init(list <int> [MAX]);
void input(list <int> [MAX], bool [MAX], bool [MAX]);
void calcCounts(bool [MAX], list <int> [MAX], int empUnderManCounts[MAX]);
int findCount(bool [MAX], list <int> [MAX], int [MAX], int);
void addManagerCounts(bool [MAX], bool [MAX], int [MAX]);
void showCounts(bool [MAX], int [MAX]);

int main() {
	bool isEmp[MAX];
	bool isTopMngr[MAX];
	int juniorCount[MAX];
	list <int> relations[MAX];

	// initially consider that nobody works under person, so all counts are 0
	memset(juniorCount, 0, sizeof(juniorCount));
	// initially consider that no person (A-Z = MIN-91) is an employee
	memset(isEmp, false, sizeof(isEmp));
	// initially consider that
	memset(isTopMngr, true, sizeof(isTopMngr));

	input(relations, isEmp, isTopMngr);

	calcCounts(isEmp, relations, juniorCount);
	/*
	following method will also add count of managers being under themselves, so we'll
	get the no of employees under each top-level person of hierarchy as actual no of persons
	working under him + 1 (himself)
	*/
//	addManagerCounts(isEmp, isTopMngr, juniorCount);

	showCounts(isEmp, juniorCount);

	return 0;
}

// initialize array of list of integers
void init(list <int> relations[MAX]) {
	// initialize list for all possible employees
	for (int i = MIN; i < MAX; i++) {
		list <int> tmp;
		relations[i] = tmp;
	}
}

// take input, store it in relations and also determine all persons that are employees
// as well as all persons that are top-level managers
void input(list <int> relations[MAX], bool isEmp[MAX], bool isTopMngr[MAX]) {
	int noOfRelations;
	scanf("%d", &noOfRelations);

	for (int i = 0; i < noOfRelations; i++) {
		int emp, man;

		/*	read inputs directly in form of integers rather than characters as for characters,
			we'll have to use map <char, int> which will slow down the program because
			map has an access time of O(logn)
		*/

		// loop has been used for input to make it robust against extra spaces, newlines and tabs
		while ((emp = getc(stdin)) == ' ' || emp == '\n' || emp == '\t') {
		}
		while ((man = getc(stdin)) == ' ' || man == '\n' || man == '\t') {
		}

		if (emp != man) {
			// mark that they are both valid employees
			isEmp[emp] = true;
			isEmp[man] = true;

			// also, the given employee can't be a top-level manager as he's working under someone
			isTopMngr[emp] = false;

			// store the relation in the table
			relations[man].push_back(emp);
		} else {
			// he's a top-level manager, don't put the relation in table
			isEmp[emp] = true;
		}
	}
}

// Method to invoke DFS for all employees who's juniorCount[] has not been found
void calcCounts(bool isEmp[MAX], list <int> relations[MAX], int juniorCount[MAX]) {
	bool calcDone[MAX];
	memset(calcDone, false, sizeof(calcDone));

	for (int i = MIN; i < MAX; i++) {
		if (isEmp[i] == true && calcDone[i] == false) {
			// if he is a valid employee, who's count hasn't been found then find it
			findCount(calcDone, relations, juniorCount, i);
		}
	}
}

// Depth-First Search method to find and return no of employees under crrEmp
int findCount(bool calcDone[MAX], list <int> relations[MAX], int juniorCount[MAX], int crrEmp) {
	if (calcDone[crrEmp]) {
		// if count of persons under crrEmp has already been found, return it
		return juniorCount[crrEmp];
	} else {
		// otherwise, recursively find sum of juniorCount[] for all employees who work under crrEmp
		int sum = 0;
		for (list <int>::iterator it = relations[crrEmp].begin(); it != relations[crrEmp].end(); it++) {
			sum += findCount(calcDone, relations, juniorCount, *it) + 1;
		}

		// store the count and mark it as done
		juniorCount[crrEmp] = sum;
		calcDone[crrEmp] = true;

		// return the value of calculated count
		return sum;
	}
}

// this method has not been called but can be called if question says so, read about it in main() method
void addManagerCounts(bool isEmp[MAX], bool isTopMngr[MAX], int juniorCount[MAX]) {
	for (int i = MIN; i < MAX; i++) {
		if (isEmp[i] && isTopMngr[i]) {
			juniorCount[i]++;
		}
	}
}

// display the output
void showCounts(bool isEmp[MAX], int juniorCount[MAX]) {
	printf("\nNo of empoyees under each person are:-\n");
	for (int i = MIN; i < MAX; i++) {
		if (isEmp[i]) {
			printf("%c - %d\n", ((char) i), juniorCount[i]);
		}
	}
}
