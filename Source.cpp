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
#include <time.h>

using namespace std;

// Const and variables
const int MAX_GRID_SIZE = 500; // Hard set value, can be changed later
const string FILENAME = "infile.txt";
string nameOfFile; // The name of the file from the infile
int xDim = 0, yDim = 0; // the x and y dimensions
char field[MAX_GRID_SIZE * MAX_GRID_SIZE]; // We won't use all the spots
enum Directions { UP = 1, DOWN, LEFT, RIGHT };

// Functions
void newFileInfo() {
	cout << "NoF: \"" << nameOfFile << "\"" << endl;
	cout << "X Dim: " << xDim << endl;
	cout << "Y Dim: " << yDim << endl;
}

void setGridToZero(int xLim, int yLim) {
	// set the field to zero for all positions
	for (int pos = 0; pos < xLim * yLim; pos++) {
		field[pos] = '0';
	}
}

int translation(int xPos, int yPos) {
	// As the field is one dimensional, we need a function that moves it into 2D
	// This is row width times the current yPos and then adding xPos
	return yPos * yDim + xPos;
}

bool inField(int xPos, int yPos) {
	// As we have a variable field size we should check to see if the
	// x and y coords are in bounds of the field
	if ((xPos < 0 || xPos >= xDim) || (yPos < 0 || yPos >= yDim))
		return false;
	return true;
}

void printField(ostream& output) {
	// Print the grid in either a file or out to the console screen
	for (int yPos = 0; yPos < yDim; yPos++) {
		for (int xPos = 0; xPos < xDim; xPos++) {
			output << field[translation(xPos, yPos)];
		}
		output << endl;
	}
	// We would take out the beginning and the ends here
}

void goToPosition(int xPos, int yPos) {
	// At this position, we have to make it a space so that 
	// It can act like a path to a maze
	field[translation(xPos, yPos)] = ' ';

	// To connect the empty part of the field we can make a 
	// direction call, either UP, DOWN, LEFT, or RIGHT
	// We have to place these in a random order
	int direction[4];
	direction[0] = UP;
	direction[1] = DOWN;
	direction[2] = LEFT;
	direction[3] = RIGHT;

	for (int dir = 0; dir < 4; dir++) {
		// Change up the directions randomly
		int randNum = rand() % 4;
		int temporary = direction[randNum];
		direction[randNum] = direction[dir];
		direction[dir] = temporary;
	}

	// Now go to every direction and try to visit it
	for (int dir = 0; dir < 4; dir++) {
		int xNew = 0, yNew = 0; // The new positions of x and y
		switch (direction[dir]){
		case UP: 
			yNew = -1; 
			break;
		case DOWN:
			yNew = 1; 
			break;
		case LEFT:
			xNew = -1;
			break;
		case RIGHT:
			xNew = 1;
			break;
		}

		int x2 = xPos + (xNew << 1);
		int y2 = yPos + (yNew << 1);

		if (inField(x2, y2)) {
			if (field[translation(x2, y2)] == '0') {
				field[translation(x2 - xNew, y2 - yNew)] = ' ';

				goToPosition(x2, y2);
			}
		}
	}

}

int main() {
	srand(time(NULL)); // Make the numbers random

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

	// Clear the field and show an example
	setGridToZero(xDim, yDim);
	goToPosition(1, 1);
	printField(std::cout);

	infile.close();
	return 0;
}
