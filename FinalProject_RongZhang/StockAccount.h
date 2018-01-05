//
//StockAccount.h
//Final project by Rong Zhang
//
#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include <string>
#include "Account.h"
#include "Node.h"
using std::string;

//Class StockAccount is derived from class Account. In this class, a double linked list is set up to store the 
//information of the portfolio.
class StockAccount :public Account
{
public:
	StockAccount();//constructor
	~StockAccount();//destructor
	double FindPrice(string);//return a price of stock
	void DisplayPortfolio();//display the current portfolio
	void BuyShare();//buy some shares
	void SellShare();//sell some shares

	//Let the user to choose a sort method, is a achievement of design pattern STRATEGY.
	//There are two methods of sorting the list, but the methods are hidden to the user.
	//The user can make a choice to choose the way they sort the list, but they can't access
	//the two methods.
	void Sort(int);//give the user a way to sort the list. 2 methods are provided.

	virtual void PrintHistory() const;//print the history of the list
	void updateFiles();//update two files 
	void ViewGraph();//use MATLAB to show the graph

private:
	Node *myHead;//head of the list
	Node *myTail;//tail of the list
	double getTotalvalue(Node*);//get total value of one node, used to sort the list
	int mySize;//the size of the list
	Node *getnewNode(string &, int &);//get a new node
	void removeNode(string &);//remove a node
	void Bubblesort();//sort method 1
	void Insertsort();//sort method 2
};
#endif


