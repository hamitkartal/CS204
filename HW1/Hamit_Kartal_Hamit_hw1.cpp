// Hamit Kartal hamit@sabanciuniv.edu 28404

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/*
************************************************************
matrixDisplayer function simply displays the
elements of the given matrix in a matrixic way
*/

void matrixDisplayer (const vector<vector<char>>& matrix){
	for (int i=0; i < matrix.size(); i++){
		for (int j=0; j < matrix[i].size(); j++){
			cout << matrix[i][j] << "\t";
		}
		cout << endl << endl;
	}
}
/*
************************************************************
*/

bool cclockwise(vector<vector<char>>& matrix, int& row, int& colm, string direction, const char& ch){
	/*
	Basic logic is, for any letter we need to check for if 4 directions (right-left-up-down) are available or not.
	We begin to check with the given direction and orient with the given orientation in case the current direction is not available.
	If 4 directions are not available, then we cannot place the letter and cancel the word and not try the next letters.
	If we somehow manage to place the letter, we continue to implement the algorithm on next letters.
	Further explanation is provided along the algorithm

	NOTE: cclockwise and clockwise functions work in same way so I didn't provide any explanation for clockwise func. Everything I wrote
	here also hold for that func.
	*/

	// these flag boolean expressions express the availability of the corresponding directions
	// if any of them is false, it means that corresponding direction was tried and it is not available
	bool flag1 = true; // stands for the direction 'r'
	bool flag2 = true; // stands for the direction 'u'
	bool flag3 = true; // stands for the direction 'l'
	bool flag4 = true; // stands for the direction 'd'
	// there is no correlation with flag number and the direction


	while (true){ // either the letter is put successfully or not, this while loop is never executed infinitely

		if (flag1 == true && direction == "r" && colm+1 < matrix[0].size() && matrix[row][colm+1] == '-'){  // here it is checked if direction 'r' is available when the current one is 'r'
			matrix[row][colm+1] = ch;																		// here the letter is placed
			colm++;																							// the current index is updated
			return true;																					// true is returned to the main() to try the next letter
		}
		else if (flag1 == true && direction == "r"){ // current direction 'r' is inavailable and 
			direction = 'u';						// direction is oriented according to the orientation
			flag1 = false;							// here we close the direction 'r', it is checked one time and it is not going to be checked again neither in if statement nor in else-if
		}

		if (flag2 == true && direction == "u" && row-1 != -1 && matrix[row-1][colm] == '-'){   // here it is checked if direction 'u' is available when the current one is 'u'
			matrix[row-1][colm] = ch;															// here the letter is placed
			row--;													    						// the current index is updated
			return true;										     							// true is returned to the main() to try the next letter
		}
		else if (flag2 == true && direction == "u"){  // current direction 'u' is inavailable and 
			direction = 'l';						// direction is oriented according to the orientation
			flag2 = false;							// here we close the direction 'u', it is checked one time and it is not going to be checked again neither in if statement nor in else-if
		}

		if (flag3 == true && direction == "l" && colm-1 != -1 && matrix[row][colm-1] == '-'){   // here it is checked if direction 'l' is available when the current one is 'l'
			matrix[row][colm-1] = ch;															// here the letter is placed
			colm--;																				// the current index is updated
			return true;																		// true is returned to the main() to try the next letter
		}
		else if (flag3 == true && direction == "l"){  // current direction 'l' is inavailable and 
			direction = 'd';						// direction is oriented according to the orientation
			flag3 = false;							// here we close the direction 'l', it is checked one time and it is not going to be checked again neither in if statement nor in else-if
		}

		if (flag4 == true && direction == "d" && row+1 < matrix.size() && matrix[row+1][colm] == '-'){   // here it is checked if direction 'd' is available when the current one is 'd'
			matrix[row+1][colm] = ch;																	// here the letter is placed
			row++;																						// the current index is updated
			return true;																				// true is returned to the main() to try the next letter
		}
		else if (flag4 == true && direction == "d"){  // current direction 'd' is inavailable and 
			direction = 'r';						// direction is oriented according to the orientation
			flag4 = false;							// here we close the direction 'd', it is checked one time and it is not going to be checked again neither in if statement nor in else-if
		}

		if (flag1 == false && flag2 == false && flag3 == false && flag4 == false) { // this is the case that 4 directions are inavailable, it returns false and 
			return false;															// stops the function immediately, programme will do what needs to be done
		}
	}
}

