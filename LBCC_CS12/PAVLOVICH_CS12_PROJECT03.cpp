#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

class bankAccount 
{
    protected:
        int accountnumber;
        double balance;
		
		string fname;
        string lname;

        static int counttheaccounts;

    public:

        bankAccount() 
        {
            accountnumber = 1000 + counttheaccounts;
            balance = 0.0;
            counttheaccounts = counttheaccounts + 1;

            fname = "No Name Assigned";
            lname = "No Name Assigned";
        }
        bankAccount(string f, string l)
        {
            accountnumber = 1000 + counttheaccounts;
            balance = 0.0;
            counttheaccounts = counttheaccounts + 1;

            fname = f;
            lname = l;
        }
        ~bankAccount() { counttheaccounts--; };

        void setaccountnumber(int a) { accountnumber = a; };
        void setbalance(double b) { balance = b; };
        void setFname(string f) { fname = f; };
        void setLname(string l) { lname = l; };

        int getaccountnumber() { return accountnumber; };
        double getbalance() { return balance; };
        string getFname() { return fname; };
        string getLname() { return lname; };

        virtual void monthlyStatement() = 0;
        virtual void printAccount() = 0;

        double withdraw(double w) 
        {
            balance = balance - w;
            return balance;
        }
        double deposit(double d) 
        {
            balance = balance + d;
            return balance;
        }

};
int bankAccount::counttheaccounts;

class checkingAccount : public bankAccount 
{
    protected:
        double interest;
        double minimumbalance;

        static int countchecking;

    public:
        checkingAccount() 
        {
            countchecking++;
            interest = 0.0;
            minimumbalance = 0.0;
        }
        checkingAccount(string f, string l):bankAccount(f, l) 
        {
            countchecking++;
            interest = 0.0;
            minimumbalance = 0.0;
        }		
		checkingAccount(double mb, double ir)
		{
			countchecking++;
            interest = ir;
            minimumbalance = mb;
		}
		checkingAccount(double mb, double ir, string f, string l):bankAccount(f,l)
		{
			countchecking++;
            interest = ir;
            minimumbalance = mb;
		}
        ~checkingAccount() 
        { 
            countchecking--;
        };

        void setinterestrate(double i) { interest = i; };
        void setminimumbalance(double mb) { minimumbalance = mb; };

        double getinterest() { return interest; };
        double getminimum() { return minimumbalance; };

	    virtual double writeCheck() = 0;

        bool isaboveMinimum() 
        {
            if (balance >= minimumbalance) {
                return true;
            }
            else {
                return false;
            }
        }

        // redefine the original virtual
        void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent " << setw(18) << "Acct Minimum" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << minimumbalance << endl;
        }

};
int checkingAccount::countchecking;

class serviceChargeChecking : public checkingAccount
{
    protected:
        int maxChecks;
        int checksWritten;

		double servicecharge;
        double feescharged;

    public:
        serviceChargeChecking()
        {
			// construct with no details
			maxChecks = 10;
            checksWritten = 0;
			servicecharge = 0.0;
			feescharged = 0.0;

        }
        serviceChargeChecking(string f, string l):checkingAccount(f, l)
        {
            // construct with only a name
			maxChecks = 10;
            checksWritten = 0;
			servicecharge = 0.0;
			feescharged = 0.0;
        }
		serviceChargeChecking(int maxC, int cw, int ir, double sc, string f, string l):checkingAccount(0.0, ir, f, l)
        {
            // construct with all account details
			// force a minimum balance of zero for this account type
			// pass interest rate to checking constructor
			maxChecks = maxC;
            checksWritten = cw;
			servicecharge = sc;
			feescharged = 0.0;
        }
		~serviceChargeChecking() {}

        void setmaxchecks(int mc) { maxChecks = mc; }				// allow changing max checks permitted
        void setservicecharge(double sc) { servicecharge = sc; }	// allow changing the service fee
		void setcheckswritten(int cw) { checksWritten = cw; }		// allow reseting checks written
		
		double getservicecharge() { return servicecharge; }
        double getfeescharged() { return feescharged; }
		int getcheckswritten()	{ return checksWritten; }


