#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

/*the iterative method using a matrix passed in as a parameter. It runs a nested for loop, checking to see if the characters between the strings match. If they do, then it adds one to the number saved in the spot one up and one to the left of it. If not, then it saves whichever is the larger value between the spot to its left and above. It repeats this and then returns the integer saved in the bottom right corner of the matrix, which should be the length of the longest common subsequence.
*/
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

/*this function does the same thing as the iterative method above except that it creates its own matrix inside to do it. The process is identical, and it returns the bottom right spot of the matrix.*/
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
/*This method takes the same parameters as the iterative method without the matrix but uses recursion. The base case is if either of the string lengths are zero. If the characters at the end of the strings are identical, it returns the function while passing in both strings with one less length, adding 1. OTherwise, it returns the function with one of the strings shortened by one, determined by whichever is the larger of the two.
*/
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
/* This method uses the already filled matrix from the first iterative method (with matrix parameter) to construct the string, through recursion. The base case is when both top and left spot are zero. If they are equal, the function adds whichever character corresponds and returns the function with a shortened string. Otherwise, it returns the function based on whichever spot, left or top, is smaller or greater than the other.*/
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

/*
I included this method as a means of testing the methods of this program with much smaller input. It also prints out the actual matrices in the backtrack and first iterative method, so that one can observe whether or not the internal process is correct.
*/
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
  
  //Testing the iterative method with external matrix. Length for each length method
  //should be 3 and the string should be "ADF" 
  
  int lcs_Length = lcs_it(D,testOne,testTwo,lengthOne,lengthTwo);
  cout << "the length of the LCS is " << lcs_Length << endl; //first iterative method
  lcs_Length = lcs_it_test(testOne,testTwo,lengthOne,lengthTwo); 
  cout << "the length of the LCS is" << lcs_Length << endl;//iterative method without matrix as parameter
  lcs_Length = lcs_re(testOne,testTwo,lengthOne,lengthTwo);
  cout << "the length of the LCS is " << lcs_Length << endl;

  string actualLCS = backtrack(D,testOne,testTwo,lengthOne,lengthTwo);
  cout << "The LCS is " << actualLCS << endl;

  
  //Testing to see that the matrix printed properly.
  cout << "the 2d matrix at present is: " << endl;
    for (int i = 0; i < lengthOne+1; ++i) {
      for (int j = 0; j < lengthTwo+1; ++j) {
        cout << D[i][j];
      }
      cout << endl;
    }
}

/*
This main method takes two strings from a file, saves the size into two int variables, creates a two dimensional array, and then runs the necessary tests. It first prints the length of the two strings passed in through the input file. It then gets the length of the longest common subsequence first using the iterative method with a matrix sent in as a parameter. Then it retrieves the actual sequence using the backtrack method. 

In the second part, it uses the iterative and recursive methods without matrices to find the lcs in two strings of length that the user chooses. It acquires the length and prints the time it took to finish that process. Finally it repeats this with every length from 1-800 for the iterative function, and 1-20 for the recursive.
*/
int main() {
  string X;
  string Y;
  int start_s, stop_s;

  ifstream inputFile;
  //Enter the title of the input file here.
  inputFile.open("input.txt");
  
  inputFile >> X;
  inputFile >> Y;

  int m = X.size();
  int n = Y.size();
  int **C = new int*[m+1];
  for (int i = 0; i < m+1; ++i) {
    C[i] = new int [n+1];
  }  


  //Part One:
  cout << X.size() << endl;
  cout << Y.size() << endl;

  

  int len = lcs_it(C,X,Y,m,n);

  cout << "length of lcs is " << len << endl;
  cout << "LCS is " << backtrack(C,X,Y,m,n) << endl;
  cout << endl;

  
  //Part Two:

  //measuring the time for the iterative function.
  int iterativeTest;
  int recursiveTest;
  
  cout << "Please enter a length for iterative function to test: (0-800)" << endl;
  cin >> iterativeTest;
  if (iterativeTest < 0 || iterativeTest > 800) {
    cout << "Error, unusable length. Changing to 1." << endl;
    iterativeTest = 1;
  }
  cout << "Please enter a length for recursive function to test: (0-20)" << endl;
  cin >> recursiveTest;
  if (recursiveTest < 0 || recursiveTest > 20) {
    cout << "Error, unusuable length. Changing to 1." << endl;
    recursiveTest = 1;
  }

  start_s = clock();
  int result = lcs_it_test(X,Y,iterativeTest,iterativeTest);
  stop_s=clock();
  cout << "For your input : (" << iterativeTest << ") the result";
  cout << " was length " << result << " and it took ";
  cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000<< " seconds using the iterative method." << endl;

  start_s = clock();
  result = lcs_re(X,Y,recursiveTest,recursiveTest);
  stop_s=clock();
  cout << "For your input : (" << recursiveTest << ") the result";
  cout << " was length " << result << " and it took ";
  cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000<< " seconds using the recursive method." << endl;
  
  
  //measuring the time for the iterative function
  for (int i=1; i <= 800; i++) {
    start_s=clock();
    int stuff = lcs_it_test(X,Y,i,i);
    stop_s=clock();
    clog << i << "\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
  }
  
  //measuring the time for the recursive function.
  for (int i=1; i <= 20; i++) {
    start_s=clock();
    int stuff = lcs_re(X,Y,i,i);
    stop_s=clock();
    clog << i << "\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
  }

  return 0;
} 