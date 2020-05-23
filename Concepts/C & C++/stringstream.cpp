#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string a;
	getline(cin,a);
    stringstream ss(a);
    vector <string> vec;
    string bu;
    while (ss >> bu) {
            vec.push_back(bu);
	}
    for (int i = vec.size()-1; i >= 0 ; i--) {
		cout << vec[i] << " ";
    }
}
