#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

class bankAccount {

protected:
	int accountnumber;
	double balance;
	static int counttheaccounts;

public:

	bankAccount() {
		accountnumber = 1000 + counttheaccounts;
		balance = 0.0;
		counttheaccounts = counttheaccounts + 1;
	}
	~bankAccount() { counttheaccounts--; };

	void setaccountnumber(int a) { accountnumber = a; };
	void setbalance(double b) { balance = b; };

	int getaccountnumber() { return accountnumber; };
	double getbalance() { return balance; };

	double withdraw(double w) {
		balance = balance - w;
		return balance;
	}
	double deposit(double d) {
		balance = balance + d;
		return balance;
	}

	void printaccount() {
		cout << fixed << setprecision(2);
		cout << left << setw(15) << " Account Number" << setw(15) << "Account Balance" << endl;
		cout << right << setw(15) << accountnumber << setw(15) << balance << endl;
	}

};
int bankAccount::counttheaccounts;

class checkingAccount : public bankAccount {

private:
	double interest;
	double minimumbalance;
	double servicecharge;
	double feescharged;

	static int countchecking;


public:
	checkingAccount() {
		countchecking++;
		interest = 0.0;
		minimumbalance = 0.0;
		servicecharge = 0.0;
		feescharged = 0.0;
	}
	~checkingAccount() { 
		counttheaccounts--; 
		countchecking--;
	};

	void setinterestrate(double i) { interest = i; };
	void setminimumbalance(double mb) { minimumbalance = mb; };
	void setservicecharge(double sc) { servicecharge = sc; };

	double getinterest() { return interest; };
	double getminimum() { return minimumbalance; };
	double getservicecharge() { return servicecharge; };
	double getfeescharged() { return feescharged; };

	double postinterest() {
		balance = balance + ( balance * (interest * (10^-2)) );
		return balance;
	}

	bool isaboveMinimum() {
		if (balance >= minimumbalance) {
			return true;
		}
		else {
			return false;
		}
	}

	double writecheck() {
		
		double amount;
		string person;

		cout << "Write Check To: ";
		cin >> person;

		cout << "For amount: ";
		cin >> amount;

		cout << "Check written to " << person << " for $" << amount << " from account " << accountnumber << endl;
		balance = balance - amount;

		return balance;
	}

	double chargefee() {
		if (balance < minimumbalance) {
			feescharged = feescharged + servicecharge;
			balance = balance - servicecharge;
		}

		return balance;
	}

	void printaccount() {

		cout << fixed << setprecision(2);
		cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" << setw(18) << "Account Type";
		cout << right << setw(18) << "Interest Rate %" << setw(18) << "Minimum Rate" << setw(18) << "Charge Rate" << setw(18) << "Amount Charged" << endl;
		cout << right << setw(18) << accountnumber << setw(18) << balance << setw(18) << "Checking";
		cout << right << setw(18) << interest << setw(18) << minimumbalance << setw(18) << servicecharge << setw(18) << feescharged << endl;
	}

};
int checkingAccount::countchecking;

class savingsAccount : public bankAccount {

private:
	double interest;
	double interestearned;
	
	static int countsavings;

public:
	savingsAccount() {
		countsavings++;
		interest = 0.0;
		interestearned = 0.0;
	}
	~savingsAccount() { 
		counttheaccounts--;
		countsavings--;
	};

	void setinterestrate(double i) { interest = i; };
	double getinterest() { return interest; };
	double getinterestearned() { return interestearned; };

	double postinterest() {
		balance = balance + (balance * (interest * (10 ^ -2)));
		interestearned = interestearned + (balance * (interest * (10 ^ -2)));
		return balance;
	}