bool clockwise(vector<vector<char>>& matrix, int& row, int& colm, string direction, const char& ch){
	// For explanation, please go to cclockwise function
	bool flag1 = true;
	bool flag2 = true;
	bool flag3 = true;
	bool flag4 = true;
	while (true){
		if (flag1 == true && direction == "r" && colm+1 < matrix[0].size() && matrix[row][colm+1] == '-'){
			matrix[row][colm+1] = ch;
			colm++;
			return true;
		}
		else if (flag1 == true && direction == "r"){
			direction = 'd';
			flag1 = false;
		}

		if (flag4 == true && direction == "d" && row+1 < matrix.size() && matrix[row+1][colm] == '-'){
			matrix[row+1][colm] = ch;
			row++;
			return true;
		}
		else if (flag4 == true && direction == "d"){
			direction = 'l';
			flag4 = false;
		}

		if (flag3 == true && direction == "l" && colm-1 != -1 && matrix[row][colm-1] == '-'){
			matrix[row][colm-1] = ch;
			colm--;
			return true;
		}
		else if (flag3 == true && direction == "l"){
			direction = 'u';
			flag3 = false;
		}
		
		if (flag2 == true && direction == "u" && row-1 != -1 && matrix[row-1][colm] == '-'){
			matrix[row-1][colm] = ch;
			row--;
			return true;
		}
		else if (flag2 == true && direction == "u"){
			direction = 'r';
			flag2 = false;
		}

		if (flag1 == false && flag2 == false && flag3 == false && flag4 == false) {
			return false;
		}
	}
}



