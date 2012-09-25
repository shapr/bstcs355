#include "Bst.h"

BNode::BNode(){
  data = 0;
  left = null;
  right = null;
};

BNode::BNode(int d) {
  data = d;
  left = null;
  right = null;
};

BNode::BNode(int d,BNode* l, BNode* r){
  data = d;
  left = l;
  right = r;
}

BST::BST() {};