	void printaccount() {
		cout << fixed << setprecision(2);
		cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" << setw(18) << "Account Type";
		cout << right << setw(18) << "Interest Rate %" << setw(18) << "Interest Earned" << endl;
		cout << right << setw(18) << accountnumber << setw(18) << balance << setw(18) << "Savings";
		cout << right << setw(18) << interest << setw(18) << interestearned << endl;
	}
};
int savingsAccount::countsavings;

void updatecheckingaccount(checkingAccount checkingaccounts[], int accountposition);
void updatesavingsaccount(savingsAccount savingsaccounts[], int accountposition);
void printheader();
void printallaccounts(checkingAccount checkingaccounts[], savingsAccount savingsaccounts[]);
int menu(char usertype);

int main() {

	// Create the bank and fabricate the accounts
	checkingAccount checkingaccounts[50];
	savingsAccount savingsaccounts[50];

	// Menu
	bool doagain = true;
	
	// Menu Loop
	while (doagain) {

		char usertype = 'A';
		int menuchoice = 0;

		printheader();
		cout << "Enter [A] for administrator or [C] for customer: ";
		cin >> usertype;
		menuchoice = menu(usertype);

		// Do menu actions
		int manipaccount = 0;
		int accountposition = 0;

		// Admin menu
		if (usertype == 'A') {

			cout << "Enter the account number or account position (enter 0 if N/A): ";
			cin >> manipaccount;
			if (manipaccount >= 100) {
				accountposition = manipaccount - 1000;
			}
			else {
				accountposition = manipaccount;
			}

			switch (menuchoice)
			{

			case 1: // Update a checking
				if (accountposition < 50) {
					updatecheckingaccount(checkingaccounts, manipaccount);
				}
				else {
					cout << "This account number does not refer to a checking account" << endl;
				}
				break;

			case 2: // Update a savings
				if (accountposition >= 50) {
					updatesavingsaccount(savingsaccounts, accountposition - 50);
				}
				else {
					cout << "This account number does not refer to a savings account" << endl;

				}
				break;

			case 3: // Print all accounts
				printallaccounts(checkingaccounts, savingsaccounts);
				break;

			case 4: // Charge fee if applicable
				for (int i = 0; i < 1; i++) {
					if (accountposition < 50) {
						checkingaccounts[accountposition].chargefee();
					}
					else {
						cout << "Sorry, that feature is unavailable for savings accounts" << endl;

					}
				}
				break;

			case 5: // Post interest
				if (accountposition < 50) {
					checkingaccounts[accountposition].postinterest();
				}
				else {
					savingsaccounts[accountposition-50].postinterest();
				}			
				break;

			default:
				cout << "Invalid Choice" << endl;
				break;
			}


		}
		// Customer menu
		else if (usertype == 'C') {

			double w = 0.0;
			double d = 0.0;
			char accounttype = 'C';

			cout << "Enter the account number or account position: ";
			cin >> manipaccount;

			if (manipaccount >= 100) {
				accountposition = manipaccount - 1000;
			}
			else {
				accountposition = manipaccount;
			}
			

			switch (menuchoice)
			{
			case 1: // Withdraw funds
				cout << "Enter withdrawl amount: ";
				cin >> w;

				if (accountposition < 50) {
					checkingaccounts[accountposition].withdraw(w);
				}
				else {
					savingsaccounts[accountposition - 50].withdraw(w);
				}
				break;

			case 2: // Deposit funds
				cout << "Enter deposit amount: ";
				cin >> d;

				if (manipaccount < 50) {
					checkingaccounts[accountposition].deposit(d);
				}
				else{
					savingsaccounts[accountposition - 50].deposit(d);
				}
				break;

			case 3: // Write check
				if (accountposition < 50) {
					checkingaccounts[accountposition].writecheck();
				}
				else {
					cout << "Sorry, this feature is unavailable for savings accounts" << endl;
				}
				break;

			case 4: // Show account details
				if (accountposition < 50) {
					checkingaccounts[accountposition].printaccount();
				}
				else {
					savingsaccounts[accountposition - 50].printaccount();
				}
				break;

			default:
				cout << "Invalid Choice" << endl;
				break;
			}
		}

		char response = 'Y';
		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Would you like to do another action? [Y/N] ";
		cin >> response;

		system("cls");

		if (response != 'Y') {
			doagain = false;
			cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "Thank you for visiting The Bank" << endl;
			cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	
}

void printheader() {
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " WELCOME TO THE BANK" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
}

int menu(char usertype) {

	int menuchoice = 0;

	if (usertype == 'A') {
		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << " [1] Update a checkings account" << endl;
		cout << " [2] Update a savings account" << endl;
		cout << " [3] Show all accounts" << endl;
		cout << " [4] Check and charge fee (if applicable)" << endl;
		cout << " [5] Post interest" << endl;
		cout << " What would you like to do? ";
		cin >> menuchoice;
		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		return menuchoice;

	}
	else {
		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << " [1] Withdraw money" << endl;
		cout << " [2] Deposit money" << endl;
		cout << " [3] Write a check" << endl;
		cout << " [4] View my account details" << endl;
		cout << " What would you like to do? ";
		cin >> menuchoice;
		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		return menuchoice;
	}

}

void updatecheckingaccount(checkingAccount checkingaccounts[], int accountposition) {

	int i = accountposition;
	double newinterest;
	double newminimum;
	double newchargerate;

	cout << endl << "Current Account: " << endl;
	checkingaccounts[i].printaccount();

	cout << endl;
	cout << "Enter New Interest Rate(%):.....";
	cin >> newinterest;
	checkingaccounts[i].setinterestrate(newinterest);
	cout << "Enter new minimum balance:.....$";
	cin >> newminimum;
	checkingaccounts[i].setminimumbalance(newminimum);
	cout << "Enter new charge rate:.........$";
	cin >> newchargerate;
	checkingaccounts[i].setservicecharge(newchargerate);

	cout << endl << "Updated Account: " << endl;
	checkingaccounts[i].printaccount();

}

void updatesavingsaccount(savingsAccount savingsaccounts[], int accountposition) {

	int i = 0;
	double newinterest;

	// account for giving overal position vs savings position
	if (accountposition >= 50) {
		int i = accountposition - 50;
	}
	else {
		int i = accountposition;
	}

	cout << endl << "Current Account: " << endl;
	savingsaccounts[i].printaccount();

	cout << endl;
	cout << "Enter New Interest Rate(%):.....";
	cin >> newinterest;
	savingsaccounts[i].setinterestrate(newinterest);

	cout << endl << "Updated Account: " << endl;
	savingsaccounts[i].printaccount();
}

void printallaccounts(checkingAccount checkingaccounts[], savingsAccount savingsaccounts[]) {

	cout << fixed << setprecision(2);
	cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" << setw(18) << "Account Type";
	cout << right << setw(18) << "Interest Rate" << setw(18) << "Minimum Rate" << setw(18) << "Charge Rate" << setw(18) << "Amount Charged" << endl;

	for (int i = 0; i < 50; i++) {
		
		cout << right << setw(18) << checkingaccounts[i].getaccountnumber() << setw(18) << checkingaccounts[i].getbalance() << setw(18) << "Checking";
		cout << right << setw(18) << checkingaccounts[i].getinterest() << setw(18) << checkingaccounts[i].getminimum();
		cout << right << setw(18) << checkingaccounts[i].getservicecharge() << setw(18) << checkingaccounts[i].getfeescharged() << endl;
	}

	for (int i = 0; i < 50; i++) {

		cout << right << setw(18) << savingsaccounts[i].getaccountnumber() << setw(18) << savingsaccounts[i].getbalance() << setw(18) << "Savings";
		cout << right << setw(18) << savingsaccounts[i].getinterest() << setw(18) << "N/A" << setw(18) << "N/A" << setw(18) << "N/A" << endl;

	}

}