int main(){
	/*
	**************************************************************************************
	In this part, I prompt a file name from user
	user enters a string and I assign that string in variable File
	I create an ifstream object named file and open it
	I check if it's opened successfully with .fail() function
	and prompt a file name again and again until user enter a valid name
	once the user enters a valid file name, program continues
	**************************************************************************************
	*/
	string File;
	cout << "Please enter the name of the file: ";
	cin >> File;
	ifstream file;
	file.open(File.c_str());
	while (file.fail()){
		cout << "File name is incorrect, please enter again: ";
		cin >> File;
		file.open(File.c_str());
	}

	cout << endl << endl;


	/*
	*********************************************************************************************************************************************
	Every test file begins with two integers in the very first line
	First integer represents the number of rows in matrix
	and second one represents the number of columns in matrix

	first integer is stored in variable mat_row
	second integer is stored in variable mat_row
	and I create a 2D matrix (vector of vector of char) with 
	a default value '-' unless integers are invalid, in that case program terminates
	
	While putting a word letter by letter onto the matrix, if a word is failed to be
	put onto the matrix, it is needed to unplace the previous letters of the word and
	unlikely the placing process, unplacing process would be more vulnerable to make a
	mistake. In order to prevent those, I created a temporary matrix (temp_matrix).
	I will start to put the letter onto the temp_matrix, if word is put successfully I will
	assign temp_matrix to the main matrix <matrix = temp_matrix>. But if word is failed at
	some point, I will assign main matrix to the temp_matrix in order to clear temp_matrix <temp_matrix = matrix>.
	This copy-matrix may allocate more memory rather than using one&main matrix and doing placing&unplacing algorithm
	on that matrix but this copy-matrix blocks many possible mistakes and it is much safer.

	then program continues to read the text file line by line
	*********************************************************************************************************************************************
	*/
	int mat_row, mat_colm;
	file >> mat_row >> mat_colm;
	if (mat_row < 0 || mat_colm < 0){
		cout << "Invalid number for row and/or column!" << endl;
		return 0;
	}
	vector < vector<char> > matrix(mat_row, vector<char>(mat_colm, '-'));
	vector < vector<char> > temp_matrix(mat_row, vector<char>(mat_colm, '-'));
	



	string line, word, orientation, direction;
	int row, colm, start_row, start_colm;

	file.ignore();
	while (getline(file, line)){

		/* 
		************************************************************
		This part simply checks if line has exactly 5 inputs
		************************************************************
		*/
		istringstream input(line), input2(line);
		string trash;
		int input_value_counter = 0;
		while (input >> trash) {
			input_value_counter++;
		}
		
		if (input_value_counter != 5) {
			cout << "Invalid line! Number of value is different than 5." << endl;
			
			continue;
		}

		input2 >> word >> start_row >> start_colm >> direction >> orientation; // reading the line which has valid number of inputs

		row = start_row;		// while putting the letters, I will need to update the current indexes for the next letter
		colm = start_colm;		// however, I also need the starting indexes specifically, because whether the word is successful or not, I will print starting indexes
								// so, starting indexes (start_row & start_colm) are stored in order to be printed for the informative sentence
								// and row & colm will be updated throughout the process for the next word


		bool line_success = true; // this boolean expression tells us if the current word is put onto the matrix successfully or not
								// so I can print relative sentence (word was put/couldn't be put)

		if (row < 0 || row >=mat_row || colm < 0 || colm >= mat_colm){							// here I check if the starting point is valid or not
			cout << "Starting point is out of range! Point: " << row << "," << colm << endl; // it prints that starting index is not valid
			continue;																			// and it jumps to the next line in file
		}

		else if (direction != "r" && direction != "l" && direction != "u" && direction != "d"){ // here I check if the direction is valid or not
			cout << "Invalid input for direction! Direction: " << direction << endl;			// it prints that direction is not valid
			continue;																			// and it jumpts to the next line in file
		}

		else if (orientation != "CW" && orientation != "CCW"){									// I check if the orientation is valid or not
			cout << "Invalid input for orientation! Orientation: " << orientation << endl;		// it prints that orientation is not valid
			continue;																			// and it jumps to the next line in file
		}


		if (temp_matrix[row][colm] == '-'){			// it checks if the starting point is empty to begin with the word to place

			temp_matrix[row][colm] = word.at(0);	// first letter is put

			for (int i=1; i < word.length(); i++) { // it begins to the loop by the first letter

				if ( orientation == "CW") { // my algorithm runs differently according to the orientation so here I check the orientation
					line_success = clockwise(temp_matrix, row, colm, direction, word.at(i)); // my clockwise algorithm runs and returns true if letter is put or returns false if letter cannot be put
					if (line_success) // if line_success true (if letter is put successfully), I continue to for loop
						continue;
					else // if any letter of the word fails, then we need to stop to try the next letters
						break; // programme clears the failed letter from matrix itself later since line_success is false, we can just break the for loop here
				}
				else {
					line_success = cclockwise(temp_matrix, row, colm, direction, word.at(i)); // my Counter-clockwise algorithm runs and returns true if letter is put or returns false if letter cannot be put
					if (line_success) // if letter is put onto the matrix successfully we can continue to the for loop
						continue;
					else  // algorithm failed at any letter, then we need to break the for loop, programme will clear the failed letters from matrix itself
						break;
				}
			}

		}

		else {  // here it means that starting point is inavailable, so we update line_success and assign false to it
			line_success = false;
		}

		if (line_success) {  // it means that line has valid inputs and it could be put onto the matrix, here I update the main matrix and print the informative sentence
			matrix = temp_matrix;
			cout << "\"" << word << "\"" << " was put into the matrix with given starting point: " << start_row << "," << start_colm << " direction: " << direction << " orientation: " << orientation << endl;
		}

		else {     // it means that line has invalid inputs but it couldn't be put onto the matrix, here I print the informative sentence and correct the temp_matrix
			temp_matrix = matrix;
			cout << "\"" << word << "\"" << " could not be put into the matrix with given starting point: " << start_row << "," << start_colm << " direction: " << direction << " orientation: " << orientation << endl;
		}
		matrixDisplayer(matrix); // if program comes here, it means line has valid inputs and it is tried to be put, despite the success of the line we should print the current matrix before the next line
		cout << endl << endl;
	}

	file.close();
	return 0;
}