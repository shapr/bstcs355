#include "Bst.h"
#include <iostream>
#include <string>
using namespace std;

int main() {

  BST testBST;
  int data;
  cout << "inserting 20\n";
  testBST.Insert(20);
  cout << "inserting 15\n";
  testBST.Insert(15);
  cout << "inserting 30\n";
  testBST.Insert(30);
  cout << "inserting 5\n";
  testBST.Insert(5);
  cout << "inserting 18\n";
  testBST.Insert(18);
  cout << "inserting 40\n";
  testBST.Insert(40);
  cout << "inserting 25\n";
  testBST.Insert(25);

  cout << "calling PrintIn\n";
  testBST.PrintIn(cout);
  cout << "calling PrintPost\n";
  testBST.PrintPost(cout);
  cout << "calling PrintPre\n";
  testBST.PrintPre(cout);

  cout << "calling Find(4)\n";
  BNode * found = testBST.Find(4);
  cout << "found " << (*found).GetData() << endl;
}