		double chargefee() 
        {
            
			feescharged = feescharged + servicecharge;
            balance = balance - servicecharge;
			cout << "Fee was charged" << endl;

			// fees charged monthly regardless of balance
			// if (balance < minimumbalance) 
			// {
            //     feescharged = feescharged + servicecharge;
			// 	cout << "Balance is below minimum. Fee charged to account for amount: " << servicecharge << endl;
            //     balance = balance - servicecharge;
            // }

            return balance;
        }
		
		double writeCheck()override 
		{
			string writeTo;
			double amount;
			
			if(checksWritten < maxChecks)
			{
				cout << "Write check to: ";
				cin >> writeTo;

				cout << "For amount of: ";
				cin >> amount;

				cout << "Check written to " << writeTo << " for " << amount;
				cout << ". This amount has been deducted from your account" << endl;

				balance = balance - amount;
			}
			else 
			{
				cout << "Sorry, this account has reached its max number of checks written" << endl;
				balance = balance;
			}

			return balance;
		}
		
		void monthlyStatement()override {} 		
		
		void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent " << setw(18) << "Acct Minimum";
			cout << right << setw(18) << "Acct Type" << setw(18) << "Monthly Fee" << setw(18) << "Max Checks" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << minimumbalance << endl;
			cout << right << setw(18) << "Service Charge" << setw(18) << servicecharge << setw(18) << maxChecks << endl;

        }

};

class noServiceChargeChecking : public checkingAccount
{
	public:
		noServiceChargeChecking(double mb = 100, double ir = 0.5):checkingAccount(mb, ir)
		{
			// default constructor, can be used to set mb and ir if needed
			// default account details min balance 100 interest 0.5
		}
		noServiceChargeChecking(string f, string l, double mb = 100, double ir = 0.5):checkingAccount(mb, ir, f,l)
		{
			// default account details min balance 100 interest 0.5
			// also lets you add a name
		}
		~noServiceChargeChecking() {}

        double postinterest() 
        {
            balance = balance + ( balance * (interest * pow(10, -2)) );
			cout << "Interest posted: " << balance * (interest * pow(10, -2)) << endl;
            return balance;
        }
		
		double writeCheck()override 
		{
			string writeTo;
			double amount;

			cout << "Write check to: ";
			cin >> writeTo;

			cout << "For amount of: ";
			cin >> amount;

			cout << "Check written to " << writeTo << " for " << amount;
			cout << ". This amount has been deducted from your account" << endl;

			balance = balance - amount;
			return balance;
		}
		void monthlyStatement()override {}

		void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent " << setw(18) << "Acct Minimum";
			cout << right << setw(18) << "Acct Type" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << minimumbalance << endl;
			cout << right << setw(18) << "No Charge" << endl;

        }
};

class highInterestChecking : public noServiceChargeChecking
{
	public:
		highInterestChecking(double mb = 500.00, double ir = 1.5):noServiceChargeChecking(mb,ir)
		{
			// default constructor, can be used to set mb and ir if needed
			// default account details min balance 500 interest 1.5
		}
		highInterestChecking(string f, string l, double mb = 500.00, double ir = 1.5):noServiceChargeChecking(f, l, mb, ir)
		{
			// default account details min balance 500 interest 1.5
			// can be used to set mb and ir if needed
			// allows you to also set a name
		}
		~highInterestChecking() {};

		void monthlyStatement() {} ;
		// inherit ability to write unlimited checks

		void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent " << setw(18) << "Acct Minimum";
			cout << right << setw(18) << "Acct Type" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << minimumbalance << endl;
			cout << right << setw(18) << "High interest" << endl;

        }
};

class savingsAccount : public bankAccount 
{
	protected:
		double interest;
		double interestearned;
		
		static int countsavings;

	public:
		savingsAccount() 
		{
			// absolute back up
			countsavings++;
			interest = 0.0;
			interestearned = 0.0;
		}
		savingsAccount(string f, string l):bankAccount(f,l)
		{
			// absolute back up but with a name attached
			countsavings++;
			interest = 0.0;
			interestearned = 0.0;
		}
		savingsAccount(double ir)
		{
			// set just the interest, no name
			countsavings++;
			interest = ir;
			interestearned = 0.0;
		}
		savingsAccount(string f, string l, double ir):bankAccount(f,l)
		{
			// set name, set interest
			countsavings++;
			interest = ir;
			interestearned = 0.0;
		}
		~savingsAccount() { 
			counttheaccounts--;
			countsavings--;
		};

