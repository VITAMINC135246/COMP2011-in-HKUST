#include <iostream>
using namespace std;
#include <iostream>
using namespace std;
const int N = 9;
const char BLANKSPACE = ' ';
const char COLBREAK[] = "| ";
const char LINEBREAK[] = "------+-------+------";

void loadSudoku(int data[], int grid[N][N]){

    for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
    grid[row][col] = data[row * N + col];
}

void printSudoku(int grid[N][N]){
    int counter2 = 0;
    for (int i =0; i < N; i++){
        int counter1 = 0;
        for(int j = 0; j < N; j++){
            cout<<grid[i][j]<<BLANKSPACE;
            if (grid[i][j] >= 0 && grid[i][j] <=9  ){
                counter1 +=1;
            }
            if (counter1 % 3 == 0 && counter1 <= 6){
                cout<<COLBREAK<<BLANKSPACE;
            }
            if (counter1 %9 == 0){
                cout<<endl;
                if (counter1 = 27){
                cout<<LINEBREAK<<endl;
                }
            }

        }
    }
}

bool isValidNum(int grid[N][N], int row, int col, int num){
    while (grid[row][col] != 0){
        return false;
    }
    //depends on situation
    while ( num < 0 || num >9 ){
        return false;
    }

    for (int i =0; i < N; i++){
        while(num == grid [row][i] || num == grid [i][col]){
            return false;
        }
    }
    return true; // Ensure function returns a value
}

bool isFull(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool isValidSudoku(int grid[N][N]) {
    // Check rows and columns
    for (int i = 0; i < N; i++) {
        bool rowCheck[N + 1] = {false};
        bool colCheck[N + 1] = {false};
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != 0) {
                if (rowCheck[grid[i][j]]) return false;
                rowCheck[grid[i][j]] = true;
            }
            if (grid[j][i] != 0) {
                if (colCheck[grid[j][i]]) return false;
                colCheck[grid[j][i]] = true;
            }
        }
    }

    // Check 3x3 subgrids
    for (int boxRow = 0; boxRow < N; boxRow += 3) {
        for (int boxCol = 0; boxCol < N; boxCol += 3) {
            bool boxCheck[N + 1] = {false};
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = grid[boxRow + i][boxCol + j];
                    if (num != 0) {
                        if (boxCheck[num]) return false;
                        boxCheck[num] = true;
                    }
                }
            }
        }
    }

    return true;
}

int main()
{
// 0 is for empty cell in Sudoku puzzle
int data[N * N] = {5, 3, 0, 0, 7, 0, 0, 0, 0,
6, 0, 0, 1, 9, 5, 0, 0, 0,
0, 9, 8, 0, 0, 0, 0, 6, 0,
8, 0, 0, 0, 6, 0, 0, 0, 3,
4, 0, 0, 8, 0, 3, 0, 0, 1,
7, 0, 0, 0, 2, 0, 0, 0, 6,
0, 6, 0, 0, 0, 0, 2, 8, 0,
0, 0, 0, 4, 1, 9, 0, 0, 5,
0, 0, 0, 0, 8, 0, 0, 7, 9};
// Sudoku grid
int grid[N][N];
cout << "Welcome to the Sudoku game:" << endl;
loadSudoku(data, grid); // task a)
printSudoku(grid); // task b)
cout << endl;
int row, col, num;
while (!isFull(grid))
{ //check whether the grid is full, e.g. no 0
cout << "input row, col, num" << endl;
cin >> row >> col >> num;
if (isValidNum(grid, row, col, num)) // task c)
{
grid[row][col] = num;
cout << "grid[" << row << "][" << col << "] = " << num << endl;
printSudoku(grid);
}
else
cout << "Invalid number" << endl;
}
if (isValidSudoku(grid))
{ // check whether a Sudoku is done
cout << "Congratulations! You solved the Sudoku!" << endl;
printSudoku(grid);
}
else
cout << "Oops, something is wrong." << endl;
return 0;
}
