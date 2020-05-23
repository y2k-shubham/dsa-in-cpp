// http://www.geeksforgeeks.org/find-number-distinct-palindromic-sub-strings-given-string/

/*
abaaa
geek
abaab
abbaeae
a
aa
ab
*/

#include <string>
#include <cstdio>
#include <iostream>
#include <map>
#include <list>
#include <utility>

using namespace std;

void initMap(map <int, map <string, list <pair <int, int> > > >&, int);
list <pair <int, int> > createList(int, int);
void createMap(string, map <int, map <string, list <pair <int, int> > > >&);
void showMap(map <int, map <string, list <pair <int, int> > > >, int);
void showString(string);

int main() {
	string str;
	map <int, map <string, list <pair <int, int> > > > pMap;

	cout << "Enter a string:\t";
	cin >> str;

	initMap(pMap, str.size());
	createMap(str, pMap);

	showString(str);
	showMap(pMap, str.size());

	return 0;
}

void initMap(map <int, map <string, list <pair <int, int> > > >& pMap, int len) {
	for (int i = 0; i <= len; i++) {
		map <string, list <pair <int, int> > > tmpMap;
		list <pair <int, int> > tmpList;

		tmpMap["\0"] = tmpList;
		pMap[i] = tmpMap;
	}
}

list <pair <int, int> > createList(int lo, int hi) {
	list <pair <int, int> > tmpList;
	tmpList.push_back(make_pair(lo, hi));
	return tmpList;
}

void createMap(string str, map <int, map <string, list <pair <int, int> > > >& pMap) {
	for (int i = 0; i < str.size(); i++) {
		for (int r = 0; r < 2; r++) {
			string pal;
			int lo, hi;

			if (r == 0) {
				pal += str[i];

				if (pMap[1].find(pal) == pMap[1].end()) {
					pMap[1][pal] = createList(i, i);
				} else {
					pMap[1][pal].push_back(make_pair(i, i));
				}

				lo = i - 1;
				hi = i + 1;
			} else {
				lo = i;
				hi = i + 1;
			}

			while (lo >= 0 && hi < str.size() && str[lo] == str[hi]) {
				pal = str[lo] + pal + str[hi];
				int len = pal.size();

				if (pMap[len].find(pal) == pMap[len].end()) {
					pMap[len][pal] = createList(lo, hi);
				} else {
					pMap[len][pal].push_back(make_pair(lo, hi));
				}

				lo--;
				hi++;
			}
		}
	}
}

void showMap(map <int, map <string, list <pair <int, int> > > > pMap, int len) {
	printf("\nList of palindromic substrings is:-\n");

	for (int i = 1; i <= len; i++) {
		map <string, list <pair <int, int> > > tmpMap = pMap[i];
		map <string, list <pair <int, int> > >::iterator j = tmpMap.begin();

		if (tmpMap.size() > 1) {
			printf("----------\n");
			printf("Len = %d\n", i);
			for (++j; j != tmpMap.end(); j++) {
				string str = j -> first;
				list <pair <int, int> > tmpList = j -> second;

				cout << str << "\t->\t";
				for (list <pair <int, int> >::iterator k = tmpList.begin(); k != tmpList.end(); k++) {
					printf("[%d..%d]\t", k -> first, k -> second);
				}
				cout << endl;
			}
		}
	}
}

void showString(string str) {
	printf("\nOriginal string is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < str.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Char:\t";
	for (int i = 0; i < str.size(); i++) {
		printf("%c\t", str[i]);
	}
	cout << endl;
}

