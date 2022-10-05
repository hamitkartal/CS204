// Hamit Kartal 28404 hamit@sabanciuniv.edu
#include <sstream>
#include "Hamit_Kartal_Hamit_hw3_SubSeqsList_class.h"
using namespace std;

int main() {
	string line;
	int num;
	cout << "Please enter the numbers in a line: ";
	getline(cin, line);
	cout << endl << endl;
	istringstream stream(line);
	SubSeqsList main_list;
	while (stream >> num) {
		if (num >= 0)
			main_list.positive_input(num);
		else
			main_list.negative_input(num*-1);
	}
	cout << endl;
	main_list.contents();
	main_list.autolysis();
	return 0;
}