		void setinterestrate(double i) { interest = i; };
		double getinterest() { return interest; };
		double getinterestearned() { return interestearned; };

		double postinterest() 
        {
            balance = balance + ( balance * (interest * pow(10, -2)) );
			interestearned = interestearned + (balance + ( balance * (interest * pow(10, -2)) ));
            cout << "Interest posted: " << balance * (interest * pow(10, -2)) << endl;
			return balance;
        }

		void monthlyStatement()override {} ;
		void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent" << setw(18) << "Acct Type";
			cout << right << setw(18) << "Interest Earned" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << "Savings" << endl;
			cout << right << setw(18) << interestearned << endl;
        }
};
int savingsAccount::countsavings;

class highInterestSavings : public savingsAccount 
{
	private:
		double minimumbalance;

	public:
		highInterestSavings(double ir = 2.5, double mb = 1000.00):savingsAccount(ir)
		{
			// default constructor, can be used to set mb and ir if needed
			minimumbalance =  mb;
		}
		highInterestSavings(string f, string l, double ir = 2.5, double mb = 1000.00):savingsAccount(f, l, ir)
		{
			// default settings plus set name, 
			// can be used to set mb and ir if needed
			minimumbalance = mb;
		}
		~highInterestSavings(){};

	    void setminimumbalance(double mb) { minimumbalance = mb; };

		// inherits ability to post interest
		// inherits standard withdrawl and deposit
		
		void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent" << setw(18) << "Acct Type";
			cout << right << setw(18) << "Interest Earned" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << "High Int Saving" << endl;
			cout << right << setw(18) << interestearned << endl;
        };
};

class certificateOfDeposit : public bankAccount
{
	private:
		int numMaturityMonths;
		int monthsActive;
		double interest;
		double penaltyPercentage;

	public:
		certificateOfDeposit() 
		{
			// default account settings
			interest = 2.75;
			penaltyPercentage =  10.00;
			numMaturityMonths = 60;
			monthsActive = 0;
		}
		certificateOfDeposit(string f, string l):bankAccount(f,l) 
		{
			// default account settings
			// allow assigning a name
			interest = 2.75;
			penaltyPercentage =  10.00;
			numMaturityMonths = 60;
			monthsActive = 0;
		}
		certificateOfDeposit(string f, string l, double ir =  2.5, double pP = 10.00, int MM = 60):bankAccount(f,l)
		{
			// assign all account settings (or allow defaults)
			// allow assigning a name
			interest = ir;
			penaltyPercentage = pP;
			numMaturityMonths = MM;
			monthsActive = 0;
		}
		~certificateOfDeposit() {};

		void setinterestrate(double ir) { interest = ir; }
		void setmaturitylength(int mm) { numMaturityMonths = mm; }
		void setpenaltypercentage(double pp) { penaltyPercentage = pp; }
		void setmonthsactive(int ma) { monthsActive = ma; }

		double getinterestrate() {return interest; }
		double getpenaltypercent() { return penaltyPercentage; }
		int getmaturitylength() { return numMaturityMonths; }
		int getmonthsactive() { return monthsActive; }

		void addmonthactive() { monthsActive++; }

		double postinterest() 
        {
            balance = balance + ( balance * (interest * pow(10, -2)) );
			cout << "Interest posted: " << balance * (interest * pow(10, -2)) << endl;
            return balance;
        }
		double withdraw(double w) 
		{
			balance = balance - w;

			if (monthsActive < numMaturityMonths)
			{
				cout << "You are withdrawing from a CD that is not of age. " << endl;
				cout << "You will be charged " << penaltyPercentage << " of your withdrawl" << endl;
				balance = balance - (w * penaltyPercentage);
			}
			
            return balance;
		} 

