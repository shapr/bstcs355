#include "Bst.h"
#include <iostream>
#include <string>
using namespace std;

int main() {

  BST testBST;
  int data;
  cout << "inserting 36\n"; // Insertion of 36
  testBST.Insert(36);
  cout << "inserting 5\n"; // Insertion of 5
  testBST.Insert(5);
  cout << "inserting 20\n"; // Insertion of 20
  testBST.Insert(20);
  cout << "inserting 10\n"; // Insertion of 10
  testBST.Insert(10);
  cout << "inserting 7\n"; // Insertion of 7
  testBST.Insert(7);
  cout << "calling PrintIn\n"; // Call PrintIn
  testBST.PrintIn(cout);
}
