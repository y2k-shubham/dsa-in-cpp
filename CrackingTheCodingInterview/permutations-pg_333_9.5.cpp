#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
void genPerms(string, vector <string>&);
void showPerms(vector <string>);
void swap(string&, int, int);
void findPerms(string, int);

int main() {
	string str;
	vector <string> perms;

	cout << "Enter a string:\t";
	cin >> str;

	//genPerms(str, perms);
	//showPerms(perms);

	findPerms(str, 0);

	return 0;
}

void genPerms(string str, vector <string>& permsOrig) {
	permsOrig.clear();
	permsOrig.push_back(str.at(0) + "");
	
	for (int i = 1; i < str.length(); i++) {
		
		char c = str.at(i);
		vector <string> permsNew;
		cout << "char = " << c << endl;

		permsNew.clear();
		for (int j = 0; j < permsOrig.size(); j++) {
			
			//cout << permsOrig[j] << endl;
			printf("j = %d, permsOrig[%d] = ", j, j);
			cout << permsOrig[j] << endl;
			permsNew.push_back(c + permsOrig[j]);
			//cout << (c + permsOrig[j]) << endl;
			
			for (int k = 1; k < permsOrig[j].length(); k++) {
				//printf("i = %d, j = %d, k = %d\n", i, j, k);
				string lPart = permsOrig[j].substr(0, k);
				
				if (lPart.at(lPart.length() - 1) != c) {
					string rPart = permsOrig[j].substr(k);
					permsNew.push_back(lPart + c + rPart);
					//cout << (lPart + c + rPart) << endl;
				}
			}
			
			if (permsOrig[j].at(permsOrig[j].length() - 1) != c) {
				permsNew.push_back(permsOrig[j] + c);
				//cout << (permsOrig[j] + c) << endl;
			}
			//cout << endl;
		}

		permsOrig.clear();
		permsOrig = permsNew;
		//showPerms(permsOrig);
		//cout << "\n==============\n";
	}
}

void showPerms(vector <string> perms) {
	cout << "\nThe permutations are:-\n";
	for (vector <string>::iterator it = perms.begin(); it != perms.end(); it++) {
		cout << *it << endl;
	}
	cout << endl;
}

void findPerms(string str, int ind) {
	if (ind == str.length() - 1) {
		cout << str << endl;
	} else {
		findPerms(str, ind + 1);
		for (int i = ind + 1; i < str.length(); i++) {
			swap(str, ind, i);
			findPerms(str, ind + 1);
		}
	}
}

void swap(string& str, int p1, int p2) {
	char c1 = str.at(p1);
	char c2 = str.at(p2);
	string lPart = str.substr(0, p1);
	string mPart = str.substr(p1 + 1, p2 - p1 - 1);
	string rPart = str.substr(p2 + 1);
	str.clear();
	str = lPart + c2 + mPart + c1 + rPart;
}
