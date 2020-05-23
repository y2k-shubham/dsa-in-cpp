#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector <vector <int> > prettyPrint(int);
void showVec(vector <vector <int> >);

int main() {
  showVec(prettyPrint(4));
  showVec(prettyPrint(4));
  showVec(prettyPrint(3));
  showVec(prettyPrint(2));
  showVec(prettyPrint(1));
}

void showVec(vector <vector <int> > matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix.size(); j++) {
      printf("%d\t", matrix[i][j]);
    }
    cout << endl;
  }
  cout << endl;
}

vector<vector<int> > prettyPrint(int A) {
    int sideLength = (2 * A) - 1;
    vector <vector <int> > matrix(sideLength);
    
    // allocate space for matrix
    for (int i = 0; i < sideLength; i++) {
        vector <int> tempVec(sideLength);
        matrix[i] = tempVec;
    }
    
    // fill matrix
    for (int fillVal = A; fillVal >= 1; fillVal--) {
        int rowMin = A - fillVal;
        int colMin = A - fillVal;
        
        int rowMax = sideLength - rowMin - 1;
        int colMax = sideLength - colMin - 1;
        
        int row = rowMin;
        int col = colMin;
        
        // left to right
        while (col <= colMax) {
            matrix[row][col] = fillVal;
            col++;
        }
        col--;
        
        // top to bottom
        while (row <= rowMax) {
            matrix[row][col] = fillVal;
            row++;
        }
        row--;
        
        // right to left
        while (col >= colMin) {
            matrix[row][col] = fillVal;
            col--;
        }
        col++;
        
        // bottom to top
        while (row >= rowMin) {
            matrix[row][col] = fillVal;
            row--;
        }
        row++;
    }
    
    return matrix;
}
