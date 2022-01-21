#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int lcs_it(int **C, string X, string Y, int m, int n) {
  int length;


  for (int i = 1; i < m+1; i++) {
    for (int j = 1; j < n+1; j++) {
      if (X[i-1] == Y[j-1]) {
        C[i][j] = C[i-1][j-1] +1;
      }
      else {
        C[i][j] = max(C[i-1][j],C[i][j-1]);
      }
    }
  }
  /*
  for (int i = 0; i < m+1; i++) {
    for (int j = 0; j < n+1; j++) {
      cout << C[i][j];
    }
    cout << endl;
  }
*/

  return C[m][n];
}

int lcs_it_test(string X, string Y, int m, int n) {
  
  int **C = new int*[m+1];
  for (int i = 0; i < m+1; ++i) {
    C[i] = new int [n+1];
  }
  for (int i = 0; i < m+1; i++) {
    for (int j = 0; j < n+1; j++) {
      C[i][j] = 0;
    }
  }  

  for (int i = 1; i < m+1; i++) {
    for (int j = 1; j < n+1; j++) {
      if (X[i-1] == Y[j-1]) {
        C[i][j] = C[i-1][j-1] +1;
      }
      else {
        C[i][j] = max(C[i-1][j],C[i][j-1]);
      }
    }
  }
  //Code used for testing the function
  /*
  for (int i = 0; i < m+1; i++) {
    for (int j = 0; j < n+1; j++) {
      cout << C[i][j];
    }
    cout << endl;
  }
  */
  return C[m][n];
}

int lcs_re(string X, string Y, int m, int n) {
  if ((m==0) || (n==0)) {
    return 0;
  }
  else if (X[m]==Y[n]) {
    return 1 + lcs_re(X,Y, m-1,n-1);
  }
  else {
    return max(lcs_re(X,Y,m-1,n),lcs_re(X,Y,m,n-1));
  }
}

string backtrack(int **C, string X, string Y, int m, int n) {

 if (m == 0 || n == 0) {
   string tmp = "";
   return tmp;
 }
 else if (C[m-1][n] > C[m][n-1]) {
   return backtrack(C,X,Y,m-1,n);
 }
 else if (C[m][n-1] > C[m-1][n]){
   return backtrack(C,X,Y,m,n-1);
 }
 else {
   return backtrack(C,X,Y,m-1,n-1) + X[m-1];
 } 
}

void driverTest() {
  string testOne;
  string testTwo;

  testOne = "ABCDEF";
  testTwo = "ADF";

  int lengthOne = testOne.size();
  int lengthTwo = testTwo.size();

  cout << "Length of ABCDEF is " << lengthOne << endl; //should be 6
  cout << "Length of ADF is " << lengthTwo << endl; // should be 3

  int **D = new int*[lengthOne];
  for (int i = 0; i < lengthOne+1; ++i) {
    D[i] = new int[lengthTwo+1];
  }

  // after initialization matrix should be all zeros
  cout << "the 2d matrix at present is: " << endl;
  for (int i = 0; i < lengthOne+1; ++i) {
    for (int j = 0; j < lengthTwo+1; ++j) {
      cout << D[i][j];
    }
    cout << endl;
  }
  
  //Testing the iterative method with external matrix. Should be 3 
  int lcs_Length = lcs_it(D,testOne,testTwo,lengthOne,lengthTwo);
  cout << "the length of the LCS is " << lcs_Length << endl;
  
  //Testing to see that the matrix printed properly.
  cout << "the 2d matrix at present is: " << endl;
    for (int i = 0; i < lengthOne+1; ++i) {
      for (int j = 0; j < lengthTwo+1; ++j) {
        cout << D[i][j];
      }
      cout << endl;
    }
}

int main() {
  string X;
  string Y;
  int start_s, stop_s;

  ifstream inputFile;
  inputFile.open("input.txt");
  
  inputFile >> X;
  inputFile >> Y;

  int m = X.size();
  int n = Y.size();

  //Part One:
  cout << X.size() << endl;
  cout << Y.size() << endl;

  int **C = new int*[m+1];
  for (int i = 0; i < m+1; ++i) {
    C[i] = new int [n+1];
  }  

  int len = lcs_it(C,X,Y,m,n);

  cout << "length is " << len << endl;
  cout << "LCS is " << backtrack(C,X,Y,m,n) << endl;
  cout << endl;

  /*
  //Part Two:
  //measuring the time for the iterative function.
  for (int i=1; i <= 800; i+=5) {
    start_s=clock();
    int stuff = lcs_it_test(X,Y,i,i);
    stop_s=clock();
    clog << i << "\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000<<endl;
  }
  //measuring the time for the recursive function.
  for (int i=1; i <= 20; i++) {
    start_s=clock();
    int stuff = lcs_re(X,Y,i,i);
    stop_s=clock();
    clog << i << "\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000<<endl;
  }
  */
  return 0;
} 