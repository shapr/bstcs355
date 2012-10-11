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
BST::BST(const BST& Ftree){
    root = NULL;
    cursor = NULL;
    CopyList(Ftree.root);
}
void BST::ClearList(){
  if (root != NULL) ClearListHelper(root);
  root = NULL;
}

void BST::ClearListHelper(BNode * n){
  // delete down the left branch
  if (n->left != NULL) ClearListHelper(n->left);
  // delete down the right branch
  if (n->right != NULL) ClearListHelper(n->right);
  delete n; // delete this node
}

bool BST::Insert(int e) {
  if (root == NULL){
    BNode * nn = new BNode(e); // BNode is type;	Declaring new value.
    root = nn;
    cursor = nn;
    return true;
  }
  return InsertHelp(e, root);

}

bool BST::InsertHelp(int e, BNode *&n) {
	#ifdef DEBUG
  cout << "InsertHelp got " << e << endl;
#endif
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
	if (e < n->data){ n->left = nn;
	}		
    else n->right = nn;
		cursor = nn;
    return true;
  }
  else {
    return	InsertHelp(e, next);
  }
}

void BST::PrintIn(ostream& oss){
  if(root == NULL) {
    cout << "root is NULL, nothing to print\n";
    return;
  }
  // if(cursor == NULL) { cout << "cursor is NULL";}
  // else { cout << "cursor is " << cursor->data << endl; }

  PrintInHelp(oss, root);
}

void BST::PrintInHelp(ostream & oss, BNode * n){
	
  if (n->left != NULL) PrintInHelp(oss, n->left);   // any left legs have been printed
	if(n->data == cursor->data)
  oss << "[" <<  n->data << "]" << " "; // Print itself
	else
		oss << n->data << " ";
#ifdef DEBUG
  cout << "entered printInHelp node value is " << n->data << " left is " << n->left << " right is " << n->right;
#endif
  if (n->right != NULL) PrintInHelp(oss, n->right); // print right legs
}

void BST::PrintPost(ostream& oss){
  if(root == NULL) {
    cout << "root is NULL, nothing to print\n";
    return;
  }
  PrintPostHelp(oss, root);
  cout << endl << "Base List";
}

void BST::PrintPostHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintPostHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if (n->left != NULL) PrintPostHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPostHelp(oss, n->right); // recursively print right branches
	if(n->data == cursor->data)
  oss << "[" <<  n->data << "]" << " "; // Print itself
	else
		oss << n->data << " ";
}

void BST::PrintPre(ostream& oss){
  if(root == NULL) {
    cout << "root is NULL, nothing to print\n";
    return;
  }
  PrintPreHelp(oss, root);
  cout << endl << "Base List";
}

void BST::PrintPreHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintPreHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if(n->data == cursor->data)
  oss << "[" <<  n->data << "]" << " "; // Print itself
	else
		oss << n->data << " ";
  if (n->left != NULL) PrintPreHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPreHelp(oss, n->right); // recursively print right branches
}

bool BST::Empty()const {
  if (root != NULL) return false;
  return true;
}

void BST::GoToBeginning() {
  if(root == NULL) return;
  else{
  BNode * n = root;
  while (n->left != NULL) {
    n = n->left;
  }
  cursor = n;
  }
}

void BST::GoToEnd() {
  BNode * n = root;
  if (n == NULL) return; // uh, no?
  while (n->right != NULL) {
    n = n->right;
  }
  cursor = n;
}

BNode * BST::Find(int e) {
  FindHelper(e, root);
  if(cursor == NULL){
	  GoToEnd();
  return NULL;
  }
  else
	  return cursor;
}

void BST::FindHelper(int e, BNode * current){
  if (current == NULL) {
    GoToEnd(); // catches the null case;
	cursor = NULL;
    return;
  }
  if (e == current->data) cursor = current;
  if (e < current->data) FindHelper(e, current->left);
  if (e > current->data) FindHelper(e, current->right);
}

BNode * BST::AtCursor()const {
  return cursor;
}

