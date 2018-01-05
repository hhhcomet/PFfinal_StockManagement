//
//StockAccount_RongZhang.cpp
//Final project by RongZhang
//
#define _CRT_SECURE_NO_DEPRECATE

//some definitions to use MATLAB
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include <engine.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include "StockAccount.h"
using namespace::std;

StockAccount::StockAccount()
	:Account()//use Account to initialize a stock account
{
	myHead = 0;
	myTail = 0;
	int n;
	string s;
	ifstream portfile("portfolio.txt", ios::in);
	if (!portfile.is_open())
		{
			ofstream newport("portfolio.txt");//if not this file, create one
		}
	while (portfile >> s >> n)//read the value from the file to create the list
	{
		Node *current = getnewNode(s, n);
		if (mySize == 0)
		{
			myHead = myTail = current;
		}
		else
		{
			current->leftPtr = myTail;
			myTail->rightPtr = current;
			myTail = current;//insert the node in the tail of the list
		}
		mySize++;
	}
	portfile.close();
}

StockAccount::~StockAccount()
{//delete all nodes from the list
	if (mySize != 0)
	{
		Node *current;
		Node *temp;
		current = myHead;

		while (current != 0)
		{
			temp = current;
			current = current->rightPtr;
			delete temp;
			--mySize;
		}
	}
}


double StockAccount::FindPrice(string symv)
{
	string sym_, date_;
	double price_=0.0;

	srand((unsigned)time(0));
	int choice;
	choice = rand() % 2;//choose a result file to read
	if (choice == 0)
	{
		ifstream stock("Result_1.txt", ios::in);
		if (!stock.is_open())
		{
			cout << "File can't be found." << endl;
			exit(1);
		}
		else
		{
			while (stock >> sym_ >> price_ >> date_)
			{
				if (symv == sym_)//the information match
				{
					return price_;
				}
			}
		}
	}
	else
	{
		ifstream stock("Result_2.txt", ios::in);
		if (!stock.is_open())
		{
			cout << "File can't be found." << endl;
			exit(1);
		}
		else
		{
			while (stock >> sym_ >> price_ >> date_)
			{
				if (symv == sym_)
				{
					return price_;
				}
			}
		}
	}
	
	return 0.0;
}


void StockAccount::BuyShare()
{
	string sym_;
	double price, maxprice, total;
	int num_;
	cout << "Please enter the stock symbol you wish to purchase:" << endl;
	cin >> sym_;//get the symbol name
	price = FindPrice(sym_);//find the price per share
	if (price == 0.0)
	{
		cout << "We can't find the stock." << endl;
		return;
	}

	cout << "Please enter the number of shares." << endl;
	cin >> num_;//get the numbers of the shares

	cout << "Please enter the maximum amount you are willing to pay per share: " << endl;
	cin >> maxprice;//get the maximum of the payment

	if (maxprice < price)
	{
		//Fail. The price is higher
		cout << "The amount of stock " << sym_ << " per share is " << price << ", which is more than the expected value." << endl;
		return;
	}

	total = num_*price;
	if (total > Account::cashbalance)
	{//Fail, not enough balance
		cout << "You don't have enough balance in the account." << endl;
		return;
	}

	Account::cashbalance = Account::cashbalance - total;

	bool added = 0;//check whether there is the same symbol
	if (mySize != 0)
	{
		Node *temp = myHead;
		while (temp != 0)
		{
			if (temp->symbol == sym_)
			{
				temp->number += num_;//the same, add the number
				added = 1;
			}
			temp = temp->rightPtr;
		}
	}
	
	Node *current = getnewNode(sym_, num_);
	if (added== 0)//not the same symbol exist, add a new node
	{
		if (mySize == 0)
		{
			myHead = myTail = current;
			mySize++;
			added = 1;
		}
		else {
			current->leftPtr = myTail;
			myTail->rightPtr = current;
			myTail = current;
			mySize++;
			added = 1;
		}
	}
	

	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);//generate time

	ofstream cash("cashbalance.txt");
	cash << Account::cashbalance << endl;//update the file of cash balance
	cash.close();

	ofstream stockfile("stock_transaction_history.txt", ios::app);
	stockfile << "Buy     " <<left<< setw(8) << sym_ << setw(14) << num_ << setw(14) <<  price << setw(12) <<  total << setw(30) << asctime(timeinfo) << endl;
	stockfile.close();//update the transaction file

	updateFiles();//update two more files

	ofstream bankfile("bank_transaction_history.txt", ios::app);
	bankfile << "Withdraw     $" << left << setw(12) << total << setw(30) << asctime(timeinfo) << endl;
	bankfile.close();// update the bankaccount history

	//buy successful
	cout << "You have purchase " << num_ << " shares of " << sym_ << " at " << price << " each for a total of " << total << ".\n";
}

