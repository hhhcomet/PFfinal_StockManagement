//
//Account.h
//Final project by Rong Zhang
//

#ifndef ACCOUNT_H
#define ACCOUNT_H

//Use virtual function and polymorphism to achieve design pattern TEMPLATE.
//Bank account and stock account are derived from class Account, and they share the same constructor ACCOUNT() and
//have different functions in same name PrintHistory(). They also share the cashbalance to build their account separately.
class Account {
public:
	Account();//constructor
	virtual void PrintHistory();//a virtual function and initialized by 0.

protected:
	static double cashbalance;//the cashbalance and the two account will share this balance.
};

#endif

