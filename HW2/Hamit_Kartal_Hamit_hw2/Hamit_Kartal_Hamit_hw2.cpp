// Hamit Kartal hamit@sabanciuniv.edu 28404
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool is_only_whitespace(const string & str) { 
// this function checks if the given string contains only whitespace characters
// if there is at least one non-whitespace character, it returns false
	for (int i=0; i < str.length(); i++) {
		if (str.at(i) != ' ' && str.at(i) != '\t') {
			return false; 
		}
	}
	return true;
}

struct node { // this struct is provided from homework file
	int value;
	node* next;
	node(){}
	node(int x, node* ptr) {
		value = x;
		next = ptr;
	}
};

/* Begin: code taken from ptrfunc.cpp and updated */
void DeleteOneNode (node* & toBeDeleted, node * & head) {
// this function deletes the node given as parameter
// and updates the head pointer and the one pointing to the deleted node
	node * ptr;
	if (toBeDeleted == head) { //if the node to be deleted is the first node
		head = head->next;
		delete toBeDeleted;
		toBeDeleted = head;
	}
	else { //if the node to be deleted is in the middle or at the end
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted
		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
		toBeDeleted = ptr;
	}
}
/* End: code taken from ptrfunc.cpp and updated */


void DeleteAll(node* &head) { // this function deletes all the nodes via the provided head pointer
	node* ptr = head;
	while (ptr != NULL) {
		head = head->next;
		cout << " " << ptr->value;
		delete ptr;
		ptr = head;
	}
}

/* Begin: code taken from ptrfunc.cpp and updated */
void DisplayList (node * head) {
// this function simply displays the content of the linkedlist via the provided head pointer
	cout << "List content: ";
	node* ptr = head;
    while (ptr != NULL) {
		cout << ptr ->value << " ";
		ptr = ptr->next;
	}
	cout << endl<<endl;
}
/* End: code taken from ptrfunc.cpp and updated */


/* Begin: code taken from ptrfunc.cpp and updated */
int existenceChecker_deleteSender (node* &head, int num, string order) {
// this function checks if the given value exists in the list, if yes -> then returns 0
// if no -> then goes through the list again and deletes nodes if it is necessary by the function DeleteOneNode

	node * ptr = head;
	bool flag = true;
    while (ptr != NULL) { // pointer (ptr) goes through the whole list
		if (ptr->value == num) // this is the when value exists in list, it returns 0 to the main()
			return 0;
		ptr = ptr->next;
	}
	ptr = head;
	cout << "Deleted nodes: ";
	if (order == "A") { // algorithm changes upon the order mode, this is the case order = 'A'
		while (ptr != NULL) {
			if (ptr->value > num) { // if there is a node containing value bigger than num, it is sent to be deleted to DeleteOneNode
				cout << ptr->value << " ";
				flag = false;
				DeleteOneNode(ptr, head);
			}
			else {
				ptr = ptr->next;
			}
		}
	}
	else { // algorithm changes upon the order mode, this is the case order = 'D'
		while (ptr != NULL) {
			if (ptr->value < num) { // if there is a node containing value smaller than num, it is sent to be deleted to DeleteOneNode
				cout << ptr->value << " ";
				flag = false;
				DeleteOneNode(ptr, head);
			}
			else {
				ptr = ptr->next;
			}
		}
	}
	if (flag) // flag was initiliazed true first, if there was a deletion from list it was changed to false
		cout << "None";
	cout << endl;
	return 1;
}
/* End: code taken from ptrfunc.cpp and updated */


int main() {
	/* here asks user to enter order mode untill user enters a valid one */
	string order_mode, numbers, str_number;
	int number;
	cout << "Please enter the order mode (A/D): ";
	cin >> order_mode;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	while (order_mode != "A" && order_mode != "D") {
		cout << "Please enter the order mode again (A/D): ";
		cin >> order_mode;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
	/* here asks user to enter order mode untill user enters a valid one */


	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);	
	cout << endl << endl;
	istringstream number_traveler(numbers);

	node * head = NULL;
	if (numbers == "" || is_only_whitespace(numbers)) // it checks if the number line is empty or contains only whitespace
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;

	else {
		while (number_traveler >> str_number) {
			number = stoi(str_number); // numbers in input line converted to the int type
			cout << "Next number: " << number << endl;
			if (existenceChecker_deleteSender(head, number, order_mode) == 0) 
				// here number is checked if it exists in list
				// if not, function also completes the deletion process itself
				cout << number << " is already in the list!" << endl;

			else if (head == NULL) { // if number is going to be inserted to the empty list
				head = new node(number, NULL);
				cout << "Appended: " << number << endl;
			}
			else { // number doesnt exist in the list and list is not empty
				node* temp = head;
				while (temp->next != NULL)
					temp = temp->next;
				node* tail = new node(number, NULL);
				temp->next = tail;
				cout << "Appended: " << number << endl;
			}
			DisplayList(head);
		}
		cout << "All the nodes are deleted at the end of the program:";
		DeleteAll(head);
		cout << endl << endl;
	}
	return 0;
}