void StockAccount::SellShare()
{
	string sym_;
	double price, minprice, total;
	int num_;

	if (mySize == 0)
	{
		cout << "There is no shares in your stock account." << endl;
		return;//no shares to sell
	}

	cout << "Please enter the stock symbol you wish to sell:" << endl;
	cin >> sym_;
	price = FindPrice(sym_);
	if (price == 0.0)
	{
		cout << "Can't find this stock." << endl;
		return;//can't find the block
	}

	cout << "Please enter the number of shares." << endl;
	cin >> num_;

	cout << "Please enter the minimum amount you are willing to sell per share: " << endl;
	cin >> minprice;
	if (minprice > price)
	{//Fail. the willing price is higher
		cout << "The amount of stock " << sym_ << " per share is " << price << ", which is less than the expected value." << endl;
		return;
	}

	total = num_*price;

	Node *current = myHead;
	while (current != 0)
	{
		if (current->symbol == sym_)
		{
			break;
		}
		current = current->rightPtr;
	}
	if (current == 0)
	{//Fail. no match symbol
		cout << "You don't have this symbol in your account." << endl;
		return;
	}
	else if (current->number < num_)
	{//Fail. not enough shares
		cout << "You don't have enough shares to sell." << endl;
		return;
	}
	else
	{
		current->number -= num_;
		Account::cashbalance += total;
		if (current->number == 0)
		{
			removeNode(sym_);//if there are 0 share, remove the node
		}
	}

	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);

	ofstream cash("cashbalance.txt");
	cash << Account::cashbalance << endl;
	cash.close();//update cash balance.txt

	ofstream stockfile("stock_transaction_history.txt", ios::app);//update the transaction history
	stockfile << "Sell    " << left << setw(8) << sym_ << setw(14) << num_ << setw(14) << price << setw(12) << total << setw(30) << asctime(timeinfo) << endl;

	updateFiles();//update two more files

	ofstream bankfile("bank_transaction_history.txt", ios::app);//update the bank history
	bankfile << "Deposit      $" << left << setw(12) << total << setw(30) << asctime(timeinfo) << endl;

	//sell successful.
	cout << "You have sell " << num_ << " shares of " << sym_ << " at " << price << " each for a total of " << total << ".\n";

}

void StockAccount::PrintHistory() const
{
	ifstream stockfile("stock_transaction_history.txt");
	if (!stockfile.is_open())
	{
		cout << "You have no bank transaction history." << endl;
	}
	else
	{
		cout << "Event   Symbol  Number        PricePerShare Totalvalue  Time"<< endl;
		string history;
		while (!stockfile.eof())
		{
			getline(stockfile, history);//read the data
			cout << history << endl;//print
		}
	}
	stockfile.close();
}


