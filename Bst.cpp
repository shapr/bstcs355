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

bool BST::Insert(int e) {
	
	
	if (root == NULL){
		
		BNode nn; // BNode is type;	Declaring new value.
		nn = new BNode(e);
		root = &nn;
		return true;
		}
		
	else 
		
		return insertHelper(root, e);
		
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

bool BST::insertHelper(BNode *n, int e) {

	BNode * next;
	
	if (e < n->data) {
		next = n->left; // check left side
	}
	else {
		next = n->right; // Check right side
	}
	
		if (next == NULL) { 
			// Creating a New node
			BNode nN;
			nN = new BNode(e);
			next = &nN;
			return true;
		}
		else { 
			return	insertHelper(next, e);
		}
}

void BST::PrintIn(BNode * n, ostream & oss){
	
	if (n->left) PrintInHelp(n->left, oss);
	
	// any left legs have been printed
	oss << n.GetData(); // Print itself
	
	if (n->right) PrintInHelp(n->right, oss);
	return oss;

}
		
		
