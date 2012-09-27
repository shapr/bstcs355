#include "Bst.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  BST testBST;
  int data;
  testBST.Insert(36);
  testBST.PrintIn(cout);
  testBST.Insert(5);
  testBST.PrintIn(cout);
  testBST.Insert(20);
  testBST.Insert(10);
  testBST.Insert(7);
  testBST.PrintIn(cout);
}
