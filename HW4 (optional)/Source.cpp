#include "DynamicStack.h"
#include <fstream>
using namespace std;

struct cellStruct
{
	char ch;
	bool isBlocked;
};

void fiilTheMatrix(cellStruct** &matrix, const int &row, const int &colm, ifstream &file)
{
	string line;
	int i = 0;
	while (getline(file, line))
	{
		for (unsigned int j=0; j < line.length(); j++)
		{
			matrix[i][j].ch = line.at(j);
			matrix[i][j].isBlocked = false;
		}
		i++;
	}
}

void ResetMatrix (cellStruct** &matrix, const int &row, const int &colm)
{
	for (int i=0; i < row; i++) {
		for (int j=0; j < colm; j++)
			matrix[i][j].isBlocked = false;
	}
}

void PrintMatrix (cellStruct** &matrix, const int &row, const int &colm)
{
	for (int i=0; i < row; i++) {
		for (int j=0; j < colm; j++)
			cout << matrix[i][j].ch << " ";
		cout << endl;
	}
}

void DeleteMatrix (cellStruct** &matrix, const int &row)
{
	for (int i=0; i < row; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void PrintStack (DynamicStack& stack)
{
	DynamicStack temp;
	string dummy;
	while (!stack.isEmpty())
	{
		stack.pop(dummy);
		temp.push(dummy);
	}

	while (!temp.isEmpty())
	{
		temp.pop(dummy);
		cout << dummy << " ";
	}
	cout << endl;
}

int main()
{
	string File_name, bits;
	ifstream file;
	unsigned int row, colm;

	cout << "Please enter the number of rows: ";
	cin >> row;
	cout << "Please enter the number of columns: ";
	cin >> colm;

	cellStruct** matrix = new cellStruct* [row];
	for (unsigned int i=0; i < row; i++)
		matrix[i] = new cellStruct[colm];

	
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> File_name;
	file.open(File_name.c_str());
	while (file.fail())
	{
		cout << "File cannot be opened.\nPlease enter the name of the input file again: ";
		cin >> File_name;
		file.open(File_name.c_str());
	}
	fiilTheMatrix(matrix, row, colm, file);

	DynamicStack stack;
	cout << endl << "Please enter a string of bits to search (CTRL+Z to quit): ";
	unsigned int current_row=0, current_colm=0, current_bit_index=0;
	bool isFound;
	while (cin >> bits)
	{
		int length = bits.length();
		/*PrintMatrix(matrix, row, colm);*/
		isFound = false;
		if (matrix[current_row][current_colm].ch != bits.at(current_bit_index))
			matrix[current_row][current_colm].isBlocked = true;

		while (matrix[0][0].isBlocked == false && !isFound)
		{
			/*#ifdef _DEBUG
				cout << "Index: " << current_row << "," << current_colm << " is being searched for " << bits.at(current_bit_index) << endl;
			#endif*/
			if (!matrix[current_row][current_colm].isBlocked && matrix[current_row][current_colm].ch == bits.at(current_bit_index))
			{
				stack.push("(" + to_string(current_row) + "," + to_string(current_colm) + ")");
				current_bit_index++;
				if (current_bit_index == bits.length())
					isFound = true;
				else if (current_colm+1 < colm && !matrix[current_row][current_colm+1].isBlocked)
					current_colm++;
				else if (current_row+1 < row && !matrix[current_row+1][current_colm].isBlocked)
					current_row++;
				else
				{
					matrix[current_row][current_colm].isBlocked = true;
					string backtrack;
					stack.pop(backtrack);
					current_row = backtrack.at(1) - '0';
					current_colm = backtrack.at(3) - '0';
					current_bit_index--;
				}
			}

			else if (matrix[current_row][current_colm].isBlocked || matrix[current_row][current_colm].ch != bits.at(current_bit_index))
			{
				matrix[current_row][current_colm].isBlocked = true;
				string backtrack;
				stack.pop(backtrack);
				current_row = backtrack.at(1) - '0';
				current_colm = backtrack.at(3) - '0';
				current_bit_index--;
			}
		}

		if (isFound)
		{
			cout << "The bit string " << bits << " is found following these cells:" << endl;
			PrintStack(stack);
		}
		if (matrix[0][0].isBlocked)
			cout << "The bit string " << bits << " could not be found." << endl;

		cout << "---------------------------------------------------------\nPlease enter a string of bits to search (CTRL+Z to quit): ";
		stack.~DynamicStack();
		ResetMatrix(matrix, row, colm);
		current_row=0, current_colm=0, current_bit_index=0;
	}
	
	
	DeleteMatrix(matrix, row);
	file.close();
	cout << "Program ended successfully!" << endl << endl;
	return 0;
}
