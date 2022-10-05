#include "Hamit_Kartal_Hamit_hw3_SubSeqsList_class.h"
using namespace std;

SubSeqsList::SubSeqsList() { // default constructor
	hHead = NULL;
}

void SubSeqsList::positive_input(const int &input) { // first positive input func, checks if it exists in list, if not then send the int to another func to be added
	if (does_it_exist_in_structure(input))
		cout << input << " is already in the list!" << endl;
	else
		add_positive_input(input);
}

bool SubSeqsList::does_it_exist_in_structure(const int &num) { // it checks if given int exists in the list, returns true/false
	SubSeqHeadNode* sequence_pointer = hHead;
	while (sequence_pointer != NULL && sequence_pointer->size == 1) {
		if (sequence_pointer->sHead->value == num)
			return true;
		sequence_pointer = sequence_pointer->next;
	}
	return false;
}

void SubSeqsList::add_positive_input(const int &num) {
	cout << "Subsequence(s) containing " << num << " has/have been added" << endl;
	if (hHead == NULL) {
		SubSeqNode* ptr = new SubSeqNode(num, NULL);
		is_allocation_successful(ptr);
		SubSeqHeadNode* ptr2 = new SubSeqHeadNode(1, ptr, NULL);
		is_allocation_successful(ptr2);
		hHead = ptr2;
	}

	else {
		SubSeqHeadNode* seq_head_pointer = hHead;
		while (seq_head_pointer != NULL) {
			if (is_OK_to_develop(seq_head_pointer->sHead, num)) {
				SubSeqNode* will_be_copied = seq_head_pointer->sHead;
				SubSeqNode* will_be_merged = new SubSeqNode(will_be_copied->value, NULL);
				is_allocation_successful(will_be_merged);
				SubSeqNode* tail = will_be_merged;
				will_be_copied = will_be_copied->next;
				while (will_be_copied != NULL) {
					SubSeqNode* temp = new SubSeqNode(will_be_copied->value, NULL);
					is_allocation_successful(temp);
					tail->next = temp;
					tail = tail->next;
					will_be_copied = will_be_copied->next;
				}
				tail-> next = new SubSeqNode(num, NULL);
				is_allocation_successful(tail->next);
				spot_finder_and_placer(will_be_merged, seq_head_pointer->size+1);
			}
			seq_head_pointer = seq_head_pointer->next;
		}

		SubSeqNode* new_list = new SubSeqNode(num, NULL);
		if (hHead->sHead->value > num) {
			hHead = new SubSeqHeadNode(1, new_list, hHead);
			is_allocation_successful(hHead);
			}
		else {
			SubSeqHeadNode* subseq_headnode = hHead;
			while (subseq_headnode->next->size != 2 && subseq_headnode->next->sHead->value < num)
				subseq_headnode = subseq_headnode->next;
			 subseq_headnode->next = new SubSeqHeadNode(1, new_list, subseq_headnode->next);
			 is_allocation_successful(subseq_headnode->next);
		}
	}
}

bool SubSeqsList::is_OK_to_develop(SubSeqNode* ptr, const int &num) {
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr->value < num);
}

void SubSeqsList::spot_finder_and_placer(SubSeqNode* new_list_head, int new_list_size) {
	SubSeqHeadNode* subseq_headnode = hHead;
	while (subseq_headnode->next != NULL && subseq_headnode->next->size < new_list_size)
		subseq_headnode = subseq_headnode->next;
	if (subseq_headnode->next == NULL) {
		subseq_headnode->next = new SubSeqHeadNode(new_list_size, new_list_head, NULL);
		is_allocation_successful(subseq_headnode->next);
	}
	else {
		do {
			if ( is_this_the_place(subseq_headnode->next->sHead, new_list_head, new_list_size) ) {
				subseq_headnode->next = new SubSeqHeadNode(new_list_size, new_list_head, subseq_headnode->next);
				is_allocation_successful(subseq_headnode->next);
				return;
			}
			else
				subseq_headnode = subseq_headnode->next;
		}while (subseq_headnode->next != NULL && subseq_headnode->next->size == new_list_size);
		subseq_headnode->next = new SubSeqHeadNode(new_list_size, new_list_head, subseq_headnode->next);
		is_allocation_successful(subseq_headnode->next);
	}
}

