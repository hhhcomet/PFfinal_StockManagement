//
//BankAccount_RongZhang.cpp
//Final project by RongZhang
//

#define _CRT_SECURE_NO_DEPRECATE
#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include "BankAccount.h"
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::setw;
using std::left;
using std::string;

BankAccount::BankAccount()
	: Account()
{
	amount = 0;//Use account to initiate a Bankaccount.
}

BankAccount::~BankAccount()
{
}

void BankAccount::GetBalance() 
{
	cout << "Your balance is $" << Account::cashbalance << endl<<endl;//print the cashbalance
}

void BankAccount::Deposit()
{
	cout << "Please input the amount of the money you want to deposit." << endl;
	cin >> amount;
	if (amount <= 0)
	{
		cout << "You input the invalid value." << endl;
		return;
	}
	else 
	{
		time_t seconds;
		seconds = time(NULL);
		tm * timeinfo;
		timeinfo = localtime(&seconds);//generate the time

		ofstream bankfile("bank_transaction_history.txt", ios::app);
		bankfile << "Deposit      $" <<left<<setw(12)<< amount <<setw(30) << asctime(timeinfo) << endl;//store the history
		
		ofstream cash("cashbalance.txt");
		Account::cashbalance = Account::cashbalance + amount;
		cash << Account::cashbalance << endl;//store the cashbalance

		cash.close();
		bankfile.close();

		cout << "You have deposit $" << amount << " successfully." << endl << endl;//deposit successful
	}
}

void BankAccount::Withdraw()
{
	cout << "Please input the amount of the money you want to withdraw." << endl;
	cin >> amount;
	if (amount > Account::cashbalance)
	{
		cout << "Sorry. You don't have enough money to withdraw." << endl;
		return;
	}
	else if (amount <= 0)
	{
		cout << "You input the invalid value." << endl;
		return;
	}
	else
	{
		time_t seconds;
		seconds = time(NULL);
		tm * timeinfo;
		timeinfo = localtime(&seconds);

		ofstream bankfile("bank_transaction_history.txt", ios::app);//store the history
		bankfile << "Withdraw     $" << left << setw(12) << amount  << setw(30) << asctime(timeinfo) << endl;
		
		ofstream cash("cashbalance.txt");
		Account::cashbalance = Account::cashbalance - amount;
		cash << Account::cashbalance << endl;//store the cash balance to the file
		cash.close();
		bankfile.close();
		cout << "You have withdraw $" << amount << " successfully." << endl << endl;//successful
	}
}

void BankAccount::PrintHistory() const
{
	ifstream bankfile("bank_transaction_history.txt");
	if (!bankfile.is_open())
	{
		cout << "You have no bank transaction history." << endl;
	}
	else
	{
		cout << "Event        Amount       Date" << endl << endl;;
		string history;
		while (!bankfile.eof())
		{
			getline(bankfile, history);//read the data of the file
			cout << history << endl;//print.
		}
	}
	bankfile.close();
	cout << endl;
}