bool BST::Remove(int e){
  BNode * tmpcursor = cursor; // we want to restore the cursor when we're done
  BNode * d = Find(e); // get a pointer to the node
  if (d == tmpcursor) { 
    GoToEnd(); // don't restore cursor to deleted node
  } else {
    cursor = tmpcursor;
  }
  
  if(d==NULL) return false; // well DUH
  // BNode * parent = getParent(d);
  // cout << "removing " << e << " node has value " << d->data << "branches are " << d->left << " " << d->right << endl;
  // cout << "Does NULL == 0? " << (NULL == 0) << endl;
  // node has no children, remove from tree
  if ((d->left == NULL) && (d->right == NULL)) {
    //cout << "inside zero children remove\n";
    if (d == root) {
      //cout << "inside root removal\n";
      delete d;
      root = NULL;
      return true; // ARGH
    } else {
      //cout << "removing non-root zero-child node\n";
      BNode * parent = getParent(d);
      // check parent, set matching branch pointer to NULL
      if (parent->left == d) {
        parent->left = NULL;
        delete d;
        return true;
      } else {
        parent->right = NULL;
        delete d;
        return true;
      }
    }
  } else {
    // cout << "skipped out of zero children\n"; 
  }

  int children = 0; // this is ugly
  BNode * child;
  if(d->left != NULL) {
    children++;
    child = d->left;
  }
  if(d->right != NULL) {
    children++;
    child = d->right;
  }
  if(children == 1) {   // has only one child
    // delete node, replace with its one child
    if(d == root) {
      root = child;
      delete d;
      return true;
    }
    BNode * parent = getParent(d);
    if(parent->left == d) parent->left = child;
    if(parent->right == d) parent->right = child;
    delete d;
    return true;
  }
  /* node to delete has two children
     swap value with left-most child of right subtree (in-order successor)
     in-order successor node will have zero or one children,
     delete swapped value according to simpler cases above
  */
  BNode * succ = d->right; // follow branch to the right once
  // cout << "succ after one step right has value " << d->data << endl;
  // a segfault here can only mean I'm not setting the branch pointers to NULL!
  while(succ->left != NULL) { // follow branches all the way to the left
    succ = succ->left;
  }
#ifdef DEBUG
  cout << "delete node with two children should now have traversed to in-order successor\n";
  cout << "traversed from" << d->data << " to " << succ->data << endl;
#endif
  // swap the two integer values
  int tmp = d->data;
  d->data = succ->data;
  succ->data = tmp;
  // delete the node that has one or two children
  return Remove(succ->data);
}


BNode * BST::getParent(BNode * child){
  if (child == root) return NULL;
  return getParentHelp(child, root);
}

/*
  got handed node, if this node has pointer to the object of search, return THIS node.
  if not, call ourself with the children
  if no children, return NULL pointer.
 */
BNode* BST::getParentHelp(BNode * child,BNode * current){
#ifdef DEBUG
  cout << "entered getParentHelp, node holds " << current->data << " left is " << current->left << " right is " << current->right;
#endif
  if(current == NULL) return NULL;
  if(current->left == child) return current; // check this node
  if(current->right == child) return current; // check this node
  BNode * found;
  if ( (found = getParentHelp(child, current->left)) ) return found; // recursively search left branches
  if ( (found = getParentHelp(child, current->right)) ) return found; // recursively search right branches
  return NULL;
}
/*
  go to prev is left child or
  getParent until parent->data < current->data
  go to next is right child or
  get parent until parent->data is > current->data
*/
void BST::GoToPrev(){
  if (cursor == NULL) return; // duh, fail

  // branch case, left branch once, right many
  if (cursor->left != NULL) {
    cursor = cursor->left;
    while (cursor->right != NULL) {
      cursor = cursor->right;
    }
    return; // our work here is done.
  } else {
    // cursor->left IS null
    // getParent until the value is less than current->data
    BNode * parent = getParent(cursor);
    if (parent == NULL) return; // FAIL
    while(parent->data > cursor->data){
      parent = getParent(parent);
      if (parent == NULL) return; // MORE FAIL
    }
    cursor = parent; // found a parent that has a value LESS than the current value, hurrah!
    return; // our work here is done.
  }
}

void BST::GoToNext(){
  if(cursor == NULL) {
    // cout << "cursor is null on gotonext"; 
    return; // you FAIL
  }
  if(cursor->right != NULL) {
    // cout << "recursing right, then many left";
    cursor = cursor->right;
    while(cursor->left != NULL) {
      cursor = cursor->left;
    }
    // cout << "should be right";
    return; // all done
  } else {
    // cursor right IS null, leaf case requires us to go to parent
    // cout << "gotonext walking parents";
    BNode * parent = getParent(cursor);
    if(parent == NULL) return; // NOW what broke?
    while(parent->data < cursor->data){
      parent = getParent(parent);
      if(parent == NULL) return; // you screwed the pooch
    }
    cursor = parent; // found a parent that has a value GREATER than the current value!
    return; // we all done
  }
}

void BST::CopyList(BNode* previousNode) {
	if(root == NULL){
		cout << "List is Empty" << endl;
		return;
	}
	else{
	Insert(previousNode->data);

	if (previousNode->left != NULL)
		CopyList(previousNode->left);

	if (previousNode->right != NULL)
		CopyList(previousNode->right);
	}
}

BST& BST::operator=(const BST& Ftree){

    ClearList();

    CopyList(Ftree.root); // Ftree = First Tree

    return *this;

}
