/* 
MazeWord
Erik Hale
12/15/20 : 12:10AM
The objective of this program is to make a maze that follows
specifications given to it by a file (files contents might
look like: "9 9" or "Name \n 9 9") and create a grid that size with a maze either
in that same document or a new one
Also it might be cool if there was another file that had a 
possible solution but not in the same file for ease of use

12/15:	Setup / Start of project
		Taking in input from files
*/
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

// Const and variables
const int MAX_GRID_SIZE = 500; // Hard set value, can be changed later
const string FILENAME = "infile.txt";
string nameOfFile; // The name of the file from the infile
int xDim = 0, yDim = 0; // the x and y dimensions

void newFileInfo() {
	cout << "NoF: \"" << nameOfFile << "\"" << endl;
	cout << "X Dim: " << xDim << endl;
	cout << "Y Dim: " << yDim << endl;
}

int main() {
	// Open the file and check to see if it's there
	fstream infile;
	infile.open(FILENAME);
	if (!infile) {
		// If the file isn't there, quit and warn user
		printf("Error, File does not exist\n");
		exit(-1);
	}

	// File is open, so now the program can read the contents
	// It should only be the file name and the grid dimensions
	string inputFromFile = "";
	getline(infile, inputFromFile); // Pull the name of the new file
	if (inputFromFile.find(" ")) {
		// Replace spaces with underscores if there are any
		for (int currPos = 0; currPos < inputFromFile.length(); currPos++) {
			if (inputFromFile.at(currPos) == ' ')
				inputFromFile.at(currPos) = '_';
		}
	}
	// if the string doesn't have a space then it is a valid filename
	nameOfFile = inputFromFile;
	// Take in the x and y dimensions for the new file
	infile >> xDim;
	infile >> yDim;
	newFileInfo(); // Display what the system should give back to the user

	infile.close();
	return 0;
}