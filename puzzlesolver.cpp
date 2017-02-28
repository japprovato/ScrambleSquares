#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>

using namespace std;

int squarecount = 9;

// reads lines and places them in 2D char array
// param: void
// return: pointer to char array containing squares
char **readLines() {
	int n = squarecount;
	string val;
	int linecount = 0;
	int valLength = 0;
	char **squares = new char*[squarecount];
	
	// add read from file code
	// should be while no EOF
	while(linecount < n){
		cin >> val;
		valLength = val.length();
		squares[linecount] = new char[9];
		// moves string input value to a char array
		for(int i=0,j=0; i < valLength; i++){
			if(val[i] != ','){
				squares[linecount][j++]= val[i];
			}
			if(j==8){
				//add square's index to end of array
				squares[linecount][j] = (to_string(linecount+1))[0];
			}
		}
		linecount++;
	}
	return squares;
}

// prints squares out in format:
// <cardNum>. <<top>, <right>, <bottom>, <left>>
// param: pointer to char array of squares
// return: void
void printInput(char **squares) {
	cout << "Input tiles:" << endl;
	for(int i=0; i < squarecount; i++){
		cout << squares[i][8] << ". ";
		cout << "<";
		cout << squares[i][0] << squares[i][1] << ", ";
		cout << squares[i][2] << squares[i][3] << ", ";
		cout << squares[i][4] << squares[i][5] << ", ";
		cout << squares[i][6] << squares[i][7] << ">" << endl;
	}
}

// prints one solution in ASCII art
// param: pointer to character array
// return: void
void printSingleSolution(char **squares) {
	for(int j=0; j < 9; j+=3){
		cout << "+--------+--------+--------+" << endl;
		for(int i=j; i < j+3; i++){
			cout << "|";
			cout << squares[i][8];
			cout << "  ";
			cout << squares[i][0] << squares[i][1];
			cout << "   ";
		}
		cout << "|" << endl;
		
		for(int i=j; i < j+3; i++){
			cout << "|";
			cout << squares[i][6] << squares[i][7];
			cout << "    ";
			cout << squares[i][2] << squares[i][3];
		}
		cout << "|" << endl;
		
		for(int i=j; i < j+3; i++){
			cout << "|   ";
			cout << squares[i][4] << squares[i][5];
			cout << "   ";
		}
		cout << "|" << endl;
	}
	cout << "+--------+--------+--------+" << endl;
}

// rotates a square clockwise once
// so that <A, B, C, D> becomes <D, A, B, C>
// param: pointer to char array of one square
char* rotateSquare(char* square){
	char temp[2] = {square[6], square[7]};
	square[7] = square[5];
	square[6] = square[4];
	square[5] = square[3];
	square[4] = square[2];
	square[3] = square[1];
	square[2] = square[0];
	square[1] = temp[1];
	square[0] = temp[0];
	return square;
}

// swaps position of two squares on board
// param: pointer to char array of all squares,
// param: index of squares to swap (not square number, index in array)
// return: char array of squares in new order
char** swapSquares(char **squares, int indexA, int indexB) {
	if(indexA > 8 || indexB > 8 || indexA < 0 || indexB < 0){
		return squares;
	}
	char* temp = squares[indexA];
	squares[indexA] = squares[indexB];
	squares[indexB] = temp;
	return squares;
}

// prints all solutions by calling printSingleSolution()
// param: solutions array of 2D char arrays, int number of solutions
// return: int (0)
int printSolutions(char ***solutions, int solutionSize){
	cout << endl;
	if(solutionSize == 0){
		cout << "No solution found." << endl;
		return 0;
	} else if(solutionSize == 1){
		cout << "1 unique solution found:" << endl;
	} else {
		cout << solutionSize << " unique solutions found:" << endl;
	}
	for(int i=0; i < solutionSize; i++){
		printSingleSolution(solutions[i]);
	}
	return 0;
}

int main() {
	
	char** squares;
	squares = readLines();
	printInput(squares);
	
	// find solutions
	// array of char** arrays (squares)
	
	// temp solution for testing prints
	char ***solutions = new char **[10];
	solutions[0] = squares;
	solutions[1] = swapSquares(squares, 0, 6);
	
	// print solutions
	printSolutions(solutions, 2);
	
	return 0;
}
