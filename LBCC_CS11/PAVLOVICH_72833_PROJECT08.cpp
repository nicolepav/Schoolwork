#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct menuItemType {

	int itemNum;
	string itemName;
	double itemCost;

};
struct billType {

	int itemNum;
	int itemQuantity;
	
	string itemName;
	double itemCost;
	double itemTotalCost;

	int billLength;
};

void windowResize(int width, int height);
void getData(menuItemType menu[], string filename);
void showMenu(menuItemType menu[], string storeName);
void showBill(billType tab[]);
void printBill(billType tab[], string filename);

int main() {

	// Create and populate a new menu
	windowResize(400, 500);
	const int MenuSize = 50;
	menuItemType menuList[MenuSize];
	for (int i = 0; i < MenuSize; i++) {
		
		menuList[i].itemCost = 0.0;
		menuList[i].itemName = { "null" };
		menuList[i].itemNum = { i + 1 };
	}

	// Grab Menu & Print to Screen
	getData(menuList, "theMenu.txt");
	showMenu(menuList, "Hector's Restuarant");

	// Start a Tab
	const int maxtabSize = 5;						// choose the maximum size of a tab
	billType tab[maxtabSize];						// create a new tab array
	for (int i = 0; i < maxtabSize; i++) {

		tab[i].itemCost = 0.0;
		tab[i].itemName = { "null" };
		tab[i].itemNum = { 0 };
		tab[i].itemQuantity = { 0 };
		tab[i].billLength = { 0 };

	}	
	
	// Loop controls
	string nextitem = "Y";

	// Selection Loop
	for (int tabindex = 0; tabindex <= maxtabSize; tabindex++) {

		// Ask for and store an item number
		cout << endl;
		if (tabindex == 0) {
			cout << "   What would you like to order today?" << endl;
			for (int i = 0; i < 50; i++) {
				cout << "-";
			}
			cout << endl;
		}
		cout << left << setw(46) << "   Item number:";
		cin >> right >> setw(6) >> tab[tabindex].itemNum;
		cout << left << setw(46) << "   Item Quantity:";
		cin >> right >> setw(6) >> tab[tabindex].itemQuantity;

		// Assign the correct data based on the item number
		tab[tabindex].itemName = menuList[(tab[tabindex].itemNum - 1)].itemName;
		tab[tabindex].itemCost = menuList[(tab[tabindex].itemNum - 1)].itemCost;

		// Update the length of the bill
		tab[0].billLength = tab[0].billLength + 1;

		// Add more items/Terminate Tab
		if (tab[0].billLength < maxtabSize) {

			cout << left << setw(46) << "   Add another item? (Y/N)";	
			cin >> nextitem;

			if (nextitem != "Y") {
				cout << "   Thank you for your order";
				break;
			}

		}
		else {
			cout << endl;
			cout << "   You have reached the maximum tab size" << endl;
			cout << "   Thank you for your order" << endl;
			break;
		}

	}

	// Print the Tab
	showBill(tab);
	printBill(tab, "Receipt.txt");

}

void windowResize(int width, int height) {
	
	// Resizes the console window to dimensions of choice
	// Approx 8 pixels per column, ~400 px per 50 columns
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);							//stores the console's current dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE); // 400 width, 500 height
}

void getData(menuItemType menu[], string filename) {
	
	// Get Data
	ifstream theMenu;
	theMenu.open(filename);

	// read from file
	int i = 0;
	while (!theMenu.eof()) {
		char dummy;
		getline(theMenu, menu[i].itemName);
		theMenu >> menu[i].itemCost;
		theMenu.get(dummy);
		i++;
	}
}

void showMenu(menuItemType menu[], string storeName) {
	
	system("cls");

	// Menu Title
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "   Menu for " << storeName  << endl;

	// Menu Header/Labels
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << endl;
	cout << left << setw(13) << "   Item" << setw(30) << "Name" << "Cost" << endl;
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << endl;

	// Menu Items (change menu length with j)
	for (int j = 0; j < 8; j++) {
		cout << fixed << setprecision(2) << left << "   #" << setw(9) << menu[j].itemNum << setw(25) << menu[j].itemName << right << setw(3) << "$" << setw(6) << menu[j].itemCost << endl;
	}
	cout << endl;

	// Menu Footer
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
}

void showBill(billType tab[]) {

	// Open top edge of bill & header
	cout << endl;
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "   Bill:" << endl;
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << endl;

	// Column headers for items purchased
	cout << left << setw(26) << "   Item Purchased" << setw(16) << "Qty" << setw(5) << "Cost" << endl << endl;

	// Display items purchased
	for (int i = 0; i < tab[0].billLength; i++) {
		
		tab[i].itemTotalCost = tab[i].itemCost * tab[i].itemQuantity;

		cout << left << fixed << setprecision(1) << "   " << setw(25) << tab[i].itemName << setw(5) << (tab[i].itemQuantity) << right << setprecision(2) <<  setw(7) << "$" << setw(6) << tab[i].itemTotalCost << endl;
	}
	
	// Calculate Totals & Taxes
	double total = 0.0;
	double taxRate = 0.05;
	for (int j = 0; j < tab[0].billLength; j++) {
		total = total + tab[j].itemTotalCost;
	}
	
	// Print final subtotal/tax/total
	cout << endl;
	cout << right << setw(35) << "Subtotal: " << setw(5) << "$" << setw(6) << total << endl;
	cout << right << setw(35) << "Tax (5%): " << setw(5) << "$" << setw(6) << total * taxRate << endl;
	cout << right << setw(35) << "Total: " << setw(5) << "$" << setw(6) << total + (total*taxRate) << endl;

	// Close bottom edge of bill
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}

}

void printBill(billType tab[], string filename) {
	
	ofstream orderTab;
	orderTab.open(filename);

	// Open top edge of bill & header
	// orderTab << endl;
	for (int i = 0; i < 50; i++) {
		orderTab << "-";
	}
	orderTab << endl;
	orderTab << "   Customer Recipt" << endl;
	orderTab << "   Thank you for visiting our restuarant!" << endl;

	for (int i = 0; i < 50; i++) {
		orderTab << "-";
	}
	orderTab << endl;

	// Column headers for items purchased
	orderTab << left << setw(26) << "   Item Purchased" << setw(16) << "Qty" << setw(5) << "Cost" << endl << endl;

	// Display items purchased
	for (int i = 0; i < tab[0].billLength; i++) {

		// Calculate total item cost
		tab[i].itemTotalCost = tab[i].itemCost * tab[i].itemQuantity;
		// Display rows
		orderTab << left << fixed << setprecision(1) << "   " << setw(25) << tab[i].itemName << setw(5) << (tab[i].itemQuantity) << right << setprecision(2) << setw(7) << "$" << setw(6) << tab[i].itemTotalCost << endl;
	
	}

	// Calculate Totals & Taxes
	double total = 0.0;
	double taxRate = 0.05;
	for (int j = 0; j < tab[0].billLength; j++) {
		total = total + tab[j].itemTotalCost;
	}

	// Print final subtotal/tax/total
	orderTab << endl;
	orderTab << right << setw(35) << "Subtotal: " << setw(5) << "$" << setw(6) << total << endl;
	orderTab << right << setw(35) << "Tax (5%): " << setw(5) << "$" << setw(6) << total * taxRate << endl;
	orderTab << right << setw(35) << "Total: " << setw(5) << "$" << setw(6) << total + (total*taxRate) << endl;

	// Close bottom edge of bill
	for (int i = 0; i < 50; i++) {
		orderTab << "-";
	}


}