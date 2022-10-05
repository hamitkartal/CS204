#ifndef _DYNAMICSTACK_H
#define _DYNAMICSTACK_H

#include <iostream>
#include <string>
using namespace std;

struct StackNode
{
	string indice;
	StackNode* next;
	StackNode() {}
	StackNode(string str, StackNode* ptr): indice(str), next(ptr) {}
};

class DynamicStack
{
	public:
		DynamicStack();						// default constructor
		~DynamicStack();					// destructor
		void push(string);					// pushes int onto the top of the stack
		void pop(string&);					// pops the toppest element of the stack
		bool isEmpty() const;				// returns true if stack is empty, returns false if stack is not empty
	private:
		StackNode* top;
};
#endif