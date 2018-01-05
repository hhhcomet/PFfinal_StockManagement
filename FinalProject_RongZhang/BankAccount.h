//
//BankAccount.h
//Final project by Rong Zhang
//

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Account.h"

//Bankaccount is a derived class from Accoount. It inherits the function PrintHistory() and cashbalance.
class BankAccount : public Account {

    public:
		BankAccount();//contructor
		~BankAccount();//destructor
		void GetBalance();//show the balance of the account
		void Deposit();//deposit money
		void Withdraw();//withdraw money
		virtual void PrintHistory()const;//print the transaction history of bankaccount.

    private:
		double amount;
};

#endif