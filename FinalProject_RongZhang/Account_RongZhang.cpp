//
//Account_RongZhang.cpp
//Final project by Rong Zhang
//
#include "Account.h"
#include <iostream>
#include <fstream>
using namespace std;

Account::Account()
{
	ifstream cash("CashBalance.txt");//open the txt of storing cashbalance
	if (!cash.is_open())
	{
		cashbalance = 10000;// if not, initialize the cashbalance
	}
	else
		cash >> cashbalance;//read the cash balance from the file
}

void Account::PrintHistory()
{
	return;
}

double Account::cashbalance = 0.0;//definition of a static number