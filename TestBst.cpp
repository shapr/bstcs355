#include "Bst.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  BST testBST;
  int data;
  cout << "inserting 36\n";
  testBST.Insert(36);
  cout << "inserting 5\n";
  testBST.Insert(5);
  cout << "inserting 20\n";
  testBST.Insert(20);
  cout << "inserting 10\n";
  testBST.Insert(10);
  cout << "inserting 7\n";
  testBST.Insert(7);
  cout << "calling PrintIn\n";
  testBST.PrintIn(cout);
}
