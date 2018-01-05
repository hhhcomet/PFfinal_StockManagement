//
//main_RongZhang.cpp
//Final project by RongZhang
//

#include <iostream>
#include <string>
#include <iomanip>
#include "BankAccount.h"
#include "StockAccount.h"
#include <fstream>
using namespace std;

void bankmenu(BankAccount *value)
{//print the menu of Bankaccount
	while (1)
	{
		cout << "\nPlease select an option:" << endl;
		cout << "1. View account balance" << endl;
		cout << "2. Deposit money" << endl;
		cout << "3. Withdraw money" << endl;
		cout << "4. Print out history" << endl;
		cout << "5. Return to previous menu" << endl;
		cout << endl << "Option:";

		int choice;
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			value->GetBalance();
			break;
		case 2:
			value->Deposit();
			break;
		case 3:
			value->Withdraw();
			break;
		case 4:
			value->PrintHistory();
		case 5:
			return;
			break;
		dafault:
			{
				cout << "Your option is invalid. Try again." << endl;
				break;
			}
		}
	}
}

void stockmenu(StockAccount *value)
{//print the menu of stock account
	while (1)
	{
		cout << "\nPlease select an option:" << endl;
		cout << "1. Display the price of a stock symbol" << endl;
		cout << "2. Display the current portfolio" << endl;
		cout << "3. Buy shares" << endl;
		cout << "4. Sell shares" << endl;
		cout << "5. View a graph for the portfolio value" << endl;
		cout << "6. View transaction history" << endl;
		cout << "7. Choose your sort method" << endl;
		cout << "8. Return to previous menu" << endl;
		cout << endl << "Option: ";
		int choice;
		static int sortchoice = 1;//a static integer to choose the sort method
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
		{
			double price_;
			string sym_;
			cout << endl << "Please enter the stock symbol:";
			cin >> sym_;
			price_ = value->FindPrice(sym_);
			if (price_ == 0)
				cout << "Symbol is not in this list." << endl;//there is not the stock
			else {
				cout << "Company Symbol        Price Per Share" << endl;
				cout << left<<setw(20)<<sym_ << setw(14) << price_ << endl;//print the name and the price of the stock
			}
			break;
		}
		case 2:
			value->Sort(sortchoice);
			value->DisplayPortfolio();
			break;
		case 3:
			value->BuyShare();
			value->Sort(sortchoice);
			break;
		case 4:
			value->SellShare();
			value->Sort(sortchoice);
			break;
		case 5:
			value->Sort(sortchoice);
			value->ViewGraph();
			break;
		case 6:
			value->Sort(sortchoice);
			value->PrintHistory();
			break;
		case 7:
		{
			int c;
			cout << "Choose your sort method for your list." << endl;
		    cout << "1.Bubble sort" << endl;
		    cout << "2.Insertion sort" << endl;
		    cout << endl << "Option: ";
		    cin >> c;
			if (c == 1 || c == 2)
			{
				sortchoice = c;//choose the sort method
			}
			else
			{
				cout << "Your choice is invalid." << endl;
			}
	
		    break;
		}
		case 8:
			return;
			break;
		default:
			cout << "Your input is invalid." << endl;
			break;
		}

	}
	
}

int main()
{
	int choice;
	//print the menu
	while (1) {
		cout << "\nWelcome to the Account Management System." << endl;
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cout << endl << "Option: ";
		cin >> choice;
		cout << endl;
		if (choice == 3)
			break;

		switch (choice)
		{
		case 1:
		{
			StockAccount a;
			stockmenu(&a);//call the menu of stock
			break;
		}
		case 2:
		{
			BankAccount bank;
			bankmenu(&bank);//call the menu of bank
			break;
		}
		default:
		{
			cout << "Your input is invalid. Try again." << endl;
			break;
		}
		}
	}
	return 0;
}