		void monthlyStatement()override {} 
		void printAccount() 
        {
			cout << fixed << setprecision(2);
            
			cout << right << setw(18) << " Account Number" << setw(18) << "Account Balance" ;
            cout << right << setw(18) << "Interest Percent" << setw(18) << "Acct Type";
			cout << right << setw(18) << "Maturity Length" << setw(18) << "Months Active";
			cout << right << setw(18) << "Penalty Percentage" << endl;
            
			cout << right << setw(18) << accountnumber << setw(18) << balance;
            cout << right << setw(18) << interest << setw(18) << "C.D." << endl;
			cout << right << setw(18) << numMaturityMonths << setw(18) << monthsActive;
			cout << right << setw(18) << penaltyPercentage << endl;
        }
};

// Functions for admin updates
template <typename checkingtype>
void updateCheckingType(checkingtype accounts[], int accountposition);
template <typename savingstype>
void updateSavingsType(savingstype accounts[], int accountposition);
void updateCDtype(certificateOfDeposit accounts[], int accountposition);

// Mass print
void printAll(serviceChargeChecking SCarray[],noServiceChargeChecking NSCarray[], highInterestChecking HICarray[], savingsAccount SAarray[], highInterestSavings HISarray[], certificateOfDeposit CDarray[]);

// Functions for the basic bank
int menu(char usertype);
void printheader();


