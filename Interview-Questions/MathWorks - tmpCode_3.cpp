#include <bits/stdc++.h>
using namespace std;
class Account {
private:
	double balance;
public:
	Account (double bal) {
		cout << "balance: " << bal << endl;
		balance = bal;
	}
	virtual double getBalance();
	virtual void printBalance();
};

int main(int argc, char * argv[]) {
	Account *savings = new Account(100.0);
	return 0;
}

