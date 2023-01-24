/*
 * Amy Saad
 * File: main.cpp
 *
 * Program to recursively map out all the paths in a given cave
 *
 * Class: Cave
 *
 * Methods:
 * void displayCave();  // method to display the cave from input file
 * void searchPath();   // method to search for path in the cave
 * void displayPath();  // method to display the path in the cave
 * int numDeadEnds();   // method to find the number of dead ends
 * void ReadFileHelper(ifstream& inputFile, int CurrentRow, int
CurrentColumn);   // method to help read file without loops
 * void ReadFile();  // method to read file
 * void TheGrid(int Row, int Column);  // method to initialize SpotVisited array
 * bool IsSpotValid(short Row, short Column) const;  // method to check if spot in cave is a valid spot
 * void DisplayCaveHelper(int Row, int Column);  // method to display cave grid
 * void FindPathInCave(short Row, short Column);  // method to find path in cave
 * void DisplayPathHelper(int Row, int Column);  // method to display path from cave
 * bool SpotVisited[NumOfRows][NumOfColumns];  // method to check if spot in cave was visited
 *
 * Input: User input of a file, with the first line containing
 * two integers representing the number of rows and columns, where
 * the max number of rows and columns is 50
 *
 * Output: The output print the initial grid from the file,
 * following with the paths found in the cave. The '0' indicating
 * a path, and an empty space indicating the blockage. Following
 * should be the number of dead ends in the cave
 */

#include <iostream>
#include <fstream>
using namespace std;

const int NumOfRows = 50;
const int NumOfColumns = 50;
// Maximum number of rows
// Maximum number of columns

char Grid[NumOfRows][NumOfColumns];
int NumOfRowsFromFile;
int NumOfColumnsFromFile;
// 2D array for file input
// Integer to store number of rows
// Integer to store number of columns

int StartOfRow;
int StartOfColumn;

class Cave {
public:
    Cave();  // Constructor
    void displayCave();  // Method to display the cave from input file
    void searchPath();  // Method to search for path in the cave
    void displayPath();  // Method to display the path in the cave
    int numDeadEnds();  // Method to find the number of dead ends

private:
    void ReadFileHelper(ifstream& inputFile, int CurrentRow, int CurrentColumn);  // Method to help read file without loops
    void ReadFile();  // Method to read file
    void TheGrid(int Row, int Column);  // Method to initialize SpotVisited array
    bool IsSpotValid(short Row, short Column) const;  // Method to check if spot in cave is a valid spot
    int NumOfDeadEnds;  // Integer to store the number of dead ends
    void DisplayCaveHelper(int Row, int Column);  // Method to display cave grid
    void FindPathInCave(short Row, short Column);  // Method to find path in cave
    void displayPathHelper(int Row, int Column);  // Method to display path from cave
    bool SpotVisited[NumOfRows][NumOfColumns];  // Method to check if spot in cave was visited
};

Cave::Cave() {
    ReadFile();  // Calls read file method
    NumOfDeadEnds = 0;  // Initializes number of dead ends to 0
    TheGrid(0,0);  // Initializes SpotsVisited array with 0
}

void Cave::ReadFileHelper(ifstream& inputFile, int CurrentRow, int CurrentColumn) {
    if (CurrentRow == NumOfRowsFromFile) {
        // If current row is the max number of rows
        return;
    }
    if (CurrentColumn == NumOfColumnsFromFile) {
        // If current row is the max number of rows
        ReadFileHelper(inputFile, CurrentRow + 1, 0);  // Calls readFileHelper method with next row, and sets column to 0
        return;
    }
    inputFile >> Grid[CurrentRow][CurrentColumn];  // Calls readFileHelper assigns to spot on grid
    ReadFileHelper(inputFile, CurrentRow, CurrentColumn + 1);  // Calls readFileHelper method with same row and next column
}

void Cave::ReadFile() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    ifstream inputFile(fileName);  // Opens file

    if (inputFile.is_open()) {  // If file is open
        inputFile >> NumOfRowsFromFile >> NumOfColumnsFromFile;  // Reads number of rows and columns from file
        ReadFileHelper(inputFile, 0, 0);  // Calls readFileHelper method
        inputFile.close();  // Closes
    } else {
        cout << "Hmmmm... can't open file...";  // Error message for invalid file entry
    }
}