bool SubSeqsList::is_this_the_place(SubSeqNode* this_one_is_in_hHead, SubSeqNode* this_one_is_candidate, const int &repeat) {
	do {
		if (this_one_is_in_hHead->value > this_one_is_candidate->value)
			return true;
		else {
			this_one_is_in_hHead = this_one_is_in_hHead->next;
			this_one_is_candidate = this_one_is_candidate->next;
		}
	} while (this_one_is_candidate != NULL);
	return false;
}

void SubSeqsList::autolysis() { // it deletes the entire list
	SubSeqHeadNode* sequence_pointer = hHead;
	while (sequence_pointer != NULL) {
		SubSeqNode* node_pointer = sequence_pointer->sHead;
		delete_entire_linkedlist(node_pointer);
		hHead = hHead->next;
		delete sequence_pointer;
		sequence_pointer = hHead;
	}
}

void SubSeqsList::contents() {
	cout << endl << "FINAL CONTENT";
	if (hHead == NULL)
		cout << endl << "List is empty!" << endl;
	else {
		SubSeqHeadNode* subseqhead_ptr = hHead;
		while (subseqhead_ptr != NULL) {
			SubSeqNode* subseq_ptr = subseqhead_ptr->sHead;
			cout << endl << subseqhead_ptr->size << " | " << subseq_ptr->value;
			subseq_ptr = subseq_ptr->next;
			while (subseq_ptr != NULL) {
				cout << " --> " << subseq_ptr->value;
				subseq_ptr = subseq_ptr->next;
			}
			subseqhead_ptr = subseqhead_ptr->next;
		}
	}
	cout << endl << endl;
}

void SubSeqsList::negative_input(int num) { // first negative input func, checks if it exists in list, if not then send the int to another func to delete all subsequences
	if (!does_it_exist_in_structure(num))
		cout << "There is no subsequence that contains " << num << " to be deleted" << endl;
	else 
		delete_subsequences_containing(num);
}

bool SubSeqsList::does_it_exist_in_linkedlist(SubSeqHeadNode* subseq_head_ptr, int num) {
	SubSeqNode* subseq_ptr = subseq_head_ptr->sHead;
	while (subseq_ptr != NULL) {
		if (subseq_ptr->value == num)
			return true;
		subseq_ptr = subseq_ptr->next;
	}
	return false;
}

void SubSeqsList::delete_entire_linkedlist(SubSeqNode* subseq_ptr) {
	SubSeqNode* delete_this = subseq_ptr;
	while (subseq_ptr != NULL) {
		subseq_ptr = delete_this->next;
		delete delete_this;
		delete_this = subseq_ptr;
	}
}

void SubSeqsList::delete_subsequences_containing(int num) { // it deletes all subsequences containing the given int // BU FONKSÝYONU BÝTÝRDÝÐÝNDE NEGATÝF ÝNPUTLARIN ÝÞÝ BÝTÝYOR
	cout << "All subsequence(s) containing " << num << " has/have been deleted" << endl;
	SubSeqHeadNode* subseq_head_ptr = hHead;
	while (subseq_head_ptr != NULL && subseq_head_ptr->next != NULL) {
		if (does_it_exist_in_linkedlist(subseq_head_ptr->next, num)) {
			delete_entire_linkedlist(subseq_head_ptr->next->sHead);
			SubSeqHeadNode* delete_this = subseq_head_ptr->next;
			subseq_head_ptr->next = delete_this->next;
			delete delete_this;
		}
		else
			subseq_head_ptr = subseq_head_ptr->next;
	}
	
	subseq_head_ptr = hHead;
	if (does_it_exist_in_linkedlist(subseq_head_ptr, num)) {
		delete_entire_linkedlist(subseq_head_ptr->sHead);
		hHead = hHead->next;
		delete subseq_head_ptr;
	}
}

bool SubSeqsList::is_allocation_successful(SubSeqHeadNode* ptr) {
	if (ptr == NULL) {
		cout << "Memory allocation is failed. Program is being terminated..." << endl;
		exit(0);
	}	
}

bool SubSeqsList::is_allocation_successful(SubSeqNode* ptr) {
	if (ptr == NULL) {
		cout << "Memory allocation is failed. Program is being terminated..." << endl;
		exit(0);
	}
}