int main() {

	// Create the bank and fabricate the accounts
	// checkingAccount checkingaccounts[50];
	// savingsAccount savingsaccounts[50];

	// Create the bank //
	// Checking accounts available
	serviceChargeChecking scCheckingAccounts[10];
	noServiceChargeChecking nscCheckingAccounts[10];
	highInterestChecking hiCheckingAccounts[10];

	// Savings accounts available
	savingsAccount genericSavingAccounts[10];
	highInterestSavings hiSavingsAccounts[10];

	// CD accounts available
	certificateOfDeposit CdAccounts[10];

	// Menu
	bool doagain = true;
	
	// Menu Loop
	while (doagain) 
	{
		char usertype = 'A';
		int menuchoice = 0;

		printheader();
		cout << "Enter [A] for administrator or [C] for customer: ";
		cin >> usertype;
		// print correct menu, accept choice
		menuchoice = menu(usertype);

		// Do menu actions
		int manipaccount = 0;
		int accountposition = 0;

		// Admin menu
		if (usertype == 'A') 
		{
			cout << "Enter the account number or account position (enter 0 if N/A): ";
			cin >> manipaccount;
			if (manipaccount >= 60) // if they provide num #### instead of overallpos #
			{
				accountposition = manipaccount - 1000; // convert to overallpos
			}
			else 
			{
				accountposition = manipaccount;
			}

			// menu actions
			switch (menuchoice)
			{

			case 1: // Update a checking, pick correct type based on position
				if (accountposition < 10) 
				{
					updateCheckingType(scCheckingAccounts, accountposition);
					double newchargerate = 0.0;
					cout << "Enter new charge rate:.................$";
					cin >> newchargerate;
					scCheckingAccounts[accountposition].setservicecharge(newchargerate);
				}
				else if (accountposition < 20)
				{
					updateCheckingType(nscCheckingAccounts, accountposition - 10);
				}
				else if (accountposition < 30)
				{
					updateCheckingType(hiCheckingAccounts, accountposition - 20);
				}
				else 
				{
					cout << "This account number does not refer to a checking account" << endl;
				}
				break;

			case 2: // Update a savings, pick correct type based on position

				if (accountposition < 40) 
				{
					updateSavingsType(genericSavingAccounts, accountposition - 30);
				}
				else if (accountposition < 50)
				{
					updateSavingsType(hiSavingsAccounts, accountposition - 40);
					double newminimum = 0.0;
					cout << "Enter new minimum balance:.................$";
					cin >> newminimum;
					hiSavingsAccounts[accountposition - 40].setminimumbalance(newminimum);
				}
				else 
				{
					cout << "This account number does not refer to a savings account" << endl;
				}
				break;
			case 3: // Update a certificate of deposit
				if (accountposition < 60 && accountposition >= 50)
				{
					updateCDtype(CdAccounts, accountposition - 50);
				}
				else 
				{
					cout << "This account number does not refer to a Certificate of Deposit" << endl;
				}
				break;	
			case 4: // Print all accounts
				printAll(scCheckingAccounts, nscCheckingAccounts, hiCheckingAccounts,genericSavingAccounts, hiSavingsAccounts, CdAccounts);
				break;

			case 5: // Charge fee if applicable
				cout << "Service charge accounts have a monthly fee regardless of balance." << endl;
				cout << "These accounts are numbered between 0 and 9" << endl;
				
				if (accountposition < 10) 
				{
					scCheckingAccounts[accountposition].chargefee();
				}
				else 
				{
					cout << "The number you have entered does not refer to the correct account type" << endl;
				}
				break;

			case 6: // Post interest
				
				cout << "The following account types can earn interest:" << endl;
				cout << "no service charge and high interest checking (10-29), all savings accounts (30-49), CDs (50-59)" << endl;
				
				if (accountposition < 10){
					cout << "This account type cannot earn interest" << endl;
				}
				else if (accountposition < 20) {
					nscCheckingAccounts[accountposition - 10].postinterest();
				}
				else if (accountposition < 30){
					hiCheckingAccounts[accountposition - 20].postinterest();
				}
				else if (accountposition < 40){
					genericSavingAccounts[accountposition - 30].postinterest();
				}	
				else if (accountposition < 50){
					hiSavingsAccounts[accountposition - 40].postinterest();
				}	
				else if (accountposition < 60){
					CdAccounts[accountposition - 50].postinterest();
				}	
				else {
					cout << "not a valid account number" << endl;
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
			if (manipaccount >= 60) // if they provide num #### instead of overallpos #
			{
				accountposition = manipaccount - 1000; // convert to overallpos
			}
			else 
			{
				accountposition = manipaccount;
			}
			
			switch (menuchoice)
			{
			case 1: // Withdraw funds
				cout << "Enter withdrawl amount: ";
				cin >> w;

				if (accountposition < 10){
					scCheckingAccounts[accountposition].withdraw(w);
					cout << "You have withdrawn " << w << " from your account" << endl;
				}
				else if (accountposition < 20) {
					nscCheckingAccounts[accountposition - 10].withdraw(w);
					cout << "You have withdrawn " << w << " from your account" << endl;
				}
				else if (accountposition < 30){
					hiCheckingAccounts[accountposition - 20].withdraw(w);
					cout << "You have withdrawn " << w << " from your account" << endl;
				}
				else if (accountposition < 40){
					genericSavingAccounts[accountposition - 30].withdraw(w);
					cout << "You have withdrawn " << w << " from your account" << endl;
				}	
				else if (accountposition < 50){
					hiSavingsAccounts[accountposition - 40].withdraw(w);
					cout << "You have withdrawn " << w << " from your account" << endl;
				}	
				else if (accountposition < 60){
					CdAccounts[accountposition - 50].withdraw(w);
					cout << "You have withdrawn " << w << " from your account" << endl;
				}	
				else {
					cout << "not a valid account number" << endl;
				}

			case 2: // Deposit funds
				cout << "Enter deposit amount: ";
				cin >> d;

				if (accountposition < 10){
					scCheckingAccounts[accountposition].deposit(d);
					cout << "You have added " << d << " to your account" << endl;
				}
				else if (accountposition < 20) {
					nscCheckingAccounts[accountposition - 10].deposit(d);
					cout << "You have added " << d << " to your account" << endl;
				}
				else if (accountposition < 30){
					hiCheckingAccounts[accountposition - 20].deposit(d);
					cout << "You have added " << d << " to your account" << endl;
				}
				else if (accountposition < 40){
					genericSavingAccounts[accountposition - 30].deposit(d);
					cout << "You have added " << d << " to your account" << endl;
				}	
				else if (accountposition < 50){
					hiSavingsAccounts[accountposition - 40].deposit(d);
					cout << "You have added " << d << " to your account" << endl;
				}	
				else if (accountposition < 60){
					CdAccounts[accountposition - 50].deposit(d);
					cout << "You have added " << d << " to your account" << endl;
				}	
				else {
					cout << "not a valid account number" << endl;
				}

			case 3: // Write check
				
				if (accountposition < 10) {
					nscCheckingAccounts[accountposition].writeCheck();
				}
				else if (accountposition < 20){
					scCheckingAccounts[accountposition - 10].writeCheck();
				}
				else if (accountposition < 30){
					hiCheckingAccounts[accountposition - 20].writeCheck();
				}
				else {
					cout << "Error: Account number does not refer to a checking account" << endl;
				}
				break;

			case 4: // Show account details ADD HEADER
				if (accountposition < 10){
					scCheckingAccounts[accountposition].printAccount();
				}
				else if (accountposition < 20) {
					nscCheckingAccounts[accountposition - 10].printAccount();
				}
				else if (accountposition < 30){
					hiCheckingAccounts[accountposition - 20].printAccount();
				}
				else if (accountposition < 40){
					genericSavingAccounts[accountposition - 30].printAccount();
				}	
				else if (accountposition < 50){
					hiSavingsAccounts[accountposition - 40].printAccount();
				}	
				else if (accountposition < 60){
					CdAccounts[accountposition - 50].printAccount();
				}	
				else {
					cout << "not a valid account number" << endl;
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

// Functions for the basic bank
void printheader() 
{
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " WELCOME TO THE BANK" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
}

int menu(char usertype) 
{

	int menuchoice = 0;

	if (usertype == 'A') {
		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << " [1] Update a checkings account" << endl;
		cout << " [2] Update a savings account" << endl;
		cout << " [3] Update a certificate of deposit" << endl;
		cout << " [4] Show all accounts" << endl;
		cout << " [5] Check and charge fee (if applicable)" << endl;
		cout << " [6] Post interest" << endl;
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

// Mass print
void printAll(serviceChargeChecking SCarray[],noServiceChargeChecking NSCarray[], highInterestChecking HICarray[], savingsAccount SAarray[], highInterestSavings HISarray[], certificateOfDeposit CDarray[])
{
	cout << "Registry of all accounts" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 60; i ++){

		if (i < 10){
			// header
			SCarray[i].printAccount();
			if (i == 9) { cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;}
		}
		else if (i < 20){
			// header
			NSCarray[i].printAccount();
			if (i == 19) { cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;}
		}
		else if (i < 30){
			// header
			HICarray[i].printAccount();
			if (i == 29) { cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;}
		}
		else if (i < 40){
			// header
			SAarray[i].printAccount();
			if (i == 39) { cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;}

		}
		else if (i<50){
			//header
			HISarray[i].printAccount();
			if (i == 49) { cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;}

		}
		else if (i < 60){
			// header
			CDarray[i].printAccount();
			if (i == 59) { cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;}

		}

	}
}

// Functions for admin updates //
template <typename savingstype>
void updateSavingsType(savingstype accounts[], int accountposition)
{
	int i = accountposition;
	double newinterest;
	double newminimum;

	cout << "Enter New Interest Rate(%):.............";
	cin >> newinterest;
	accounts[i].setinterestrate(newinterest);

	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "Updated Account: " << endl;
	//accounts[i].printAccount(); // fix this function
}

template <typename checkingtype>
void updateCheckingType(checkingtype accounts[], int accountposition)
{
	int i = accountposition;
	double newinterest;
	double newminimum;
	double newchargerate;

	cout << "Enter new interest rate(%):.............";
	cin >> newinterest;
	accounts[i].setinterestrate(newinterest);

	cout << "Enter new minimum balance:.............$";
	cin >> newminimum;
	accounts[i].setminimumbalance(newminimum);

	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "Updated Account: " << endl;
	//accounts[i].printAccount(); // fix this function

}

void updateCDtype(certificateOfDeposit accounts[], int accountposition)
{
	int i = accountposition;
	int newma = 0;
	int newml = 0;
	double newPenalty = 0.0;
	double newinterest;

	cout << "Enter new interest rate(%):.............";
	cin >> newinterest;
	accounts[i].setinterestrate(newinterest);
	cout << "Enter new penalty percentage:...........";
	cin >> newPenalty;
	accounts[i].setpenaltypercentage(newPenalty);
	cout << "Enter new maturity length:..............";
	cin >> newml;
	accounts[i].setmaturitylength(newml);
	cout << "Enter new months active:................";
	cin >> newma;
	accounts[i].setmonthsactive(newma);

	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "Updated Account: " << endl;
	//accounts[i].printAccount(); // fix this function

}
