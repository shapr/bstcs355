#include "Bst.h"

BNode::BNode(){
  data = 0;
  left = NULL;
  right = NULL;
}

BNode::BNode(int d) {
  data = d;
  left = NULL;
  right = NULL;
}

BNode::BNode(int d,BNode* l, BNode* r){
  data = d;
  left = l;
  right = r;
}

int BNode::GetData() const{
  return data;
}

BST::BST() {
  root = NULL;
  cursor = NULL;
}

BST::~BST() {
  ClearList();
}

void BST::ClearList(){
  ClearListHelper(root);
}

void BST::ClearListHelper(BNode * n){
  // delete down the left branch
  if (n->left) ClearListHelper(n->left);
  // delete down the right branch
  if (n->right) ClearListHelper(n->right);
  delete n; // delete this node
}

bool BST::Insert(int e) {
  if (root == NULL){
    BNode * nn = new BNode(e); // BNode is type;	Declaring new value.
    // nn = new BNode(e);
    root = nn;
    cursor = nn;
    return true;
  }
  return InsertHelp(e, root);

  /*if (e < root->data)
  // We need to check left
  if (root->left == NULL){
  BNode ln;
  ln = new BNode(e);
  root->left = &ln;
  return true;
  }
  else
  root->left */
}

bool BST::InsertHelp(int e, BNode *&n) {
#ifdef DEBUG
  cout << "InsertHelp got " << e << endl;
#endif
  BNode * next;
  if (e < n->data) {
    next = n->left; // check left side
      cursor = n->left;
  }
  else {
    next = n->right; // Check right side
  }

  if (next == NULL) {
    // Creating a New node
    BNode * nn = new BNode(e); // new returns a pointer
    if (e < n->data) n->left = nn;
    else n->right = nn;
      cursor = n->right;
    return true;
  }
  else {
    return	InsertHelp(e, next);
  }
}

void BST::PrintIn(ostream& oss){
  PrintInHelp(oss, root);
}

void BST::PrintInHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintInHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if (n->left != NULL) PrintInHelp(oss, n->left);   // any left legs have been printed
  oss << n->data << endl; // Print itself
  if (n->right != NULL) PrintInHelp(oss, n->right); // print right legs
}

void BST::PrintPost(ostream& oss){
  PrintPostHelp(oss, root);
}

void BST::PrintPostHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintInHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if (n->left != NULL) PrintPostHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPostHelp(oss, n->right); // recursively print right branches
  oss << n->data << endl; // Print itself
}

void BST::PrintPre(ostream& oss){
  PrintPreHelp(oss, root);
}

void BST::PrintPreHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintPreHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  oss << n->data << endl; // Print itself
  if (n->left != NULL) PrintPreHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPreHelp(oss, n->right); // recursively print right branches
}

bool BST::Empty()const {
  if (root) return false;
  return true;
}

void BST::GoToBeginning() {
  BNode * n = root;
  while (n->left != NULL) {
    n = n->left;
  }
  cursor = n;
}

void BST::GoToEnd() {
  BNode * n = root;
  while (n->right != NULL) {
    n = n->right;
  }
  cursor = n;
}
