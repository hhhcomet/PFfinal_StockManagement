//
//Node.h
//Final project by Rong Zhang
//
#ifndef NODE_H
#define NODE_H

#include <string>
using std::string;

//Class Node is used to build a doubly linked list in Stockaccount.
class Node
{
	friend class StockAccount;//can be accessed by stockaccount

public:
	Node(string &, int &);//constructor

private:
	int number;
	string symbol;
	Node *leftPtr;
	Node *rightPtr;
};

#endif