void Cave::TheGrid(int Row, int Column) {
    if ((Row < NumOfRows) and (Column < NumOfColumns)) {
        // If current row is less than max rows and current column is less than max columns
        SpotVisited[Row][Column] = false;  // False for current spot
        if (Column == NumOfColumns - 1) {
            // One less than max column
            TheGrid(Row + 1, 0);  // Calls TheGrid method for next row at column 0
        } else {
            TheGrid(Row, Column + 1);  // Next column in same row
        }
    }
}

bool Cave::IsSpotValid(short Row, short Column) const {
    if ((Row < 0) or (Row >= NumOfRowsFromFile) or (Column < 0)
        // Spot is not within the cave
        or (Column >= NumOfColumnsFromFile)) {
        // Spot is not within the cave
        return false;
    }
    char Result = Grid[Row][Column];
    if (Result == 'X') {
        return false;
    } else if (Result == '_') {
        // Checks if spot is open ('-')
        return true;
    }
    // Spot is valid
    return true;
}

int Cave::numDeadEnds() {
    // Returns number of dead ends in path
    return NumOfDeadEnds;
}

void Cave::DisplayCaveHelper(int Row, int Column) {
    if (Row == NumOfRowsFromFile) {
        // If max number of rows is reached
        return;
    }
    // No more rows to display
    if (Column == NumOfColumnsFromFile) {
        // If max number of columns is reached
        cout << endl;  // Next row
        DisplayCaveHelper(Row + 1, 0);  // Next row at column 0
        return;
    }
    cout << Grid[Row][Column] << " ";  // Current spot
    DisplayCaveHelper(Row, Column + 1);  // For next column in current row
}

void Cave::displayCave() {
    DisplayCaveHelper(0, 0);  // Initial row and column
}

void Cave::searchPath() {
    Grid[StartOfRow][StartOfColumn] = '0';  // Position as 0
    FindPathInCave(StartOfRow, StartOfColumn);  // Start
}

void Cave::FindPathInCave(short Row, short Column) {
    SpotVisited[Row][Column] = true;
    int IsDirectionValid = 0;  // Direction of path
    Grid[Row][Column] = '0';  // Marks starting of path
    if (IsSpotValid(Row + 1, Column)) {
        FindPathInCave(Row + 1, Column);  // If spot below is valid, continue in same direction
        IsDirectionValid++;  // Increments IsDirectonValid counter
    }
    if (IsSpotValid(Row - 1, Column)) {
        FindPathInCave(Row - 1, Column);  // If spot above is valid, continue in same direction
        IsDirectionValid++;  // Increments IsDirectonValid counter
    }
    if (IsSpotValid(Row, Column - 1)) {
        FindPathInCave(Row, Column - 1);  // If spot left is valid, continue in same direction
        IsDirectionValid++;  // Increments IsDirectonValid counter
    }
    if (IsSpotValid(Row, Column + 1)) {
        FindPathInCave(Row, Column + 1);  // If spot right is valid, continue in same direction
        IsDirectionValid++;  // Increments IsDirectonValid counter
    }
    if (!IsDirectionValid) {
        NumOfDeadEnds++;  // If none of spots are valid, increments NumOfDeadEnds
    }
}

void Cave::displayPathHelper(int Row, int Column) {
    if (Row == NumOfRowsFromFile) {
        // If max number of rows is reached
        return;
    }
    if (Column == NumOfColumnsFromFile) {
        // If max number of columns is reached
        cout << endl;  // Next row
        displayPathHelper(Row + 1, 0);  // Next row at column 0
        return;
    }
    char spot = Grid[Row][Column];  // Current spot
    if (spot == 'X') {
        return;
    }
    // If none of spots are valid
    cout << spot << " ";  // Empty space
    displayPathHelper(Row, Column + 1);  // For next column in current row
}

void Cave::displayPath() {
    displayPathHelper(0, 0);  // Initial row and column
}

int main () {
    Cave TheCave;
    cout << " ";
    cout << "Initial grid: " << endl;
    TheCave.displayCave();
    cout << "Searching for path(s) through cave..." << endl;
    TheCave.searchPath();
    cout << "Path(s) found: " << endl;
    TheCave.displayPath();
    cout << "Dead ends: " << TheCave.numDeadEnds() << endl;
    return 0;
}
