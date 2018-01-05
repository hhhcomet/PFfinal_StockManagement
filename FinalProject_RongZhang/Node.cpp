//
//Node_RongZhang.cpp
//Final project by RongZhang
//
#include "Node.h"

Node::Node(string &sym, int &num)//initialize the Node
		:symbol(sym), number(num)
	{
		this->leftPtr = NULL;
		this->rightPtr = NULL;
	}
