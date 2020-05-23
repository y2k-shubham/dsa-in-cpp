// http://www.geeksforgeeks.org/find-cube-pairs-set-1-n23-solution/
// not the O(n^(2/3)) solution discussed in the post, but close to O(n^(1/3)) solution
// but closer to http://www.geeksforgeeks.org/find-cube-pairs-set-2-n13-solution/

/*
6
1729
1331
4104
512
13832
64
*/

/*
Explanation:	Store all cubes of numbers from 1 to cubeRootN in a map. The key of map is the
				cube and value is the cube-root of key. This loop takes O(N^(1/3)) time

				Although we could've saved space by using set instead of map, but we do so in
				order to avoid cube-root operation afterwards,
				which is not only costly but can also lead to potential errors due to limited
				precision of floating point operations (although it's very unlikely).

				Next we iterate over the above map and each key, we see if N - key is already
				present in map or not. If it is present, then we've found a pair of numbers who's
				cubes add upto N. These numbers are values of map for keys k and N-k, where k is
				the key at current position of iterator. This loop also takes O(N^(1/3)) time

				Whenever a pair is found in above loop, it is added to a set. Finally, the set is
				displayed as output. This loop for displaying set takes
*/

#include <cstdio>
#include <iostream>
#include <set>
#include <map>
#include <cmath>
#include <utility>

using namespace std;

int main() {
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		// declare necessary variables and containers
		int N, cubeRootN;
		map <int, int> cube;
		set <pair <int, int> > pairs;

		// read the number and find it's cube-root
		cout << endl;
		scanf("%d", &N);
		cubeRootN = (int) pow(N, (1.0 / 3.0));

		// find all cubes till cubeRootN. runtime: O(cubeRootN)
		for (int i = 1; i <= cubeRootN; i++) {
			cube.insert(make_pair((int) pow(i, 3), i));
		}

		// iterate over set and if a pair is found, put it into set. runtime: O(cubeRootN)
		for (map <int, int>::iterator it = cube.begin(); it != cube.end(); it++) {
			if ((*it).second > 0 && cube.find(N - ((*it).first)) != cube.end()) {
				pairs.insert(make_pair((*it).second, cube[N - (*it).first]));
				cube[N - (*it).first] = -1;		// to avoid repeated pairs
			}
		}

		if (pairs.size() > 0) {
			// display the found pairs
			for (set <pair <int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
				printf("(%d, %d)\t", (*it).first, (*it).second);
			}
			cout << endl;
		} else {
			// otherwise say that no pairs have been found
			cout << "No cubes add upto " << N << endl;
		}
	}

	return 0;
}