void StockAccount::removeNode(string &symv)
{
	if (mySize == 0)
	{
		cout << "This is a empty portfolio account." << endl;
	}
	else {
		Node *current = myHead;
		while (current != 0)
		{
			if (current->symbol == symv)//symbol match
			{
				if (current == myHead)
				{
					if (myHead == myTail)
					{
						myHead = myTail = 0;
						--mySize;
						return;
					}
					else {
						Node *temp1 = myHead;
						myHead = myHead->rightPtr;
						myHead->leftPtr = 0;
						delete temp1;
						--mySize;
						return;
					}
				}
				else if (current == myTail)
				{
					Node *temp2 = myTail;
					myTail = myTail->leftPtr;
					myTail->rightPtr = 0;
					delete temp2;
					--mySize;
					return;
				}
				else
				{
					Node *temp3 = current;
					current->leftPtr->rightPtr = current->rightPtr;
					current->rightPtr->leftPtr = current->leftPtr;
					delete temp3;
					--mySize;
					return;
				}
			}
			current = current->rightPtr;
		}
		cout << "This symbol is not in this list." << endl;//symbol match failed
	}
}

void StockAccount::DisplayPortfolio()
{
	cout << "Cash balance = $" << Account::cashbalance << endl;//print cash balance
	cout << "CompanySymbol Number    PricePerShare Totalvalue" << endl;
	double total, totalport, price;
	totalport = Account::cashbalance;
	Node* current = myHead;
	if (mySize == 0)
	{
		cout << "You don't have any shares in your stock account." << endl;
	}
	else {
		while (current != 0)
		{//print the symbol and totalvalue of the nodes
			price = FindPrice(current->symbol);
			total = price*current->number;
			totalport += total;//calculate total portfolio value
			cout <<setw(14)<<left<< current->symbol << setw(10) << current->number << setw(14)  << price << setw(14)  << total << endl;
			current = current->rightPtr;
		}
	}
	cout << "Total portfolio value: $" << totalport << endl;//print total portfolio value
}

void StockAccount::Sort(int sortchoice)
{//choose a sort method
	if (sortchoice == 1)
	{
		Bubblesort();
	}
	else if (sortchoice == 2)
	{
		Insertsort();
	}
}

void StockAccount::Bubblesort()//sort method 1: bubble sort
{
	int swapFlag;
	Node *current = myHead;
	double total1, total2;
	if (mySize == 0 && mySize == 1)// no or only one node
	{
		return;
	}
	Node *left = 0;
	Node *temp = 0;
	swapFlag = 0;

	for (int i = 0; i < mySize; i++)//loop mySize-1 time
	{
		while (current->rightPtr != 0) // checking if it is not a tail pointer
		{
			temp = current->rightPtr;
			total1 = getTotalvalue(current);
			total2 = getTotalvalue(temp);
			if (total1 < total2)
			{
				temp->leftPtr = current->leftPtr;
				current->leftPtr = temp;
				current->rightPtr = temp->rightPtr;
				swapFlag = 1;

				if (current->rightPtr != 0) 
					current->rightPtr->leftPtr = current;
				    temp->rightPtr = current;   
				if (left != 0)				  
					left->rightPtr = temp;  
				    left = temp;              
				if (myHead == current)       
					myHead = temp;
				if (current->rightPtr == 0)    
					myTail = current;
			}
			else
			{
				left = current;               
				current = current->rightPtr;  //the next loop
			}
		}
		if (swapFlag == 0) //check if the list is sorted
			break;
		else{//the next out loop
			left = 0;
			current = myHead;
			swapFlag = 0;
		}
	}
}


void StockAccount::Insertsort()//sort method 2: insert  ion sort
{
	int swapFlag;
	double total1, total2;
	Node *current;
	current = myHead;
	if (mySize == 0 && mySize == 1)// no or only one node
	{
		return;
	}

	Node *temp1, *temp2;
	current = current->rightPtr;//start from the next ptr
	while (current != 0)
	{
		swapFlag = 0;//in each loop, update swapFlag
		temp1 = current;
		temp2 = current->leftPtr;
		current = current->rightPtr;
		total1 = getTotalvalue(temp2);
		total2 = getTotalvalue(temp1);
		while (temp2 != 0 && total1<total2)
		{
			swapFlag =1;//need to swap
			temp2 = temp2->leftPtr;
		}
		if (swapFlag !=0)
		{
			temp1->leftPtr->rightPtr = temp1->rightPtr;
			if (temp1->rightPtr != 0)//if temp1=myTail
				temp1->rightPtr->leftPtr = temp1->leftPtr;
			if (temp2 == 0)
			{
				temp2 = myHead;
				temp1->leftPtr = 0;
				temp1->rightPtr = temp2;
				temp1->rightPtr->leftPtr = temp1;
				myHead = temp1;
			}
			else
			{
				temp2 = temp2->rightPtr;
				temp2->leftPtr->rightPtr = temp1;
				temp1->leftPtr = temp2->leftPtr;
				temp2->leftPtr = temp1;
				temp1->rightPtr = temp2;
			}
		}
	}
}

