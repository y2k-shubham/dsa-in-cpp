// https://www.youtube.com/watch?v=BbITele7neA
/*
	if
		r1 = no of red balls in 1st urn
		b1 = no of blue balls in 1st urn
	then
		no of red balls in 2nd urn = 100 - r1
		no of blue balls in 2nd urn = 100 - b1

	then probability of getting a red ball is given by
	(1/2) * [{r1 / (r1 + b1)} + {(100 - r1) / (200 - r1 - b1)}]

	we just need to vary r1, b1 from 0 to 100 (except both can't be 0 and 100)
*/

#include <cstdio>
#include <iostream>

using namespace std;

#define COUNT_RED 100
#define COUNT_BLUE 100

int main() {
	float mProb = 0.0f;
	int mProbR1, mProbB1;

	for (int r1 = 0; r1 <= 100; r1++) {
		for (int b1 = 0; b1 <= 100; b1++) {
			if ((r1 + b1 != 0) && (r1 + b1 != 200)) {
				float cProb = ((((float) r1) / (r1 + b1)) + (((float) (COUNT_RED - r1)) / ((COUNT_RED + COUNT_BLUE) - r1 - b1))) / 2;
				if (cProb > mProb) {
					mProb = cProb;
					mProbR1 = r1;
					mProbB1 = b1;
				}
			}
		}
	}

	printf("Best strategy is:-\n");
	printf("Urn 1:\t%d R, %d B\n", mProbR1, mProbB1);
	printf("Urn 2:\t%d R, %d B\n", (COUNT_RED - mProbR1), (COUNT_BLUE - mProbB1));
	printf("P(red) = %f\n", mProb);

	return 0;
}

