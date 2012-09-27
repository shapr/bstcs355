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
  BNode * next;
  if (e < n->data) {
    next = n->left; // check left side
  }
  else {
    next = n->right; // Check right side
  }

  if (next == NULL) {
    // Creating a New node
    BNode * nn = new BNode(e); // new returns a pointer
    next = nn;
    return true;
  }
  else {
    return	InsertHelp(e, next);
  }
}

void BST::PrintInHelp(ostream & oss, BNode * n){
  if (n->left) PrintInHelp(oss, n->left);
  // any left legs have been printed
  oss << n->GetData(); // Print itself
  if (n->right) PrintInHelp(oss, n->right);
  // return oss;
}