double StockAccount::getTotalvalue(Node *v)
{
	double price,total;
	price=FindPrice(v->symbol);
	total = price*v->number;
	return total;//get total value to sort the list
}

Node * StockAccount::getnewNode(string &symv, int &numv)
{
	return new Node(symv, numv);//get new node
}


void StockAccount::updateFiles()
{
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);

	double total, totalport, price;
	totalport = Account::cashbalance;
	Node* current = myHead;

	ofstream portfile("portfolio.txt");
	ofstream matlab("totalvalue.txt", ios::app);

	while (current != 0)
	{
		portfile << current->symbol << setw(10) << current->number << endl;//store the data of portfolio.
		price = FindPrice(current->symbol);
		total = price*current->number;
		totalport += total;
		current = current->rightPtr;
	}
	portfile.close();

	//when store totalvalue.txt, I separate the value of time to let it be easy to collect in the MATLAB part.
	matlab << 1900+timeinfo->tm_year<<setw(8)<<1+timeinfo->tm_mon<<setw(5) << 1+timeinfo->tm_mday<<setw(5)<<1+timeinfo->tm_hour<<setw(5)<<1+timeinfo->tm_min<<setw(5)<<1+timeinfo->tm_sec<<setw(20) << totalport << endl;
	matlab.close();
}

void StockAccount::ViewGraph()
{
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found" << endl;
		exit(1);
	}
	int y,m,da,h,mi,s;
	double v;
	double a[10000][6];
	double b[10000];
	int size = 0;
	ifstream matlab("totalvalue.txt", ios::in);
	if (!matlab.is_open())
	{
		cout << "File could not be opened." << endl;
		return;
	}
	while (matlab >>y>> m >> da >> h >> mi >> s>>v)//read the value of the file
	{
		a[size][0] = y;//year
		a[size][1] = m;//month
		a[size][2] = da;//days
		a[size][3] = h;//hour
		a[size][4] = mi;//minute
		a[size][5] = s;//second
		b[size] = v;//value
		size++;
	}
	if (mySize != 0)
	{
		mxArray *mx1;
		mxArray *mx2;
		mx1 = mxCreateDoubleMatrix(6, size, mxREAL);
		mx2 = mxCreateDoubleMatrix(1, size, mxREAL);
		memcpy((void *)mxGetPr(mx1), (void*)a, 6*sizeof(double)*size);
		memcpy((void *)mxGetPr(mx2), (void*)b, sizeof(double)*size);
		engPutVariable(ep, "A", mx1);
		engPutVariable(ep, "B", mx2);

		engEvalString(ep, "X=A';");
		engEvalString(ep, "a=X(:,1);b=X(:,2);c =X(:,3);d=X(:,4);e=X(:,5);f=X(:,6);");//get 6 separate matrix
		engEvalString(ep, "x=datenum(a,b,c,d,e,f);");//get datenum
		engEvalString(ep, "Y=B;");
		engEvalString(ep, "plot(x,Y,'-*');");//plot the graph
		//engEvalString(ep, "ylim([6000 12000]);");
		engEvalString(ep, "datetick('x',0);");//place datenum with time
		engEvalString(ep, "title('Plot of Total value of portfolio with time');");//title
		engEvalString(ep, "xlabel('Time'),ylabel('TotalValue');");//axis name

		engEvalString(ep, "pause(15.0);");//15 seconds to close the window

		engClose(ep);//close matlab engine	
	}
	return;
}








