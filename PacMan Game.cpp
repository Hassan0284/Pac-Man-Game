#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h> 

using namespace std;

//calculate Euclidean distance btw ghost and pacman
double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    int i, j, row = 0, col = 0;
    int R = 4, C = 5; //ghost position
    int k = 6, l = 8; //pacman position

    int r1, r2, r3, r4; //random numbers for walls
    char move;
    int count = 0;

    srand(time(0));
    r1 = rand() % 12 + 5;
    r2 = rand() % 15 + 3;
    r3 = rand() % 13 + 3;
    r4 = rand() % 16 + 3;

    cout << "Enter number of rows for maze: ";
    cin >> row;
    cout << "Enter number of columns for maze: ";
    cin >> col;
    cout << "Use a or A for moving Pac-Man 'left'.\nUse s or S for moving Pac-Man 'Down'" << endl;
    cout << "Use d or D for moving Pac-Man 'right'.\nUse w or W for moving Pac-Man 'up'." << endl;

    string universal[row][col];
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                universal[i][j] = "#"; //boundary walls
            } else {
                universal[i][j] = ".";
                count++;
            }
        }
    }

    //creating random walls
    for (i = r1; i <= r1; i++) {
        for (j = r3; j <= r2; j++) {
            universal[i][j] = "#";
        }
    }
    for (i = r1; i <= r2; i++) {
        for (j = r4; j <= r4; j++) {
            universal[i][j] = "#";
        }
    }
    for (i = r4; i <= r4; i++) {
        for (j = r3; j <= r2; j++) {
            universal[i][j] = "#";
        }
    }
    for (i = r4; i <= r3; i++) {
        for (j = r2; j <= r2; j++) {
            universal[i][j] = "#";
        }
    }

    universal[k][l] = "P"; //initial position of pacman
    universal[R][C] = "G"; //initial position of ghost

    cout << endl;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cout << universal[i][j] << " ";
        }
        cout << endl;
    }

    while (true) {
        cout << endl << "Enter your move: ";
        move = _getch(); //for immediate input without pressing enter

        int newK = k, newL = l;

        if (move == 's' || move == 'S') newK++;
        if (move == 'w' || move == 'W') newK--;
        if (move == 'a' || move == 'A') newL--;
        if (move == 'd' || move == 'D') newL++;

        if (universal[newK][newL] != "#") {
            universal[k][l] = " ";
            k = newK;
            l = newL;
            universal[k][l] = "P";
            count--;
        }

        //ghost chasing pacman with some random movement
        int nextR = R, nextC = C;
        double minDist = calculateDistance(R, C, k, l);
        int possibleMoves[4][2] = {{R - 1, C}, {R + 1, C}, {R, C - 1}, {R, C + 1}};
        bool foundMove = false;

        //randomly decide if the ghost should move randomly or intelligently
        if (rand() % 100 < 70) { //70% chance to move intelligently
            for (int m = 0; m < 4; m++) {
                int newR = possibleMoves[m][0];
                int newC = possibleMoves[m][1];
                if (universal[newR][newC] != "#" && calculateDistance(newR, newC, k, l) < minDist) {
                    nextR = newR;
                    nextC = newC;
                    minDist = calculateDistance(newR, newC, k, l);
                    foundMove = true;
                }
            }
        } 

        //if not found an intelligent move or decided to move randomly
        if (!foundMove || rand() % 100 < 30) { //30% chance to move randomly
            int randomMoveIndex = rand() % 4;
            nextR = possibleMoves[randomMoveIndex][0];
            nextC = possibleMoves[randomMoveIndex][1];
            if (universal[nextR][nextC] == "#") { //if random move hits a wall, don't move
                nextR = R;
                nextC = C;
            }
        }

        //move the ghost
        if (universal[nextR][nextC] != "P") {
            universal[R][C] = " ";
            R = nextR;
            C = nextC;
            universal[R][C] = "G";
        }

        //check for game over
        if (R == k && C == l) {
            cout << "Game Over! You were caught by the ghost!" << endl;
            break;
        }

        system("CLS"); //clear screen
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                cout << universal[i][j] << " ";
            }
            cout << endl;
        }

        if (count == 0) {
            cout << "You win! All dots have been eaten!" << endl;
            break;
        }
    }
    return 0;
}

