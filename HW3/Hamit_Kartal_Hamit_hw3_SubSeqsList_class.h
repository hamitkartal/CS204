#ifndef HAMIT_KARTAL_HAMIT_HW3_SUBSEQSLIST_CLASS_H
#define HAMIT_KARTAL_HAMIT_HW3_SUBSEQSLIST_CLASS_H

#include <iostream>
#include <string>
using namespace std;

struct SubSeqNode { 
	int value; 
	SubSeqNode * next; // constructors come here
	SubSeqNode() {}
	SubSeqNode(int x, SubSeqNode* ptr) {
		value = x;
		next = ptr;
	}
};

struct SubSeqHeadNode { 
	int size;			// number of elements in the subsequence 
	SubSeqNode * sHead; // head of the subsequence list 
	SubSeqHeadNode * next;  // constructors come here 
	SubSeqHeadNode() {}
	SubSeqHeadNode(int x, SubSeqNode* shead, SubSeqHeadNode* headnode) {
		size = x;
		sHead = shead;
		next = headnode;
	}
};

class SubSeqsList {
	public:
		SubSeqsList(); //default constructor that creates an empty list
		void positive_input(const int &); // does the necessary implementations for a positive input
		void negative_input(int); // does the necessary implementations for a negative input
		void contents();		  // shows the contents of the hHead
		void autolysis();		// destroys the whole hHead and dynamic allocated memories
	private:
		SubSeqHeadNode * hHead;
		void delete_subsequences_containing(int); // goes through the SubSeqHeadNodes and checks them (via does_it_exist_in linkedlist) if it contains the int itself
												 // if yes, then it deletes all SubSeqNodes (via delete_entire_linkedlist) and then deletes the corresponding SubSeqHeadNode
												 // then continues till to the last SubSeqHeadNode. at last it checks first SubSeqHeadNode, if it contains the int, then
												 // first SubSeqHeadNode and its single SubSeqnode is deleted, hHead is updated to the new first SubSeqHeadNode

		void delete_entire_linkedlist(SubSeqNode*); // copy of a head pointer of a linkedlist is given as parameter, function deletes all the nodes of the corresponding linkedlist

		void add_positive_input(const int &); // first it checks every subsequence 1by1 if they are OK to be copied (via is_OK_to_develop), if yes it copies the present
											  // subsequence and add the input at the end of clone-subsequence. then it sends the new-linkedlist to the spot_finder_and_placer
											  // to be placed. at the end of func, it creates a SubSeqHeadNode with size = 1 (contains the input alone) and places the correct place

		bool is_OK_to_develop(SubSeqNode*, const int &); // goes to the end of the given linkedlist and compares with the last value with given int (returns true/false)
														 // and determines if input is appendable to the current subsequence or not.

		void spot_finder_and_placer(SubSeqNode*, int); // it finds the interval where the new linkedlist should be placed (according to the size), then checks every possible places
													   // (via is_this_the_place), consequently it places the new linkedlist into hHead

		bool is_this_the_place(SubSeqNode*, SubSeqNode*, const int &); // compares the respective values of two given linkedlists, and determines if candidate linkedlist
																	   // should be placed before or after the linkedlist which is already in part of hHead, a.k.a other parameter

		bool does_it_exist_in_structure(const int &);	// checks if the input already exists in hHead, if yes --> returns true. if no --> returns false

		bool does_it_exist_in_linkedlist(SubSeqHeadNode*,int); // checks if the input alreadys exists (in order to be deleted afterwards), if yes --> returns true. if no --> returns false

		bool is_allocation_successful(SubSeqHeadNode*); // checks if dynamic memory allocation is succesfful. if not --> it terminates the program
		bool is_allocation_successful(SubSeqNode*);		// checks if dynamic memory allocation is succesfful. if not --> it terminates the program
};
#endif