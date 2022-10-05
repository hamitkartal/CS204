#include "DynamicStack.h"
using namespace std;

DynamicStack::DynamicStack()
{
	top = NULL;
}

DynamicStack::~DynamicStack()
{
	StackNode* temp = top;
	while (top != NULL)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}

void DynamicStack::push(string str)
{
	if (top == NULL)
		top = new StackNode (str, NULL);
	else
		top = new StackNode(str, top);
}

void DynamicStack::pop(string &str)
{
	str = top->indice;
	StackNode* temp = top;
	top = top->next;
	delete temp;
}

bool DynamicStack::isEmpty() const
{
	return (top == NULL);
}